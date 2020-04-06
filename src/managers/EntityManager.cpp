//============================================================================
// Name       		: EntityManager.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/25/2020
//============================================================================




#include "EntityManager.h"
#include "../entities/IEntity.hpp"
#include "Builder.h"
#include "../utilities/GameLogger.h"
#include "../utilities/physics/Collisions.h"
#include "../utilities/physics/Dimension.h"
#include "../utilities/physics/Direction.h"
#include "../utilities/physics/Position.h"
#include "RendererManager.h"
#include "../world/TileMap.h"
#include "../world/ITile.h"




EntityManager::EntityManager(class GameLogger *loggerptr)
	: logger(loggerptr),
	  entityID(0) {
	logger->message(EnumLogLevel::INFO, "Entity Manager has been initialized", EnumLogOutput::TXT_FILE);
}



EntityManager::~EntityManager() {
	logger->message(EnumLogLevel::INFO, "Entity Manager stopped", EnumLogOutput::TXT_FILE);
}



/*
 * @param	tag The entity's identification tag
 *
 * @param	builder A pointer to the entity's builder
 *
 * Registers the given Entity's builder with the Entity Manager
 */
void EntityManager::registerEntity(std::string tag, BuilderBase<IEntity>* builder){

	logger->message(EnumLogLevel::INFO, "Registering Entity '" + tag + "'", EnumLogOutput::TXT_FILE);

	auto itr = this->entityRegistry.insert({tag, std::unique_ptr<BuilderBase<IEntity>>(builder)});
	builder = nullptr;

	//insert returns a pair, the first element is an iterator and the second is if the insert was successful
	itr.second ? logger->message(EnumLogLevel::INFO, "Entity '" + tag + "' has been registered", EnumLogOutput::TXT_FILE) :
			logger->message(EnumLogLevel::ERROR, "The Entity tag: '" + tag + "' is not unique! The Entity's builder was not registered", EnumLogOutput::TXT_FILE);
}



/*
 * @nullable
 *
 * @param	tag The entity's identification tag
 *
 * @param	pos The location the entity will be spawned
 *
 * @param	facing The direction that the Entity is facing
 *
 * @return	A pointer to the Entity that has been spawned
 *
 * Spawns an Entity at the given coordinates.
 * Do Not delete the pointer that is returned
 */
IEntity* EntityManager::spawn(std::string tag, const Position &pos, EnumSide facing){

	if(!this->entityRegistry.count(tag)) {
		logger->message(EnumLogLevel::WARNING, "The Entity: '" + tag + "' could not be spawned, tag is missing in registry", EnumLogOutput::TXT_FILE);
		return nullptr;
	}

	IEntity *entity = this->entityRegistry[tag]->build();
	this->entityList.emplace_back(std::unique_ptr<IEntity>(entity));
	entity->spwan(pos, EnumSide::RIGHT, getNextEntityID());
	return entity;
}



/*
 * Despawns all Entities that have been marked as inactive
 *
 * This will check all Entities even those that are not on screen
 * it is recommended that this method is not called each tick
 */
void EntityManager::despawn(){

	logger->message(EnumLogLevel::INFO, "Removing all inactive Entities", EnumLogOutput::TXT_FILE);
	auto itr = entityList.begin();
	while(itr != entityList.end()) {
		if(!itr->get()->isActive()) {
			itr->get()->onDespwan();
			itr = entityList.erase(itr);
		}
		else itr++;
	}
}



/*
 * @param	cameraPos Coordinates of the camera
 *
 * @param	windowSize Size of the Window
 *
 * @param	renderer Reference to the Renderer Manager
 *
 * @param	renderAabb Flag if Entity's axis aligned
 * 			bounding box should be rendered
 *
 * Draws all Entities that are visible on screen
 */
void EntityManager::drawAll(const Position &cameraPos, const Dimension &windowSize, RendererManager &renderer, bool renderAabb){

	std::vector<IEntity*> entitiesOnScreen;
	//TODO fix 'pop-in', currently entities will 'pop in' along the top-left edges of the screen
	this->getEntities(entitiesOnScreen, AABB(cameraPos.xPos(), cameraPos.yPos(), cameraPos.xPos() + windowSize.width, cameraPos.yPos() + windowSize.height));
	for(auto &itr : entitiesOnScreen) {
		if(renderAabb) {
			switch(itr->getType()) {
			case EnumEntityType::AGGRESSIVE:
				renderer.setDrawColor(255, 0, 0, 255);
				break;

			case EnumEntityType::NEUTRAL:
				renderer.setDrawColor(255, 255, 0, 255);
				break;

			case EnumEntityType::PASSIVE:
				renderer.setDrawColor(0, 255, 0, 255);
				break;

			case EnumEntityType::PLAYER:
				renderer.setDrawColor(0, 0, 255, 255);
				break;

			default:
				renderer.setDrawColor(255, 255, 255, 255);
				break;
			}
			renderer.drawRect(itr->getAabb().getPos() - cameraPos, Dimension(itr->getAabb().widthN(), itr->getAabb().heightN()), false);
		}
		renderer.drawSprite(itr->getRegistryTag(), itr->getPos(), cameraPos, itr->getSprite(), false);
	}
}



/*
 * @param	cameraPos Coordinates of the camera
 *
 * @param	windowSize Size of the Window
 *
 * @param	deltaTime The time since the last tick
 *
 * @param	worldIn The current map
 *
 * Updates all Entities that are currently on screen
 */
void EntityManager::tickAll(const Position &cameraPos, const Dimension &windowSize, TileMap &worldIn, float deltaTime){

	//logger->message(Level::INFO, "Ticking all Entities on screen", Output::TXT_FILE);
	std::vector<IEntity*> entitiesOnScreen;
	this->getEntities(entitiesOnScreen, AABB(cameraPos.xPos(), cameraPos.yPos(), cameraPos.xPos() + windowSize.width, cameraPos.yPos() + windowSize.height));

	for(auto &itr : entitiesOnScreen) {
		if(itr->isActive()) {
			itr->tick(worldIn, deltaTime);
			if(itr->canCollide()){
				this->checkEntityCollisions(entitiesOnScreen, *itr);
				this->checkTileCollisions(worldIn, *itr);
			}
		}
	}
}



/*
 * @param	vectorIn The vector that the array of Entities is to be added to
 *
 * @param	area The area to search for Entities
 *
 * Adds a list of Entities in the given area to the vector that is passed in
 */
void EntityManager::getEntities(std::vector<IEntity*> &vectorIn, const AABB &area){

	for(auto &itr : this->entityList) {
		if(Collision::RectVsPt(area, itr->getPos())) {
			vectorIn.emplace_back(itr.get());
		}
	}
}



//Gets the next Entity ID and increments to the next ID
unsigned int EntityManager::getNextEntityID(){
	return this->entityID++;
}



/*
 * @param	entities List of all Entities that are on screen
 *
 * @param	entity The subject Entity that is being tested for collisions
 *
 * Checks if the given Entity is colliding with any entity in the array
 * and if it is colliding the Entity's position will be changed
 */
void EntityManager::checkEntityCollisions(std::vector<IEntity*> &entities, IEntity &entity){

	for(auto &itr : entities) {
		if(itr->getID() != entity.getID() && itr->isActive() && itr->canCollide()) {
			//Make sure that the Entity is not being checked against itself
			EnumSide side = Collision::RectEdge(entity.getAabb(), itr->getAabb());
			if(side != EnumSide::NONE) {
				entity.onEntityColision(*itr, side);
			}
		}
	}
}



/*
 * @param	worldIn The tile map to check the collisions against
 *
 * @param	entity The Entity to check for collisions
 *
 * Checks if the given Entity is colliding with any Tiles in the world
 * and if it is colliding the Entity's onTileColision method will be called
 *
 * Entity vs Tile collision is done by creating a "collision loop" around the Entity
 */
void EntityManager::checkTileCollisions(TileMap &worldIn, IEntity &entity){

	const Dimension topLeftTile(-1, -1);

	/*
	 * The bottom-right tile is determined by the Entity's size
	 * this is done so that if an Entity is bigger than one tile the collision loop will grow to fully enclose the Entity
	 */
	Dimension bottomRightTile(1 + static_cast<int>(entity.getAabb().width()/worldIn.tileWidth() + 0.5),
			1 + static_cast<int>(entity.getAabb().height()/worldIn.tileHeight() + 0.5));

	//This translates the entity's position into the tile-map unit coordinate system aka "Tile-Space"
	Dimension entityTile(static_cast<int>(entity.getAabb().getPos().xPos()/worldIn.tileWidth() + 0.5),
			static_cast<int>(entity.getAabb().getPos().yPos()/worldIn.tileHeight() + 0.5));

	//Check if the entity collides with any of the tiles around it
	//TODO Improve performance by skipping the corner tiles as they can never be collided with
	for(int y = topLeftTile.height; y <= bottomRightTile.height; y++) {
		int yCord = y + entityTile.height;

		//Skip if the y coordinate is outside of the tile-map
		if((yCord < 0) || (yCord > worldIn.height())) continue;
		for(int x = topLeftTile.width; x <= bottomRightTile.width; x++) {
			int xCord = x + entityTile.width;

			//Skip if the x coordinate is outside of the tile-map
			if((xCord < 0) || (xCord > worldIn.width())) continue;

			ITile *tile = worldIn.getTile(xCord, yCord);
			if(tile == nullptr) {
				//Fail safe if the above somehow does not catch the tile-map being indexed out of
				logger->message(EnumLogLevel::WARNING,
						"Null Pointer exception: Tried to check Tile for collisions but Tile does not exist",
						EnumLogOutput::TXT_FILE);
				return;
			}

			if(tile->canCollide()) {
				EnumSide side = Collision::RectEdge(tile->getAabb(), entity.getAabb());

				if(side != EnumSide::NONE) {
					//Check if the side collided with is an "internal edge", if it is an internal edge ignore it
					//Internal edges when collided with can cause "sticky" behavior
					ITile *tile2 = worldIn.getOffsetTile(tile->getPos(), side);
					if(tile2 != nullptr && !tile2->canCollide()) entity.onTileColision(*tile, side);
				}
			}
		}
	}
}








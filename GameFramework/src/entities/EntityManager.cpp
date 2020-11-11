#include "EntityManager.h"
#include "IEntity.hpp"
#include "renderer/Renderer.h"
#include "utilities/Builder.hpp"
#include "utilities/physics/Collisions.h"
#include "utilities/math/Pos2.hpp"
#include "utilities/physics/Direction.h"
#include "utilities/physics/TilePos.h"
#include "world/TileMap.h"
#include "world/ITile.h"




EntityManager::EntityManager()
	: m_entityID(0) 
{
	m_logger = Loggers::getLog();
	m_logger->info("Entity Manager has been initialized");
}



EntityManager::~EntityManager() 
{
	m_logger->info("Entity Manager stopped");
}



/*
 * @param	tag The entity's identification tag
 *
 * @param	builder A pointer to the entity's builder
 *
 * Registers the given Entity's builder with the Entity Manager
 */
void EntityManager::registerEntity(std::string tag, BuilderBase<IEntity>* builder)
{
	m_logger->info("Registering Entity '{0}'", tag);

	auto itr = m_entityRegistry.insert({ tag, std::unique_ptr<BuilderBase<IEntity>>(builder) });
	builder = nullptr;

	//insert returns a pair, the first element is an iterator and the second is if the insert was successful
	if (itr.second)
		m_logger->info("Entity '{0}' has been registered", tag);
	else
		m_logger->error("The Entity tag: '{0}' is not unique! The Entity's builder was not registered", tag);
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
IEntity* EntityManager::spawn(std::string tag, const Pos2D& pos, EnumSide facing)
{
	if (!m_entityRegistry.count(tag)) 
	{
		m_logger->warn("The Entity: '{0}' could not be spawned, tag is missing in registry", tag);
		return nullptr;
	}

	IEntity *entity = m_entityRegistry[tag]->build();
	m_entityList.emplace_back(std::unique_ptr<IEntity>(entity));
	entity->spwan(pos, EnumSide::RIGHT, getNextEntityID());
	return entity;
}



/*
 * Despawns all Entities that have been marked as inactive
 *
 * This will check all Entities even those that are not on screen
 * it is recommended that this method is not called each tick
 */
void EntityManager::despawn()
{
	m_logger->info("Removing all inactive Entities");
	auto itr = m_entityList.begin();
	while (itr != m_entityList.end()) 
	{
		if (!itr->get()->isActive()) 
		{
			itr->get()->onDespwan();
			itr = m_entityList.erase(itr);
		}
		else 
			itr++;
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
void EntityManager::drawAll(const TilePos& cameraPos, const Pos2N& windowSize, Renderer& renderer, bool renderAabb)
{
	std::vector<IEntity*> entitiesOnScreen;
	//TODO fix 'pop-in', currently entities will 'pop in' along the top-left edges of the screen
	this->getEntities(entitiesOnScreen, AABB(cameraPos.x(), cameraPos.y(), cameraPos.x() + windowSize.w, cameraPos.y() + windowSize.h));
	for (auto &itr : entitiesOnScreen) 
	{
		if (renderAabb) 
		{
			switch (itr->getType()) 
			{
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
			Pos2D posRect(itr->getAabb().getPos().x - cameraPos.x(), itr->getAabb().getPos().y - cameraPos.y());
			renderer.drawRect(posRect, Pos2N(itr->getAabb().widthN(), itr->getAabb().heightN()), false);
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
void EntityManager::tickAll(const TilePos& cameraPos, const Pos2N& windowSize, TileMap& worldIn, float deltaTime)
{
	std::vector<IEntity*> entitiesOnScreen;
	this->getEntities(entitiesOnScreen, AABB(cameraPos.x(), cameraPos.y(), cameraPos.x() + windowSize.w, cameraPos.y() + windowSize.h));

	for (auto &itr : entitiesOnScreen) 
	{
		if (itr->isActive()) 
		{
			itr->tick(worldIn, deltaTime);
			if (itr->canCollide())
			{
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
void EntityManager::getEntities(std::vector<IEntity*> &vectorIn, const AABB &area)
{
	for (auto &itr : m_entityList) 
	{
		if (Collision::RectVsPt(area, itr->getPos())) 
			vectorIn.emplace_back(itr.get());
	}
}



//Gets the next Entity ID and increments to the next ID
unsigned int EntityManager::getNextEntityID()
{
	return m_entityID++;
}



/*
 * @param	entities List of all Entities that are on screen
 *
 * @param	entity The subject Entity that is being tested for collisions
 *
 * Checks if the given Entity is colliding with any entity in the array
 * and if it is colliding the Entity's position will be changed
 */
void EntityManager::checkEntityCollisions(std::vector<IEntity*> &entities, IEntity &entity)
{
	for (auto &itr : entities) 
	{
		if (itr->getID() != entity.getID() && itr->isActive() && itr->canCollide()) 
		{
			//Make sure that the Entity is not being checked against itself
			EnumSide side = Collision::RectEdge(entity.getAabb(), itr->getAabb());
			if (side != EnumSide::NONE)
				entity.onEntityColision(*itr, side);
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
void EntityManager::checkTileCollisions(TileMap &worldIn, IEntity &entity)
{
	const Pos2N topLeftTile(-1, -1);

	/*
	 * The bottom-right tile is determined by the Entity's size
	 * this is done so that if an Entity is bigger than one tile the collision loop will grow to fully enclose the Entity
	 */
	Pos2N bottomRightTile(
		1 + static_cast<int>(entity.getAabb().width()/worldIn.tileWidth() + 0.5), 
		1 + static_cast<int>(entity.getAabb().height()/worldIn.tileHeight() + 0.5)
	);

	//This translates the entity's position into the tile-map unit coordinate system aka "Tile-Space"
	Pos2N entityTile(
		static_cast<int>(entity.getAabb().getPos().x/worldIn.tileWidth() + 0.5), 
		static_cast<int>(entity.getAabb().getPos().y/worldIn.tileHeight() + 0.5)
	);

	//Check if the entity collides with any of the tiles around it
	//TODO Improve performance by skipping the corner tiles as they can never be collided with
	for (int y = topLeftTile.y; y <= bottomRightTile.y; y++) 
	{
		int yCord = y + entityTile.y;

		//Skip if the y coordinate is outside of the tile-map
		if ((yCord < 0) || (yCord > worldIn.height())) 
			continue;
		for (int x = topLeftTile.x; x <= bottomRightTile.x; x++) 
		{
			int xCord = x + entityTile.x;

			//Skip if the x coordinate is outside of the tile-map
			if ((xCord < 0) || (xCord > worldIn.width())) 
				continue;

			ITile *tile = worldIn.getTile(xCord, yCord);
			if (tile == nullptr) 
			{
				//Fail safe if the above somehow does not catch the tile-map being indexed out of
				m_logger->warn("Null Pointer exception: Tried to check Tile for collisions but Tile does not exist");
				return;
			}

			if (tile->canCollide()) 
			{
				EnumSide side = Collision::RectEdge(tile->getAabb(), entity.getAabb());

				if (side != EnumSide::NONE) 
				{
					//Check if the side collided with is an "internal edge", if it is an internal edge ignore it
					//Internal edges when collided with can cause "sticky" behavior
					ITile *tile2 = worldIn.getOffsetTile(tile->getPos(), side);
					if (tile2 != nullptr && !tile2->canCollide()) 
						entity.onTileColision(*tile, side);
				}
			}
		}
	}
}








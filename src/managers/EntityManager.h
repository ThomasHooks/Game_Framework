//============================================================================
// Name       		: EntityManager.h
// Author     		: Thomas Hooks
// Last Modified	: 03/22/2020
//============================================================================




#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_




#include <vector>
#include <list>
#include <map>
#include <memory>
#include <string>

#include "Builder.h"
#include "../utilities/EnumSide.h"




class EntityManager {

public:

	EntityManager(class GameLogger *loggerptr);



	~EntityManager();



	EntityManager(const EntityManager &other) = delete;



	EntityManager(EntityManager &&other) = delete;



	/*
	 * @param	tag			The entity's identification tag
	 *
	 * @param	builder		A pointer to the entity's builder
	 *
	 * Registers the given Entity's builder with the Entity Manager
	 */
	void registerEntity(std::string tag, BuilderBase<class IEntity>* builder);



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
	class IEntity* spawn(std::string tag,
			const class Position &pos,
			EnumSide facing);



	/*
	 * Despawns all Entities that have been marked as inactive
	 *
	 * This will check all Entities even those that are not on screen
	 * it is recommended that this method is not called each tick
	 */
	void despawn();



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
	 * Draws all Entities that are visible in the Window
	 */
	void drawAll(const class Position &cameraPos,
			const struct Dimension &windowSize,
			class RendererManager &renderer,
			bool renderAabb);



	/*
	 * @param	cameraPos Coordinates of the camera
	 *
	 * @param	windowSize Size of the Window
	 *
	 * @param	deltaTime The time since the last tick
	 *
	 * @param	worldIn The current map
	 *
	 * Updates all Entities that are on screen
	 */
	void tickAll(const class Position &cameraPos,
			const struct Dimension &windowSize,
			class TileMap &worldIn,
			float deltaTime);



	/*
	 * @param	vectorIn The vector that the array of
	 * 			Entities is to be added to
	 *
	 * @param	area The area this is searched for Entities
	 *
	 * Adds a list of Entities in the given area to the
	 * vector that is passed in
	 */
	void getEntities(std::vector<class IEntity*> &vectorIn,
			const class AABB &area);



protected:

	//Gets the next Entity ID and increments to the next ID
	unsigned int getNextEntityID();



	/*
	 * @param	entities A list of all entities to check collisions against
	 *
	 * @param	entity The primary Entity to check for collisions
	 *
	 * Checks if the given Entity is colliding with any entity in the array
	 * and if it is colliding the Entity's position will be changed
	 */
	void checkEntityCollisions(std::vector<class IEntity*> &entities,
			class IEntity &entity);



	/*
	 * @param	worldIn The tile map to check the collisions against
	 *
	 * @param	entity The Entity to check for collisions
	 *
	 * Checks if the given Entity is colliding with any Tiles in the map
	 * and if it is colliding the Entity's position will be changed
	 *
	 * Entity vs Tile collision is done by creating a "collision loop"
	 * around the Entity
	 */
	void checkTileCollisions(class TileMap &worldIn,
			class IEntity &entity);



private:

	class GameLogger *logger;

	unsigned int entityID;

	std::list<std::unique_ptr<class IEntity>> entityList;

	std::map<std::string,
		std::unique_ptr<BuilderBase<class IEntity>>> entityRegistry;
};


#endif /* ENTITYMANAGER_H_ */




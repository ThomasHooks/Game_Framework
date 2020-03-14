//============================================================================
// Name       		: EntityManager.h
// Author     		: Thomas Hooks
// Last Modified	: 03/14/2020
//============================================================================




#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_




#include <vector>
#include <map>
#include <memory>
#include <string>

#include "Builder.h"




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
	 * @param	tag		The entity's identification tag
	 *
	 * @param	pos		The location the entity will be spawned
	 *
	 * @return	The ID of the new entity or -1 if the entity could not be spawned
	 *
	 * Spawns an Entity at the given coordinates
	 */
	int spawn(std::string tag, const class Position &pos);



	/*
	 * @param	id The identification of the Entity to despawn
	 *
	 * @return	True if the Entity was despawned
	 *
	 * Despawns the given Entity
	 */
	bool despawn(int id);



	/*
	 * @param	cameraPos Coordinates of the camera
	 *
	 * @param	windowSize Size of the Window
	 *
	 * @param	renderer Reference to the Renderer Manager
	 *
	 * Draws all Entities that are visible in the Window
	 */
	void drawAll(const class Position &cameraPos,
			const struct Dimension &windowSize,
			class RendererManager &renderer);



	/*
	 * @nullable
	 *
	 * @param	id The identification of the entity
	 *
	 * @return	The a pointer to the active Entity given by it's ID
	 *
	 * Gets an Entity by its ID
	 */
	class IEntity* getEntity(int id);



	int numberOfEntities(void);



private:

	class GameLogger *logger;

	std::map<int, std::unique_ptr<class IEntity>> entityMap;
	int highestEntityID;

	std::map<std::string,
		std::unique_ptr<BuilderBase<class IEntity>>> entityRegistry;
};


#endif /* ENTITYMANAGER_H_ */




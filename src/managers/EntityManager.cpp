//============================================================================
// Name       		: EntityManager.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/14/2020
//============================================================================




#include "EntityManager.h"
#include "../entities/IEntity.hpp"
#include "Builder.h"
#include "../utilities/GameLogger.h"
#include "../utilities/Dimension.h"
#include "../utilities/Position.h"
#include "../utilities/Collisions.h"
#include "RendererManager.h"




EntityManager::EntityManager(class GameLogger *loggerptr)
	: logger(loggerptr),
	  highestEntityID(0) {

	this->logger->message(Level::INFO,
					   "Entity Manager has been initialized",
					   Output::TXT_FILE);
}



EntityManager::~EntityManager() {}



void EntityManager::registerEntity(std::string tag, BuilderBase<IEntity>* builder){

	if(this->entityRegistry.find(tag) == this->entityRegistry.end()){
		//The entity tag was not found in the registry so add the entity's builder
		this->logger->message(Level::INFO,
				"Registering Entity '" + tag + "'",
				Output::TXT_FILE);

		this->entityRegistry.insert({tag, std::unique_ptr<BuilderBase<IEntity>>(builder)});

		this->logger->message(Level::INFO,
				"Entity '" + tag + "' has been registered",
				Output::TXT_FILE);
	}

	else this->logger->message(Level::ERROR,
			"The Entity tag: '" + tag + "' is not unique! The Entity's builder was not registered",
			Output::TXT_FILE);

	//This is to prevent the caller from trying to access the passed in pointer
	builder = nullptr;

	return;
}



int EntityManager::spawn(std::string tag, const Position &pos){

	const static int FAILED = -1;

	if(this->entityRegistry.find(tag) != this->entityRegistry.end()){
		//the entity tag was found in the registry so spawn the entity
		this->entityMap.insert({++this->highestEntityID, std::unique_ptr<IEntity>(this->entityRegistry[tag]->build())});
		this->entityMap[this->highestEntityID]->teleport(pos);
		return this->highestEntityID;
	}

	else {
		this->logger->message(Level::WARNING,
							  "The Entity: '" + tag + "' could not be spawned. tag is missing in registry",
							  Output::TXT_FILE);
		return FAILED;
	}
}



bool EntityManager::despawn(int id){

	if(this->entityMap.find(id) != this->entityMap.end()){
		this->entityMap.erase(id);
		return true;
	}
	else return false;
}



void EntityManager::drawAll(const Position &cameraPos, const Dimension &windowSize, RendererManager &renderer){

	auto itr = this->entityMap.begin();
	while(itr != this->entityMap.end()){

		if(Collision::RectVsPt(cameraPos, windowSize, itr->second->getPos())) {
			//Only draw the entity if it is inside of the screen
			//TODO fix, currently entities will 'pop in' along the top-left edges of the screen
			IEntity *entity = itr->second.get();
			renderer.drawSprite(entity->getRegistryTag(),
					entity->getPos(),
					cameraPos,
					entity->getSprite(),
					false);
		}
	}
}



IEntity* EntityManager::getEntity(int id){
	return this->entityMap.find(id) != this->entityMap.end() ? this->entityMap[id].get() : nullptr;
}



int EntityManager::numberOfEntities(void){
	return this->entityMap.size();
}








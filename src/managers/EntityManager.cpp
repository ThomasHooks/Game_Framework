//============================================================================
// Name       		: EntityManager.cpp
// Author     		: Thomas Hooks
// Last Modified	: 02/29/2020
//============================================================================




#include "EntityManager.h"
#include "../entities/Entity.h"
#include "Builder.h"
#include "../utilities/GameLogger.h"




EntityManager::EntityManager()
	: hasBeenInit(false),
	  logger(nullptr) {}



EntityManager::EntityManager(class GameLogger *log_ptr)
	: hasBeenInit(true),
	  logger(log_ptr) {

	this->logger->Message(Level::Info,
					   "Entity Manager has been initialized",
					   Output::File_txt);
}



EntityManager::~EntityManager() {}



void EntityManager::init(class GameLogger *log_ptr){
	/*
	 *
	 */




	if(!this->hasBeenInit){
		this->logger = log_ptr;
		this->hasBeenInit = true;
		this->logger->Message(Level::Info,
						   "Entity Manager has been initialized",
						   Output::File_txt);
	}

	return;
}



void EntityManager::registerEntity(std::string tag, BuilderBase<Entity>* builder){
	/*
	 * @brief	Registers the given Entity's builder
	 *
	 * @param	tag			The entity's identification tag
	 *
	 * @param	builder		A pointer to the entity's builder
	 */




	if(this->hasBeenInit){

		if(this->entityRegistry.find(tag) == this->entityRegistry.end()){
			//The entity tag was not found in the registry so add the entity's builder
			this->entityRegistry.insert({tag, std::unique_ptr<BuilderBase<Entity>>(builder)});	//std::move()
		}

		else this->logger->Message(Level::Error,
								"The Entity tag: '" + tag + "' is not unique! The Entity Builder was not registered",
								Output::File_txt);
	}

	else this->logger->Message(Level::Fatal,
						    "Entity Manager has not been initialized!",
						    Output::File_txt);

	//This is to prevent the caller from trying to access the passed in pointer
	builder = nullptr;

	return;
}



int EntityManager::spawn(std::string tag, Position pos){
	/*
	 *
	 */

	const static int FAILED = -1;

	return FAILED;
}








//============================================================================
// Name       		: GameCamera.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/23/2020
//============================================================================




#include "GameCamera.h"
#include "GameLogger.h"
#include "SDLWindowWrapper.h"
#include "../entities/IEntity.hpp"




GameCamera::GameCamera(GameLogger *loggerPtr, SDLWindowWrapper* windowIn)
	: logger(loggerPtr),
	  window(windowIn),
	  posOffset(),
	  posTract(),
	  entity(nullptr),
	  tractingEntity(false) {

	logger->message(Level::INFO, "Camera has been built", Output::TXT_FILE);
}



GameCamera::~GameCamera() {
	logger->message(Level::INFO, "Camera has been removed", Output::TXT_FILE);
}



/*
 * @return	The current position of the camera
 *
 * Gets the current position of the camera
 */
const Position& GameCamera::getPos() const {
	return this->posOffset;
}



/*
 * @param	worldSize The size of the current World in Global-Space
 *
 * Updates the camera's position in the Global-Space coordinate system
 * This should be called every game tick
 */
void GameCamera::updatePos(const Dimension &worldSize, float deltaTime, bool keepInsideWindow){

	double xOffset = this->posTract.xPos() - window->getWidth()/2.0;
	double yOffset = this->posTract.yPos() - window->getHeight()/2.0;

	if(keepInsideWindow){
		if(xOffset < 0) xOffset = 0.0;
		else if(xOffset > worldSize.width - window->getWidth()) xOffset = worldSize.width - window->getWidth();

		if(yOffset < 0) yOffset = 0.0;
		else if(yOffset > worldSize.height - window->getHeight()) yOffset = worldSize.height - window->getHeight();
	}

	this->posOffset.move(xOffset, yOffset);
}



/*
 * @param	entityIn The Entity that the camera is to track
 *
 * Sets the camera to track the given Entity
 */
void GameCamera::trackEntity(IEntity *entityIn){

	if(entityIn != nullptr){
		this->entity = entityIn;
		this->tractingEntity = true;
		this->posTract.move(entityIn->getPos());
		logger->message(Level::INFO, "Camera is tracking Entity '" + entityIn->getRegistryTag() + "'", Output::TXT_FILE);
	}
	else logger->message(Level::WARNING, "Null Pointer exception: Camera cannot track Entity!", Output::TXT_FILE);
}



/*
 * @param	posIn The position that the camera is to track
 *
 * Sets the camera to track the given position
 */
void GameCamera::trackPos(const Position &posIn){

	if(this->entity != nullptr) {
		logger->message(Level::INFO, "Camera has stopped tracking Entity '" + this->entity->getRegistryTag() + "'", Output::TXT_FILE);
		this->entity = nullptr;
	}
	this->tractingEntity = false;
	this->posTract.move(posIn);
}








//============================================================================
// Name       		: GameCamera.cpp
// Author     		: Thomas Hooks
// Last Modified	: 04/04/2020
//============================================================================




#include "GameCamera.h"
#include "../entities/IEntity.hpp"
#include "Logger.h"
#include "wrappers/SDLWindowWrapper.h"




GameCamera::GameCamera(Logger *loggerPtr, SDLWindowWrapper* windowIn)
	: logger(loggerPtr),
	  window(windowIn),
	  posOffset(),
	  posTract(),
	  entity(nullptr),
	  trackingEntity(false) {

	logger->message(Logger::Level::INFO, "Camera has been built", Logger::Output::TXT_FILE);
}



GameCamera::~GameCamera() {
	logger->message(Logger::Level::INFO, "Camera has been removed", Logger::Output::TXT_FILE);
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
 * @return	The width of the camera
 *
 * Gets the width of the camera which will also be the screen width
 */
int GameCamera::width() const {
	return this->window->width();
}



/*
 * @return	The height of the camera
 *
 * Gets the height of the camera which will also be the screen height
 */
int GameCamera::height() const {
	return this->window->height();
}



/*
 * @param	worldSize The size of the current World in Global-Space
 *
 * @param	keepInsideWindow Flag if the camera should stay in the window
 *
 * Updates the camera's position in the Global-Space coordinate system
 * This should be called every game tick
 */
void GameCamera::updatePos(const Dimension &worldSize, bool keepInsideWindow){

	if(this->trackingEntity) {
		//Update the Camera's tracking position to the Entity's current position
		this->posTract.move(this->entity->getPos());
	}
	double xOffset = this->posTract.xPos() - window->width()/2.0;
	double yOffset = this->posTract.yPos() - window->height()/2.0;

	if(keepInsideWindow) {
		if(xOffset < 0) xOffset = 0.0;
		else if(xOffset > worldSize.width - window->width()) xOffset = worldSize.width - window->width();

		if(yOffset < 0) yOffset = 0.0;
		else if(yOffset > worldSize.height - window->height()) yOffset = worldSize.height - window->height();
	}

	this->posOffset.move(xOffset, yOffset);
}



/*
 * @param	entityIn The Entity that the camera is to track
 *
 * Sets the camera to track the given Entity
 */
void GameCamera::trackEntity(IEntity *entityIn){

	if(entityIn != nullptr) {
		this->entity = entityIn;
		this->trackingEntity = true;
		this->posTract.move(entityIn->getPos());
		logger->message(Logger::Level::INFO, "Camera is tracking Entity '" + entityIn->getRegistryTag() + "'", Logger::Output::TXT_FILE);
	}
	else logger->message(Logger::Level::WARNING, "Null Pointer exception: Camera cannot track Entity!", Logger::Output::TXT_FILE);
}



/*
 * @param	posIn The position that the camera is to track
 *
 * Sets the camera to track the given position
 */
void GameCamera::trackPos(const Position &posIn){

	if(this->entity != nullptr) {
		logger->message(Logger::Level::INFO, "Camera has stopped tracking Entity '" + this->entity->getRegistryTag() + "'", Logger::Output::TXT_FILE);
		this->entity = nullptr;
	}
	this->trackingEntity = false;
	this->posTract.move(posIn);
}








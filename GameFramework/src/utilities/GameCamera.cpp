#include "GameCamera.h"
#include "../entities/IEntity.hpp"
#include "wrappers/SDLWindowWrapper.h"




GameCamera::GameCamera(SDLWindowWrapper* windowIn)
	: window(windowIn), posOffset(), posTract(), entity(nullptr), trackingEntity(false) 
{
	m_logger = Loggers::getLog();
	m_logger->info("Camera has been built");
}



GameCamera::~GameCamera() 
{
	m_logger->info("Camera has been removed");
}



/*
 * @return	The current position of the camera
 *
 * Gets the current position of the camera
 */
const Position& GameCamera::getPos() const 
{
	return this->posOffset;
}



/*
 * @return	The width of the camera
 *
 * Gets the width of the camera which will also be the screen width
 */
int GameCamera::width() const 
{
	return this->window->width();
}



/*
 * @return	The height of the camera
 *
 * Gets the height of the camera which will also be the screen height
 */
int GameCamera::height() const 
{
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
void GameCamera::updatePos(const Dimension &worldSize, bool keepInsideWindow)
{
	if (this->trackingEntity) 
	{
		//Update the Camera's tracking position to the Entity's current position
		this->posTract.move(this->entity->getPos());
	}
	double xOffset = this->posTract.xPos() - window->width()/2.0;
	double yOffset = this->posTract.yPos() - window->height()/2.0;

	if (keepInsideWindow) 
	{
		if(xOffset < 0) 
			xOffset = 0.0;
		else if(xOffset > worldSize.width - window->width()) 
			xOffset = worldSize.width - window->width();

		if(yOffset < 0) 
			yOffset = 0.0;
		else if(yOffset > worldSize.height - window->height()) 
			yOffset = worldSize.height - window->height();
	}

	this->posOffset.move(xOffset, yOffset);
}



/*
 * @param	entityIn The Entity that the camera is to track
 *
 * Sets the camera to track the given Entity
 */
void GameCamera::trackEntity(IEntity *entityIn)
{
	if (entityIn != nullptr) 
	{
		this->entity = entityIn;
		this->trackingEntity = true;
		this->posTract.move(entityIn->getPos());
		m_logger->info("Camera is tracking Entity '{0}'", entityIn->getRegistryTag());
	}
	else 
		m_logger->warn("Null Pointer exception: Camera cannot track Entity!");
}



/*
 * @param	posIn The position that the camera is to track
 *
 * Sets the camera to track the given position
 */
void GameCamera::trackPos(const Position &posIn)
{
	if (this->entity != nullptr) 
	{
		m_logger->info("Camera has stopped tracking Entity '{0}'", this->entity->getRegistryTag());
		this->entity = nullptr;
	}
	this->trackingEntity = false;
	this->posTract.move(posIn);
}








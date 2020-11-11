#include "GameCamera.h"
#include "entities/IEntity.hpp"
#include "wrappers/SDLWindowWrapper.h"




GameCamera::GameCamera(SDLWindowWrapper* windowIn)
	: m_window(windowIn), m_posOffset(), m_posTract(), m_entityPtr(nullptr)
{
	m_logger = Loggers::getLog();
	m_logger->info("Camera has been built");
}



GameCamera::~GameCamera() 
{
	m_logger->info("Camera has been removed");
}



/*
 * @return	The width of the camera
 *
 * Gets the width of the camera which will also be the screen width
 */
int GameCamera::width() const 
{
	return m_window->width();
}



/*
 * @return	The height of the camera
 *
 * Gets the height of the camera which will also be the screen height
 */
int GameCamera::height() const 
{
	return m_window->height();
}



/*
 * @param	worldSize The size of the current World in Global-Space
 *
 * @param	keepInsideWindow Flag if the camera should stay in the window
 *
 * Updates the camera's position in the Global-Space coordinate system
 * This should be called every game tick
 */
void GameCamera::updatePos(const Pos2N& worldSize, bool keepInsideWindow)
{
	if (m_isTrackingEntity) 
	{
		//Update the Camera's tracking position to the Entity's current position
		m_posTract.set(m_entityPtr->getPos().x(), m_entityPtr->getPos().y());
	}
	double xOffset = m_posTract.x() - m_window->width()/2.0;
	double yOffset = m_posTract.y() - m_window->height()/2.0;

	if (keepInsideWindow) 
	{
		if(xOffset < 0) 
			xOffset = 0.0;
		else if(xOffset > static_cast<double>(worldSize.w) - static_cast<double>(m_window->width()))
			xOffset = static_cast<double>(worldSize.w) - static_cast<double>(m_window->width());

		if(yOffset < 0) 
			yOffset = 0.0;
		else if(yOffset > static_cast<double>(worldSize.h) - static_cast<double>(m_window->height()))
			yOffset = static_cast<double>(worldSize.h) - static_cast<double>(m_window->height());
	}

	m_posOffset.set(xOffset, yOffset);
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
		m_entityPtr = entityIn;
		m_isTrackingEntity = true;
		m_posTract.set(entityIn->getPos().x(), entityIn->getPos().y());
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
void GameCamera::trackPos(const TilePos& posIn)
{
	if (m_entityPtr != nullptr)
	{
		m_logger->info("Camera has stopped tracking Entity '{0}'", m_entityPtr->getRegistryTag());
		m_entityPtr = nullptr;
	}
	m_isTrackingEntity = false;
	m_posTract.set(posIn.x(), posIn.y());
}








#ifndef GAMECAMERA_H_
#define GAMECAMERA_H_


#include "utilities/physics/TilePos.h"
#include "utilities/math/Pos2.hpp"
#include "utilities/Loggers.hpp"




class GameCamera 
{
public:

	GameCamera(class SDLWindowWrapper* windowIn);



	virtual ~GameCamera();



	/*
	 * @return	The current position of the camera
	 *
	 * Gets the current position of the camera
	 */
	const TilePos& getPos() const { return m_posOffset; }



	/*
	 * @return	The width of the camera
	 *
	 * Gets the width of the camera which will also be the Window width
	 */
	int width() const;



	/*
	 * @return	The height of the camera
	 *
	 * Gets the height of the camera which will also be the Window height
	 */
	int height() const;



	/*
	 * @param	worldSize The size of the current World in Global-Space
	 *
	 * @param	keepInsideWindow Flag if the camera should stay in the window
	 *
	 * Updates the camera's position in the Global-Space coordinate system
	 * This should be called every game tick
	 */
	void updatePos(const Pos2N &worldSize, bool keepInsideWindow);



	/*
	 * @param	entityIn The Entity that the camera is to track
	 *
	 * Sets the camera to track the given Entity
	 */
	void trackEntity(class IEntity *entityIn);



	/*
	 * @param	posIn The position that the camera is to track
	 *
	 * Sets the camera to track the given position
	 */
	void trackPos(const TilePos& posIn);



protected:

	class SDLWindowWrapper *m_window;



private:

	std::shared_ptr<spdlog::logger> m_logger;

	TilePos m_posOffset;

	TilePos m_posTract;

	class IEntity *m_entityPtr;

	bool m_isTrackingEntity = false;
};


#endif




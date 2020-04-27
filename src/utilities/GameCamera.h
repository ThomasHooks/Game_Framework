//============================================================================
// Name       		: GameCamera.h
// Author     		: Thomas Hooks
// Last Modified	: 04/04/2020
//============================================================================



#ifndef GAMECAMERA_H_
#define GAMECAMERA_H_


#include "physics/Position.h"


class GameCamera {

public:

	GameCamera(class Logger *loggerPtr, class SDLWindowWrapper* windowIn);



	virtual ~GameCamera();



	/*
	 * @return	The current position of the camera
	 *
	 * Gets the current position of the camera
	 */
	const Position& getPos() const;



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
	void updatePos(const class Dimension &worldSize, bool keepInsideWindow);



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
	void trackPos(const Position &posIn);



protected:

	class Logger *logger;

	class SDLWindowWrapper *window;



private:

	Position posOffset;

	Position posTract;

	class IEntity *entity;

	bool trackingEntity;
};


#endif /* GAMECAMERA_H_ */




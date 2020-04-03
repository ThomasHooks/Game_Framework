//============================================================================
// Name       		: GameCamera.h
// Author     		: Thomas Hooks
// Last Modified	: 03/29/2020
//============================================================================



#ifndef GAMECAMERA_H_
#define GAMECAMERA_H_


#include "Position.h"


class GameCamera {

public:

	GameCamera(class GameLogger *loggerPtr, class SDLWindowWrapper* windowIn);



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
	 * Updates the camera's position in the Global-Space coordinate system
	 * This should be called every game tick
	 */
	void updatePos(const class Dimension &worldSize,
			float deltaTime,
			bool keepInsideWindow);



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

	class GameLogger *logger;

	class SDLWindowWrapper *window;



private:

	Position posOffset;

	Position posTract;

	class IEntity *entity;

	bool trackingEntity;
};


#endif /* GAMECAMERA_H_ */



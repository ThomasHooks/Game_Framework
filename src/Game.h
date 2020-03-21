//============================================================================
// Name       		: Game.h
// Author     		: Thomas Hooks
// Last Modified	: 03/20/2020
//============================================================================




#ifndef GAME_H_
#define GAME_H_




#include <SDL.h>

#include "managers/RendererManager.h"
#include "managers/MapManager.h"
#include "managers/StateManager.h"
#include "utilities/GameLogger.h"
#include "utilities/GameTimer.h"
#include "managers/EntityManager.h"




class Game {

public:

	/*
	 * Default constructor, game will need to be initialized by calling init
	 */
	Game();



	/*
	 * @param	title The title of the window
	 *
	 * @param	Window_Height The height of the window measured in pixels
	 *
	 * @param 	Window_Width The width of the window measured in pixels
	 *
	 * @param 	flag The flags for the window, mask of any of the following:
	 *          see "https://wiki.libsdl.org/SDL_WindowFlags" for window flags
	 *
	 * Constructor for the game framework that create a window defined by the caller
	 */
	Game(const char * title, int Window_Height, int Window_Width, Uint32 flags, int Max_FPS);



	~Game();



	/*
	 * @param	title The title of the window
	 *
	 * @param	Window_Height The height of the window measured in pixels
	 *
	 * @param 	Window_Width The width of the window measured in pixels
	 *
	 * @param 	flag The flags for the window, mask of any of the following:
	 *          see "https://wiki.libsdl.org/SDL_WindowFlags" for window flags
	 *
	 * @param	Max_FPS The maximum frames per second
	 *
	 * initializes the Window and sets the frames per second limit
	 */
	bool init(const char * title, int Window_Height, int Window_Width, Uint32 flags, int Max_FPS);



	/*
	 *
	 */
	void run();



	GameLogger Log;



	RendererManager Render;



	StateManager State;



	MapManager Map;



	EntityManager Entities;



	GameTimer Timer;



	bool get_gameOver() const {return b_gameOver;}



	void set_gameOver(bool flag) {b_gameOver = flag;}



	int get_maxFPS() const {return n_maxFPS;}



	void set_maxFPS(int Max_FPS) {if(Max_FPS != 0) n_maxFPS = Max_FPS;}



	int get_windowHeight() const {return WindowHeight;}



	void set_windowHeight(int height) {WindowHeight = height;}



	int get_windowWidth() const {return WindowWidth;}



	void set_windowWidth(int width) {WindowWidth = width;}



	SDL_Window* get_window() {return window;}



	float get_cameraX() const {return f_cameraX;}



	void set_cameraX(float positionX) {f_cameraX = positionX;}



	float get_cameraY(void) const {return f_cameraY;}



	void set_cameraY(float positionY) {f_cameraY = positionY;}



private:

	bool b_gameOver;
	bool b_hasBeenInit;

	//Coordinates of camera's top left corner
	float f_cameraX;
	float f_cameraY;

	int n_maxFPS;

	SDL_Window *window;
	//SDL_Renderer *renderer;

	int WindowHeight;
	int WindowWidth;
};




#endif /* GAME_H_ */








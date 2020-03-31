//============================================================================
// Name       		: Game.h
// Author     		: Thomas Hooks
// Last Modified	: 03/30/2020
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
	Game(const std::string &titleIn, int windowHeight, int windowWidth, uint32_t flags, int MaxFPS);



	~Game();



	/*
	 * @param	titleIn The title of the window
	 *
	 * @param	widthIn The width of the window measured in pixels
	 *
	 * @param	heightIn The height of the window measured in pixels
	 *
	 * @param	flags The flags for the window, mask of any of the following:
	 *				::SDL_WINDOW_FULLSCREEN,    ::SDL_WINDOW_OPENGL,
	 *              ::SDL_WINDOW_HIDDEN,        ::SDL_WINDOW_BORDERLESS,
	 *              ::SDL_WINDOW_RESIZABLE,     ::SDL_WINDOW_MAXIMIZED,
	 *              ::SDL_WINDOW_MINIMIZED,     ::SDL_WINDOW_INPUT_GRABBED,
	 *              ::SDL_WINDOW_ALLOW_HIGHDPI, ::SDL_WINDOW_VULKAN.
	 *    	  	see "https://wiki.libsdl.org/SDL_WindowFlags" for window flags
	 *
	 * Initializes the Window
	 */
	void initWindow(const std::string &title, int Window_Height, int Window_Width, uint32_t flags);



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



//	bool get_gameOver() const {return gameOver;}
//
//
//
//	void set_gameOver(bool flag) {gameOver = flag;}



	//Checks if the game has ended
	bool isOver() const;



	//Marks the game to be stopped
	void markOver();



	int get_maxFPS() const {return n_maxFPS;}



	void set_maxFPS(int Max_FPS) {if(Max_FPS != 0) n_maxFPS = Max_FPS;}



	/*
	 * @nullable
	 *
	 * @return	The wrapper for this game's Window
	 *
	 * Gets this game's Window
	 */
	const class SDLWindowWrapper* getWindow() const;



	/*
	 * @nullable
	 *
	 * @return	The wrapper for this game's camera
	 *
	 * Gets this game's Camera
	 */
	class GameCamera* getCamera();



private:

	std::unique_ptr<class SDLWindowWrapper> windowWrap;

	std::unique_ptr<class GameCamera> cameraWrap;

	bool gameOver;

	bool hasBeenInit;

	int n_maxFPS;
};


#endif /* GAME_H_ */




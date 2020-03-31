//============================================================================
// Name       		: Game.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/30/2020
//============================================================================




#include <SDL.h>

#include "Game.h"

#include "gamestates/BlankGameState.h"
#include "gamestates/IGameState.h"
#include "managers/StateManager.h"
#include "utilities/SDLWindowWrapper.h"
#include "utilities/GameCamera.h"




/*
 * Default constructor, game will need to be initialized by calling init
 */
Game::Game()
		: Log(Level::TRACE),
		  Render(&Log),
		  State(this),
		  Map(&Log),
		  Entities(&Log),
		  Timer(),
		  gameOver(false),
		  hasBeenInit(false),
		  n_maxFPS(60) {

	Log.message(Level::INFO, "Initializing SDL", Output::TXT_FILE);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	const int startingStateID = 0;
	State.Push(new BlankGameState(this, startingStateID));
}



/*
 * @param	title  				The title of the window
 *
 * @param	Window_Height		The height of the window measured in pixels
 *
 * @param 	Window_Width		The width of the window measured in pixels
 *
 * @param 	flag				The flags for the window, mask of any of the following:
 *               				::SDL_WINDOW_FULLSCREEN,    ::SDL_WINDOW_OPENGL,
 *               				::SDL_WINDOW_HIDDEN,        ::SDL_WINDOW_BORDERLESS,
 *               				::SDL_WINDOW_RESIZABLE,     ::SDL_WINDOW_MAXIMIZED,
 *               				::SDL_WINDOW_MINIMIZED,     ::SDL_WINDOW_INPUT_GRABBED,
 *               				::SDL_WINDOW_ALLOW_HIGHDPI, ::SDL_WINDOW_VULKAN.
 *
 *               			See "https://wiki.libsdl.org/SDL_WindowFlags" for more window flags
 *
 *
 * Constructor for the game engine class that create a window defined by the caller, and sets SDL flags
 */
Game::Game(const std::string &titleIn, int windowHeight, int windowWidth, uint32_t flags, int MaxFPS)
		: Log(Level::TRACE),
		  Render(&Log),
		  State(this),
		  Map(&Log),
		  Entities(&Log),
		  Timer(),
		  gameOver(false),
		  hasBeenInit(false),
		  n_maxFPS(MaxFPS) {

	//Start SDL2
	Log.message(Level::INFO, "Initializing SDL Video and Audio", Output::TXT_FILE);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	this->initWindow(titleIn, windowWidth, windowHeight, flags);

	const int INITSTATEID = 0;
	State.Push(new BlankGameState(this, INITSTATEID));
}



Game::~Game(){

	Log.message(Level::INFO, "Terminating SDL", Output::TXT_FILE);
	SDL_Quit();
}



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
void Game::initWindow(const std::string &titleIn, int widthIn, int heightIn, uint32_t flags){

	if (!this->hasBeenInit){

		this->windowWrap = std::make_unique<SDLWindowWrapper>(&this->Log, titleIn, Dimension(widthIn, heightIn), flags);
		this->Render.init(this->windowWrap->get());
		this->cameraWrap = std::make_unique<GameCamera>(&this->Log, this->windowWrap.get());
		this->hasBeenInit = true;
	}
}



/*
 *
 */
void Game::run(){

	if (hasBeenInit){
		while(!this->isOver()){

			//Update current time in (ms)
			Timer.Start();

			//Update the current game state
			State.Process();

			//Check if the current game state needs to be change
			State.Check();

			//Check the frame rate and limit if necessary
			Timer.Check(get_maxFPS());
		}
	}

	else {
		Log.message(Level::FATAL, "Object Game has not been initialized", Output::TXT_FILE);
		this->markOver();
	}

	return;
}



//Checks if the game has ended
bool Game::isOver() const {
	return this->gameOver;
}



//Marks the game to be stopped
void Game::markOver(){
	this->gameOver = true;
}



/*
 * @nullable
 *
 * @return	The wrapper for this game's Window
 *
 * Gets this game's Window
 */
const class SDLWindowWrapper* Game::getWindow() const {
	return this->windowWrap.get();
}



/*
 * @nullable
 *
 * @return	The wrapper for this game's camera
 *
 * Gets this game's Camera
 */
class GameCamera* Game::getCamera(){
	return this->cameraWrap.get();
}








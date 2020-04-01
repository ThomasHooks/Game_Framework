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
#include "managers/RendererManager.h"
#include "managers/EntityManager.h"
#include "managers/MapManager.h"
#include "utilities/GameLogger.h"
#include "utilities/SDLWindowWrapper.h"
#include "utilities/GameCamera.h"
#include "utilities/GameTimer.h"




Game::Game()
		: State(this),
		  gameOver(false),
		  hasBeenInit(false),
		  n_maxFPS(60) {

	this->logger = std::make_unique<GameLogger>(Level::TRACE);
	this->renderManager = std::make_unique<RendererManager>(this->logger.get());
	this->worldManager = std::make_unique<MapManager>(this->logger.get());
	this->entityManager = std::make_unique<EntityManager>(this->logger.get());
	this->timer = std::make_unique<GameTimer>();

	getLogger().message(Level::INFO, "Initializing SDL", Output::TXT_FILE);
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
		: State(this),
		  gameOver(false),
		  hasBeenInit(false),
		  n_maxFPS(MaxFPS) {

	this->logger = std::make_unique<GameLogger>(Level::TRACE);
	this->renderManager = std::make_unique<RendererManager>(this->logger.get());
	this->worldManager = std::make_unique<MapManager>(this->logger.get());
	this->entityManager = std::make_unique<EntityManager>(this->logger.get());
	this->timer = std::make_unique<GameTimer>();

	getLogger().message(Level::INFO, "Initializing SDL Video and Audio", Output::TXT_FILE);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	this->initWindow(titleIn, windowWidth, windowHeight, flags);

	const int INITSTATEID = 0;
	State.Push(new BlankGameState(this, INITSTATEID));
}



Game::~Game(){

	getLogger().message(Level::INFO, "Terminating SDL", Output::TXT_FILE);
	SDL_Quit();
}



/*
 * @param	titleIn The title of the window
 *
 * @param	widthIn The width of the window measured in pixels
 *
 * @param	heightIn The height of the window measured in pixels
 *
 * @param	flags The flags for the window, OR any of the following:
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

		this->windowWrap = std::make_unique<SDLWindowWrapper>(this->logger.get(), titleIn, Dimension(widthIn, heightIn), flags);
		this->getRenderManager().init(this->windowWrap->get());
		this->cameraWrap = std::make_unique<GameCamera>(this->logger.get(), this->windowWrap.get());
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
			getTimer().Start();

			//Update the current game state
			State.Process();

			//Check if the current game state needs to be change
			State.Check();

			//Check the frame rate and limit if necessary
			getTimer().Check(get_maxFPS());
		}
	}

	else {
		getLogger().message(Level::FATAL, "Game has not been initialized", Output::TXT_FILE);
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
	logger->message(Level::INFO, "Quitting Game", Output::TXT_FILE);
	this->gameOver = true;
}



//Gets this game's logger
GameLogger& Game::getLogger(){
	return *this->logger.get();
}



//Gets this game's renderer
RendererManager& Game::getRenderManager(){
	return *this->renderManager.get();
}



//Gets this game's world manager
MapManager& Game::getWorldManager(){
	return *this->worldManager.get();
}



//Gets this game's entity manager
EntityManager& Game::getEntityManager(){
	return *this->entityManager.get();
}



//Gets this game's timer
GameTimer& Game::getTimer(){
	return *this->timer.get();
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








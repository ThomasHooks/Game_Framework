//============================================================================
// Name       		: Game.cpp
// Author     		: Thomas Hooks
// Last Modified	: 04/05/2020
//============================================================================




#include <SDL.h>

#include "Game.h"
#include "gamestates/BlankGameState.h"
#include "gamestates/IGameState.h"
#include "managers/RendererManager.h"
#include "managers/EntityManager.h"
#include "managers/MapManager.h"
#include "managers/AudioManager.h"
#include "world/TileMap.h"
#include "utilities/GameLogger.h"
#include "utilities/GameCamera.h"
#include "utilities/GameTimer.h"
#include "utilities/GameBuilder.h"
#include "utilities/wrappers/SDLWindowWrapper.h"




Game::Game()
		: gameOver(false),
		  hasBeenInit(false),
		  tickRate(50) {

	this->logger = std::make_unique<GameLogger>(EnumLogLevel::TRACE);
	this->renderManager = std::make_unique<RendererManager>(this->logger.get());
	this->audioManager = std::make_unique<AudioManager>(this->logger.get());
	this->worldManager = std::make_unique<MapManager>(this->logger.get());
	this->entityManager = std::make_unique<EntityManager>(this->logger.get());
	this->timer = std::make_unique<GameTimer>();

	getLogger().message(EnumLogLevel::INFO, "Initializing SDL", EnumLogOutput::TXT_FILE);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	getMixer().init();

	const int startingStateID = 0;
	addState(new BlankGameState(this, startingStateID));
}



/*
 * @param	titleIn The title of the window
 *
 * @param	windowHeight The height of the window measured in pixels
 *
 * @param 	windowWidth The width of the window measured in pixels
 *
 * @param 	flag The flags for the window, mask of any of the following:
 *               ::SDL_WINDOW_FULLSCREEN,    ::SDL_WINDOW_OPENGL,
 *               ::SDL_WINDOW_HIDDEN,        ::SDL_WINDOW_BORDERLESS,
 *               ::SDL_WINDOW_RESIZABLE,     ::SDL_WINDOW_MAXIMIZED,
 *               ::SDL_WINDOW_MINIMIZED,     ::SDL_WINDOW_INPUT_GRABBED,
 *               ::SDL_WINDOW_ALLOW_HIGHDPI, ::SDL_WINDOW_VULKAN.
 *
 *               See "https://wiki.libsdl.org/SDL_WindowFlags" for more window flags
 *
 *
 * Constructor for the game engine class that create a window defined by the caller, and sets SDL flags
 */
Game::Game(const std::string &titleIn, int windowHeight, int windowWidth, uint32_t flags, int MaxFPS)
		: gameOver(false),
		  hasBeenInit(false),
		  tickRate(20) {

	this->logger = std::make_unique<GameLogger>(EnumLogLevel::TRACE);
	this->renderManager = std::make_unique<RendererManager>(this->logger.get());
	this->audioManager = std::make_unique<AudioManager>(this->logger.get());
	this->worldManager = std::make_unique<MapManager>(this->logger.get());
	this->entityManager = std::make_unique<EntityManager>(this->logger.get());
	this->timer = std::make_unique<GameTimer>();

	getLogger().message(EnumLogLevel::INFO, "Initializing SDL Video and Audio", EnumLogOutput::TXT_FILE);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	initWindow(titleIn, windowWidth, windowHeight, flags);
	getMixer().init();

	const int INITSTATEID = 0;
	addState(new BlankGameState(this, INITSTATEID));
}



Game::~Game() {

	getLogger().message(EnumLogLevel::INFO, "Terminating SDL", EnumLogOutput::TXT_FILE);
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
void Game::initWindow(const std::string &titleIn, int widthIn, int heightIn, uint32_t flags) {

	if (!this->hasBeenInit) {

		this->windowWrap = std::make_unique<SDLWindowWrapper>(this->logger.get(), titleIn, Dimension(widthIn, heightIn), flags);
		this->getRenderManager().init(this->windowWrap->get());
		this->cameraWrap = std::make_unique<GameCamera>(this->logger.get(), this->windowWrap.get());
		this->hasBeenInit = true;
	}
}



/*
 * Starts the game loop
 * which will continue running until Game::markOver is called
 */
void Game::run() {

	if (!hasBeenInit) {
		getLogger().message(EnumLogLevel::FATAL, "Game has not been initialized", EnumLogOutput::TXT_FILE);
		markOver();
	}

	getTimer().start();
	while(!this->isOver() && !this->isNullState()) {

		TileMap* world = getWorldManager().getWorld();
		if(world == nullptr) {
			getLogger().message(EnumLogLevel::FATAL, "Null Pointer exception: Tried to get a null World!", EnumLogOutput::TXT_FILE);
			markOver();
		}
		else {
			Dimension worldSize(world->width() * world->tileWidth(), world->height() * world->tileHeight());
			getCamera()->updatePos(worldSize, true);

			getState().render(*getCamera());

			getState().onInputEvent();

			if(getTimer().getTicks() >= this->tickRate) {
				getState().tick(*getCamera(), *world, getTimer().getDelta());
				getState().ChangeState(0, this);
				getTimer().start();
			}
		}
	}
}



/*
 * @param	stateIn A pointer to the new Game State
 *
 * Adds a new Game State to this Game
 */
void Game::addState(IGameState* stateIn) {

	if(stateIn == nullptr){
		logger->message(EnumLogLevel::ERROR, "Null Pointer exception: Tried to add a null State!", EnumLogOutput::TXT_FILE);
		return;
	}
	this->states.emplace_back(std::unique_ptr<IGameState>(stateIn));
	//This is done to prevent the user from trying to access the pointer
	//Or from trying to free the pointer after they passed it
	stateIn = nullptr;
}



//Removes the current Game State
void Game::removeState() {

	if(this->states.empty()) {
		logger->message(EnumLogLevel::WARNING, "Tried to remove State but there are none!", EnumLogOutput::TXT_FILE);
		return;
	}
	this->states.pop_back();
}



// @return	True if the game has ended
bool Game::isOver() const {
	return this->gameOver;
}



//Marks the game to be stopped
void Game::markOver() {
	logger->message(EnumLogLevel::INFO, "Quitting Game", EnumLogOutput::TXT_FILE);
	this->gameOver = true;
}



// @return	Gets this game's logger
GameLogger& Game::getLogger() {
	return *this->logger.get();
}



// @return	Gets this game's renderer
RendererManager& Game::getRenderManager() {
	return *this->renderManager.get();
}



// @return	Gets this game's audio manager
AudioManager& Game::getMixer() {
	return *this->audioManager.get();
}



// @return	Gets this game's world manager
MapManager& Game::getWorldManager() {
	return *this->worldManager.get();
}



// @return	Gets this game's entity manager
EntityManager& Game::getEntityManager() {
	return *this->entityManager.get();
}



// @return	Gets this game's timer
GameTimer& Game::getTimer() {
	return *this->timer.get();
}



/*
 * @nullable
 *
 * @return	Gets this game's Window
 */
const class SDLWindowWrapper* Game::getWindow() const {
	return this->windowWrap.get();
}



/*
 * @nullable
 *
 * @return	Gets this game's CameraGets this game's Camera
 */
class GameCamera* Game::getCamera() {
	return this->cameraWrap.get();
}



// @return	Gets the current Game State
class IGameState& Game::getState() {
	return *this->states.back().get();
}



// @return	True if the Game State stack is empty
bool Game::isNullState() const {
	if(this->states.empty()) {
		logger->message(EnumLogLevel::FATAL, "Game is in an unknown state!", EnumLogOutput::TXT_FILE);
		return true;
	}
	else return false;
}








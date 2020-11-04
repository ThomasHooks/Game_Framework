#include <SDL.h>

#include "Game.hpp"
#include "events/EventBus.hpp"
#include "events/WindowEvent.hpp"
#include "events/KeyboardEvent.hpp"
#include "audiomixer/AudioMixer.h"
#include "entities/EntityManager.h"
#include "gamestates/BlankGameState.h"
#include "gamestates/IGameState.h"
#include "renderer/Renderer.h"
#include "world/TileMap.h"
#include "utilities/GameCamera.h"
#include "utilities/GameTimer.h"
#include "utilities/GameBuilder.h"
#include "utilities/Logger.h"
#include "utilities/wrappers/SDLWindowWrapper.h"
#include "world/WorldStack.h"




Game::Game(const std::string &titleIn, int windowHeight, int windowWidth, uint32_t flags, int MaxFPS)
		: gameOver(false), hasBeenInit(false), tickRate(20) 
{
	this->logger = std::make_unique<Logger>(Logger::Level::TRACE);
	this->renderer = std::make_unique<Renderer>(this->logger.get());
	this->audioManager = std::make_unique<AudioMixer>(this->logger.get());
	this->worlds = std::make_unique<WorldStack>(this->logger.get());
	this->entityManager = std::make_unique<EntityManager>(this->logger.get());
	this->timer = std::make_unique<GameTimer>();

	getLogger().message(Logger::Level::INFO, "Initializing SDL Video and Audio", Logger::Output::TXT_FILE);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	initWindow(titleIn, windowWidth, windowHeight, flags);
	getMixer().init();

	m_onWindowEvent = EventBus::subscribe<WindowEvent>([this](const WindowEvent& e)
		{
			switch (e.action())
			{
			case WindowEvent::Action::CLOSE:
				this->markOver();
				break;

			default:
				break;
			}
		});

	EventBus::subscribe<KeyboardEvent>([this](const KeyboardEvent& e)
		{
			switch (e.action())
			{
			case KeyboardEvent::Action::PRESS:
				this->getLogger().message(Logger::Level::INFO, "Key pressed: " + std::to_string(e.getKeyCode()), Logger::Output::CONSOLE);
				break;

			case KeyboardEvent::Action::RELEASE:
				this->getLogger().message(Logger::Level::INFO, "Key release: " + std::to_string(e.getKeyCode()), Logger::Output::CONSOLE);
				break;

			case KeyboardEvent::Action::REPEAT:
				this->getLogger().message(Logger::Level::INFO, "Key repeat: " + std::to_string(e.getKeyCode()), Logger::Output::CONSOLE);
				break;

			default:
				break;
			}
		});

	const int INITSTATEID = 0;
	addState(new BlankGameState(this, INITSTATEID));
}



Game::~Game() 
{
	EventBus::unsubscribe<WindowEvent>(m_onWindowEvent);
	getLogger().message(Logger::Level::INFO, "Terminating SDL", Logger::Output::TXT_FILE);
	SDL_Quit();
}



void Game::initWindow(const std::string &titleIn, int widthIn, int heightIn, uint32_t flags) 
{
	if (!this->hasBeenInit) 
	{
		this->windowWrap = std::make_unique<SDLWindowWrapper>(this->logger.get(), titleIn, Dimension(widthIn, heightIn), flags);
		this->getRenderManager().init(this->windowWrap->get());
		this->cameraWrap = std::make_unique<GameCamera>(this->logger.get(), this->windowWrap.get());
		this->hasBeenInit = true;
	}
}



void Game::run() 
{
	if (!hasBeenInit) 
	{
		getLogger().message(Logger::Level::FATAL, "Game has not been initialized", Logger::Output::TXT_FILE);
		markOver();
	}

	getTimer().start();
	while(!this->isOver() && !this->isNullState()) 
	{
		TileMap* world = getWorldStack().getWorld();
		if(world == nullptr) 
		{
			getLogger().message(Logger::Level::FATAL, "Null Pointer exception: Tried to get a null World!", Logger::Output::TXT_FILE);
			markOver();
		}
		else 
		{
			Dimension worldSize(world->width() * world->tileWidth(), world->height() * world->tileHeight());
			getCamera()->updatePos(worldSize, true);
			getState().render(*getCamera());
			getState().onInputEvent();
			if(getTimer().getTicks() >= this->tickRate) 
			{
				getState().tick(*getCamera(), *world, getTimer().getDelta());
				getState().ChangeState(0, this);
				getTimer().start();
			}
		}
		EventBus::dispatchAllEvents();
	}
}



void Game::addState(IGameState* stateIn) 
{
	if(stateIn == nullptr)
	{
		logger->message(Logger::Level::ERROR, "Null Pointer exception: Tried to add a null State!", Logger::Output::TXT_FILE);
		return;
	}
	this->states.emplace_back(std::unique_ptr<IGameState>(stateIn));
	//This is done to prevent the user from trying to access the pointer
	//Or from trying to free the pointer after they passed it
	stateIn = nullptr;
}



void Game::removeState() 
{
	if(this->states.empty()) 
	{
		logger->message(Logger::Level::WARNING, "Tried to remove State but there are none!", Logger::Output::TXT_FILE);
		return;
	}
	this->states.pop_back();
}



bool Game::isOver() const 
{
	return this->gameOver;
}



void Game::markOver() 
{
	logger->message(Logger::Level::INFO, "Quitting Game", Logger::Output::TXT_FILE);
	this->gameOver = true;
}



bool Game::isKeyPressed(int scancode)
{
	int numberOfKeys = 0;
	const Uint8* keyState = SDL_GetKeyboardState(&numberOfKeys);
	if (abs(scancode) < numberOfKeys)
		return keyState[abs(scancode)];
	else
		return false;
}



Logger& Game::getLogger() 
{
	return *this->logger.get();
}



Renderer& Game::getRenderManager() 
{
	return *this->renderer.get();
}



AudioMixer& Game::getMixer() 
{
	return *this->audioManager.get();
}



WorldStack& Game::getWorldStack() 
{
	return *this->worlds.get();
}



EntityManager& Game::getEntityManager() 
{
	return *this->entityManager.get();
}



GameTimer& Game::getTimer() 
{
	return *this->timer.get();
}



const SDLWindowWrapper* Game::getWindow() const 
{
	return this->windowWrap.get();
}



GameCamera* Game::getCamera() 
{
	return this->cameraWrap.get();
}



IGameState& Game::getState() 
{
	return *this->states.back().get();
}



bool Game::isNullState() const 
{
	if(this->states.empty()) 
	{
		logger->message(Logger::Level::FATAL, "Game is in an unknown state!", Logger::Output::TXT_FILE);
		return true;
	}
	else 
		return false;
}








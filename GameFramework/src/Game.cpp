#include <SDL.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

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
#include "utilities/wrappers/SDLWindowWrapper.h"
#include "world/WorldStack.h"




Game::Game(const std::string &titleIn, int windowHeight, int windowWidth, uint32_t flags, int MaxFPS)
		: gameOver(false), hasBeenInit(false), tickRate(20) 
{
	spdlog::set_pattern("%^[%l] %n: %v - %x %T%$");
	auto fileLogger = spdlog::basic_logger_mt("fileLogger", "logs/log.txt");
	fileLogger->set_level(spdlog::level::trace);
	fileLogger->info("Logging started");
	m_logger = fileLogger;

	this->renderer = std::make_unique<Renderer>();
	this->audioManager = std::make_unique<AudioMixer>();
	this->worlds = std::make_unique<WorldStack>();
	this->entityManager = std::make_unique<EntityManager>();
	this->timer = std::make_unique<GameTimer>();

	m_logger->info("Initializing SDL Video and Audio");
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
				spdlog::get("fileLogger")->info("KeyboardEvent: keycode {0}, PRESS", e.getKeyCode());
				break;

			case KeyboardEvent::Action::RELEASE:
				spdlog::get("fileLogger")->info("KeyboardEvent: keycode {0}, RELEASE", e.getKeyCode());
				break;

			case KeyboardEvent::Action::REPEAT:
				spdlog::get("fileLogger")->info("KeyboardEvent: keycode {0}, REPEAT", e.getKeyCode());
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
	m_logger->info("Terminating SDL");
	SDL_Quit();
}



void Game::initWindow(const std::string &titleIn, int widthIn, int heightIn, uint32_t flags) 
{
	if (!this->hasBeenInit) 
	{
		this->windowWrap = std::make_unique<SDLWindowWrapper>(titleIn, Pos2N(widthIn, heightIn), flags);
		this->getRenderManager().init(this->windowWrap->get());
		this->cameraWrap = std::make_unique<GameCamera>(this->windowWrap.get());
		this->hasBeenInit = true;
	}
}



void Game::run() 
{
	if (!hasBeenInit) 
	{
		m_logger->error("Game has not been initialized");
		markOver();
	}

	getTimer().start();
	while(!this->isOver() && !this->isNullState()) 
	{
		TileMap* world = getWorldStack().getWorld();
		if(world == nullptr) 
		{
			m_logger->error("Null Pointer exception: Tried to get a null World!");
			markOver();
		}
		else 
		{
			Pos2N worldSize(world->width() * world->tileWidth(), world->height() * world->tileHeight());
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
		m_logger->error("Null Pointer exception: Tried to add a null State!");
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
		m_logger->warn("Tried to remove State but there are none!");
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
	m_logger->info("Quitting Game");
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
		m_logger->error("Game is in an unknown state!");
		return true;
	}
	else 
		return false;
}








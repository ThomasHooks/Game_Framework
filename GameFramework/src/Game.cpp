#include <SDL.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "Game.hpp"
#include "events/EventBus.hpp"
#include "events/WindowEvent.hpp"
#include "events/KeyboardEvent.hpp"
#include "audiomixer/AudioMixer.h"
#include "entities/EntityJournal.hpp"
#include "renderer/Renderer.h"
#include "world/TileMap.h"
#include "renderer/screen/GameCamera.h"
#include "renderer/screen/Window.h"
#include "world/WorldStack.h"
#include "utilities/Assertions.h"




GameBuilder::GameBuilder()
	: windowTitle(""), windowSize(640, 480), windowFlags(0), logFileLocation("./log.txt"), logLevel(spdlog::level::trace), tickRate(20)
{}



GameBuilder& GameBuilder::setWindow(const std::string & titleIn, int widthIn, int heightIn, unsigned int flagsIn)
{
	windowTitle = titleIn;
	windowSize.x = widthIn;
	windowSize.y = heightIn;
	windowFlags = flagsIn;
	return *this;
}



GameBuilder& GameBuilder::setLogger(const std::string& fileLocationIn, spdlog::level::level_enum levelIn)
{
	logFileLocation = fileLocationIn;
	logLevel = levelIn;
	return *this;
}



GameBuilder& GameBuilder::setTickRate(unsigned int ticksIn)
{
	tickRate = ticksIn;
	return *this;
}



Game::Game(const GameBuilder& builderIn)
		: m_gameOver(false), m_tickRate(20) 
{
	spdlog::set_pattern("%^[%l] %n: %v - %x %T%$");
	auto fileLogger = spdlog::basic_logger_mt("Core", "logs/log.txt");
	fileLogger->set_level(spdlog::level::trace);
	fileLogger->flush_on(spdlog::level::err);
	m_logger = fileLogger;

	std::shared_ptr<spdlog::logger> assertionLogger = spdlog::stdout_color_mt("Assertion");
	assertionLogger->set_level(spdlog::level::warn);

	m_logger->info("Logging started");

	m_renderer = std::make_unique<Renderer>();
	m_audioManager = std::make_unique<AudioMixer>();
	m_worlds = std::make_unique<WorldStack>();
	m_entities = std::make_unique<EntityJournal>();

	m_logger->info("Initializing SDL Video and Audio");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		m_logger->critical("Unable to initialize SDL: {0}", SDL_GetError());

	SDL_GL_LoadLibrary(NULL);

	GAME_ASSERT(builderIn.windowSize.w > 0 && builderIn.windowSize.h > 0);
	this->initWindow(builderIn.windowTitle, builderIn.windowSize.w, builderIn.windowSize.h, builderIn.windowFlags | SDL_WINDOW_OPENGL);
	this->audioMixer().init();

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
}



Game::~Game() 
{
	EventBus::unsubscribe<WindowEvent>(m_onWindowEvent);
	renderer().shutdown();
	m_logger->info("Terminating SDL");
	SDL_Quit();
}



void Game::run() 
{
	m_timer.start();
	while (!this->isDone())
	{
		this->updateSDL();
		TileMap* world = this->worldStack().getWorld();
		if (world == nullptr) 
		{
			m_logger->error("Null Pointer exception: Tried to get a null World!");
			this->markOver();
		}
		else 
		{
			Pos2N worldSize(world->width() * world->tileWidth(), world->height() * world->tileHeight());
			this->getCamera()->updatePos(worldSize, true);

			//Render loop
			for (auto& layer : m_layerStack)
			{
				if (layer->isActive())
					layer->onRender(*getCamera(), renderer());
			}
			//Logic loop
			if (m_timer.getMil() >= m_tickRate)
			{
				for (auto& layer : m_layerStack)
				{
					if (layer->isActive())
						layer->onTick(*getCamera(), *world, m_timer.getSec());
				}
				m_timer.start();
			}
		}
		EventBus::dispatchAllEvents();
	}
	m_timer.stop();
}



bool Game::isDone() const
{
	return m_gameOver;
}



void Game::markOver() 
{
	m_logger->info("Quitting Game");
	m_gameOver = true;
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



Renderer& Game::renderer() 
{
	return *m_renderer.get();
}



void Game::registerTexture(const std::string& tagIn, const std::string& fileLocationIn, const Pos2N& sizeIn)
{
	m_renderer->registerTexture(tagIn, fileLocationIn, sizeIn);
}



void Game::deregisterTexture(const std::string& tagIn)
{
	m_renderer->deregisterTexture(tagIn);
}



void Game::deregisterAllTextures()
{
	m_renderer->deregisterAllTextures();
}



AudioMixer& Game::audioMixer()
{
	return *m_audioManager.get();
}



WorldStack& Game::worldStack() 
{
	return *m_worlds.get();
}



EntityJournal& Game::entities()
{
	return *m_entities.get();
}



const Window* Game::getWindow() const 
{
	return m_windowWrap.get();
}



GameCamera* Game::getCamera() 
{
	return m_cameraWrap.get();
}



void Game::initWindow(const std::string& titleIn, int widthIn, int heightIn, uint32_t flags)
{
	m_windowWrap = std::make_unique<Window>(titleIn, Pos2N(widthIn, heightIn), flags);
	this->renderer().init(m_windowWrap->get());
	m_cameraWrap = std::make_unique<GameCamera>(m_windowWrap.get());
}



void Game::updateSDL()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_WINDOWEVENT_CLOSE:
			if (getWindow()->isOpen())
				markOver();
			break;

		case SDL_QUIT:
			markOver();
			break;
		}
	}
}








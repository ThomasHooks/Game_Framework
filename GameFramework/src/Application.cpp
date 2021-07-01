#include <iostream>

#include <SDL.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "Application.hpp"
#include "events/EventBus.hpp"
#include "events/WindowEvent.h"
#include "events/KeyboardEvent.h"
#include "audiomixer/AudioMixer.h"
#include "entities/EntityJournal.hpp"
#include "renderer/Renderer.h"
#include "world/TileMap.h"
#include "renderer/screen/Camera.h"
#include "renderer/screen/Window.h"
#include "world/WorldStack.h"
#include "utilities/Assertions.h"

#include "events/MouseEvent.h"




ApplicationBuilder::ApplicationBuilder()
	: windowTitle(""), windowSize(640, 480), windowFlags(0), logFileLocation("./log.txt"), logLevel(spdlog::level::trace), tickRate(20)
{}



ApplicationBuilder& ApplicationBuilder::setWindow(const std::string & titleIn, int widthIn, int heightIn, unsigned int flagsIn)
{
	windowTitle = titleIn;
	windowSize.x = widthIn;
	windowSize.y = heightIn;
	windowFlags = flagsIn;
	return *this;
}



ApplicationBuilder& ApplicationBuilder::setLogger(const std::string& fileLocationIn, spdlog::level::level_enum levelIn)
{
	logFileLocation = fileLocationIn;
	logLevel = levelIn;
	return *this;
}



ApplicationBuilder& ApplicationBuilder::setTickRate(unsigned int ticksIn)
{
	tickRate = ticksIn;
	return *this;
}



Application::Application(const ApplicationBuilder& builderIn)
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

	m_audioManager = std::make_unique<AudioMixer>();
	m_worlds = std::make_unique<WorldStack>();
	m_entities = std::make_unique<EntityJournal>();

	m_logger->info("Initializing SDL Video and Audio");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		m_logger->critical("Unable to initialize SDL: {0}", SDL_GetError());

	SDL_GL_LoadLibrary(NULL);

	GAME_ASSERT(builderIn.windowSize.w > 0 && builderIn.windowSize.h > 0);
	this->initWindow(builderIn.windowTitle, builderIn.windowSize.w, builderIn.windowSize.h, builderIn.windowFlags);

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



Application::~Application() 
{
	EventBus::unsubscribe<WindowEvent>(m_onWindowEvent);
	renderer().shutdown();
	m_window->shutdown();
	m_logger->info("Terminating SDL");
	SDL_Quit();
}



void Application::initWindow(const std::string& titleIn, int widthIn, int heightIn, uint32_t flags)
{
	m_window = std::make_unique<Window>(titleIn, Pos2N(widthIn, heightIn), flags);
	m_renderer = std::make_unique<Renderer>();
	this->renderer().init(1000);
	m_camera = std::make_shared<Camera>(static_cast<float>(widthIn), static_cast<float>(heightIn));
}



void Application::run() 
{
	m_timer.start();

	while (!this->isDone())
	{
		// Update SDL's event queue
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
		
		m_camera->update();

		//Render loop for all layers
		for (auto& layer : m_layerStack)
		{
			if (layer->isActive())
				layer->onRender(m_camera, *m_renderer.get());
		}

		m_window->update();

		//Logic loop for all layers
		if (m_timer.getMil() >= m_tickRate)
		{
			for (auto& layer : m_layerStack)
			{
				if (layer->isActive())
					layer->onTick(*m_camera.get(), m_timer.getSec());
			}
			m_timer.start();
		}

		EventBus::dispatchAllEvents();
	}

	m_timer.stop();
}



bool Application::isDone() const
{
	return m_gameOver;
}



void Application::markOver() 
{
	m_logger->info("Quitting Application");
	m_gameOver = true;
}



bool Application::isKeyPressed(int scancode)
{
	int numberOfKeys = 0;
	const Uint8* keyState = SDL_GetKeyboardState(&numberOfKeys);
	if (abs(scancode) < numberOfKeys)
		return keyState[abs(scancode)];
	else
		return false;
}



glm::ivec2 Application::getMouseLocation()
{
	int x = 0, y = 0;
	Uint32 button = SDL_GetMouseState(&x, &y);
	return glm::ivec2(x,y);
}



Renderer& Application::renderer()
{
	return *m_renderer.get();
}



void Application::registerTexture(const std::string& fileLocationIn)
{
	m_renderer->assetLibrarian().addTexture(fileLocationIn);
}



AssetLibrarian& Application::assetLibrarian()
{
	return m_renderer->assetLibrarian();
}



AudioMixer& Application::audioMixer()
{
	return *m_audioManager.get();
}



WorldStack& Application::worldStack() 
{
	return *m_worlds.get();
}



EntityJournal& Application::entities()
{
	return *m_entities.get();
}



const Window* Application::getWindow() const 
{
	return m_window.get();
}



Camera* Application::getCamera() 
{
	return m_camera.get();
}




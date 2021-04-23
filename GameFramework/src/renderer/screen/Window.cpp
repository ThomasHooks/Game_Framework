#include <SDL.h>
#include <glad/glad.h>

#include "renderer/screen/Window.h"
#include "events/EventBus.hpp"
#include "events/WindowEvent.hpp"
#include "events/KeyboardEvent.hpp"




int filterEventCallback(void *userdata, SDL_Event * event)
{
	WindowData* data = (WindowData*)userdata;
	switch(event->type)
	{
	case SDL_WINDOWEVENT:
		switch (event->window.event)
		{
		case SDL_WINDOWEVENT_CLOSE:
			data->width = 0;
			data->height = 0;
			EventBus::publish<WindowEvent>(data->width, data->height, WindowEvent::Action::CLOSE);
			return 0;

		case SDL_WINDOWEVENT_SIZE_CHANGED:
			data->width = event->window.data1;
			data->height = event->window.data2;
			EventBus::publish<WindowEvent>(data->width, data->height, WindowEvent::Action::RESIZE);
			return 0;

		default:
			break;
		}
		break;

	case SDL_KEYDOWN:
		if (event->key.repeat)
			EventBus::publish<KeyboardEvent>(event->key.keysym.sym, event->key.keysym.scancode, KeyboardEvent::Action::REPEAT);
		else
			EventBus::publish<KeyboardEvent>(event->key.keysym.sym, event->key.keysym.scancode, KeyboardEvent::Action::PRESS);
		return 0;

	case SDL_KEYUP:
		EventBus::publish<KeyboardEvent>(event->key.keysym.sym, event->key.keysym.scancode, KeyboardEvent::Action::RELEASE);
		return 0;

	default:
		break;
	}
	return 1;
}



Window::Window(const std::string& title, const Pos2N& sizeIn, unsigned int flags)
	: m_size(sizeIn.w, sizeIn.h), m_window(nullptr), m_glContext(nullptr), m_winData(title, sizeIn.w, sizeIn.h)
{
	m_logger = Loggers::getLog();
	m_logger->info("Initializing Window");

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_size.w, m_size.h, flags | SDL_WINDOW_OPENGL);
	if (m_window == nullptr)
	{
		m_logger->critical("SDL was unable to create the window: SDL error: {0}", SDL_GetError());
		__debugbreak();
	}
	m_winData.window = m_window;

	m_glContext = SDL_GL_CreateContext(m_window);
	if (m_glContext == nullptr)
	{
		m_logger->critical("SDL was unable to create the OpenGL context: SDL error: {0}", SDL_GetError());
		__debugbreak();
	}

	if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
	{
		m_logger->critical("Unable to initialize Glad");
		__debugbreak();
	}

	//0 for immediate updates, 1 for updates synchronized with the vertical retrace, -1 for adaptive vsync
	if (SDL_GL_SetSwapInterval(1) != 0)
		m_logger->warn("Unable to set the swap interval: SDL error: {0}", SDL_GetError());

	m_logger->info("Vendor: {0} GPU: {1} Version: {2}", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));

	SDL_SetEventFilter(filterEventCallback, &m_winData);

	m_logger->info("Window has been initialized");
}



Window::~Window()
{
	m_logger->info("Closing Window");
	SDL_GL_DeleteContext(m_glContext);
	m_glContext = nullptr;
	SDL_DestroyWindow(m_window);
	m_window = nullptr;
	m_logger->info("Window has been closed ");
}



void Window::update()
{
	SDL_GL_SwapWindow(m_window);
}



int Window::width() const
{
	return m_window != nullptr ? m_size.w : 0;
}



int Window::height() const
{
	return m_window != nullptr ? m_size.h : 0;
}



bool Window::isOpen() const
{
	return m_window != nullptr;
}



SDL_Window* Window::get()
{
	return m_window;
}








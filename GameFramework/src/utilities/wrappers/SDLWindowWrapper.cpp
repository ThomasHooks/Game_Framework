#include <SDL.h>

#include "SDLWindowWrapper.h"
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



SDLWindowWrapper::SDLWindowWrapper(const std::string& title, const Pos2N& sizeIn, unsigned int flags)
	: m_size(sizeIn.w, sizeIn.h), m_window(nullptr), m_winData(title, sizeIn.w, sizeIn.h)
{
	m_logger = Loggers::getLog();
	m_logger->info("Initializing Window");

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_size.w, m_size.h, flags);
	m_winData.window = m_window;

	SDL_SetEventFilter(filterEventCallback, &m_winData);

	m_logger->info("Window has been initialized");
}



SDLWindowWrapper::~SDLWindowWrapper()
{
	m_logger->info("Closing Window");
	SDL_DestroyWindow(m_window);
	m_window = nullptr;
	m_logger->info("Window has been closed ");
}



int SDLWindowWrapper::width() const
{
	return m_window != nullptr ? m_size.w : 0;
}



int SDLWindowWrapper::height() const
{
	return m_window != nullptr ? m_size.h : 0;
}



bool SDLWindowWrapper::isOpen() const
{
	return m_window != nullptr;
}



SDL_Window* SDLWindowWrapper::get()
{
	return m_window;
}








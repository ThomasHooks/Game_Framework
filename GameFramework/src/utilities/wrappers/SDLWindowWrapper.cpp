#include <SDL.h>

#include "SDLWindowWrapper.h"
#include "events/EventBus.hpp"
#include "events/WindowEvent.hpp"
#include "events/KeyboardEvent.hpp"
#include "utilities/Logger.h"




/*
 * @return	If 1 the event will be added to SDL's internal queue. If it returns 0, then the event will be dropped from
 * 			SDL's queue, but the internal state will still be updated.
 */
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



SDLWindowWrapper::SDLWindowWrapper(Logger* logger_ptr, const std::string& title, const Dimension& sizeIn, unsigned int flags)
	: size(sizeIn.width, sizeIn.height), window(nullptr), m_winData(title, sizeIn.width, sizeIn.height), logger(logger_ptr)
{
	logger->message(Logger::Level::INFO, "Initializing Window", Logger::Output::TXT_FILE);

	window = SDL_CreateWindow(title.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			size.width,
			size.height,
			flags);
	m_winData.window = window;

	SDL_SetEventFilter(filterEventCallback, &m_winData);

	logger->message(Logger::Level::INFO, "Window has been initialized", Logger::Output::TXT_FILE);
}



SDLWindowWrapper::~SDLWindowWrapper()
{
	logger->message(Logger::Level::INFO, "Closing Window", Logger::Output::TXT_FILE);
	SDL_DestroyWindow(window);
	window = nullptr;
	logger->message(Logger::Level::INFO, "Window has been closed ", Logger::Output::TXT_FILE);
}



/*
 * @return	The Window's width or '0' if the window has not been Initialized
 */
int SDLWindowWrapper::width() const
{
	return this->window != nullptr ? this->size.width : 0;
}



/*
 * @return	The Windows height or '0' if the window has not been Initialized
 */
int SDLWindowWrapper::height() const
{
	return this->window != nullptr ? this->size.height : 0;
}



/*
 * @return	Checks if this Window is open
 */
bool SDLWindowWrapper::isOpen() const
{
	return this->window != nullptr;
}



/*
 * @nullable
 * Exposes the SDL_Window inside of this wrapper
 *
 * @return	The SDL_Window pointer inside of this wrapper
 */
SDL_Window* SDLWindowWrapper::get()
{
	return this->window;
}








#ifndef SDLWINDOWWRAPPER_H_
#define SDLWINDOWWRAPPER_H_


#include <memory>
#include <string>

#include <SDL.h>

#include "utilities/Loggers.hpp"
#include "utilities/physics/Dimension.h"
#include "utilities/physics/Position.h"




struct WindowData
{
	WindowData(const std::string& titleIn = "Name of Game", unsigned int widthIn = 640, unsigned int heightIn = 480)
		: title(titleIn), width(widthIn), height(heightIn) 
	{};

	std::string title;
	unsigned int width, height;
	bool hidden = false;
	SDL_Window* window = nullptr;
};



int filterEventCallback(void *userdata, SDL_Event * event);



class SDLWindowWrapper
{
public:

	SDLWindowWrapper(const std::string &title, const Dimension &sizeIn, unsigned int flags);



	~SDLWindowWrapper();



	SDLWindowWrapper(SDLWindowWrapper &&other) = delete;



	SDLWindowWrapper(const SDLWindowWrapper &other) = delete;



	/*
	 * @return	The Window's width or '0' if the window has not been Initialized
	 */
	int width() const;



	/*
	 * @return	The Windows height or '0' if the window has not been Initialized
	 */
	int height() const;



	/*
	 * @return	Checks if this Window is open
	 */
	bool isOpen() const;



	/*
	 * @nullable
	 * Exposes the SDL_Window inside of this wrapper
	 *
	 * @return	The SDL_Window pointer inside of this wrapper
	 */
	SDL_Window* get();



private:

	Dimension size;

	SDL_Window* window;

	WindowData m_winData;

	std::shared_ptr<spdlog::logger> m_logger;
};


#endif /* SDLWINDOWWRAPPER_H_ */




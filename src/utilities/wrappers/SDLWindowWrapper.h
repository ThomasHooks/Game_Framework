//============================================================================
// Name       		: SDLWindowWrapper.h
// Author     		: Thomas Hooks
// Last Modified	: 03/30/2020
//============================================================================




#ifndef SDLWINDOWWRAPPER_H_
#define SDLWINDOWWRAPPER_H_


#include <memory>
#include <string>

#include <SDL.h>

#include "../physics/Dimension.h"
#include "../physics/Position.h"


class SDLWindowWrapper {

public:

	SDLWindowWrapper(class GameLogger* logger_ptr,
			const std::string &title,
			const Dimension &sizeIn,
			Uint32 flags);



	~SDLWindowWrapper();



	SDLWindowWrapper(SDLWindowWrapper &&other) = delete;



	SDLWindowWrapper(const SDLWindowWrapper &other) = delete;



	/*
	 * @return	The Window's width or '0' if the window has not been Initialized
	 *
	 * Gets the Windows width
	 */
	int width() const;



	/*
	 * @return	The Window's height or '0' if the window has not been Initialized
	 *
	 * Gets the Windows height
	 */
	int height() const;



	/*
	 * @return	True if the Window is open and false if closed
	 *
	 * Checks if this Window is open
	 */
	bool isOpen() const;



	/*
	 * @nullable
	 *
	 * @return	The SDL_Window pointer inside of this wrapper
	 *
	 * Exposes the SDL_Window inside of this wrapper
	 */
	SDL_Window* get();



private:

	Dimension size;

	SDL_Window* window;

	class GameLogger *logger;
};


#endif /* SDLWINDOWWRAPPER_H_ */




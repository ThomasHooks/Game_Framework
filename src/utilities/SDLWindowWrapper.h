//============================================================================
// Name       		: SDLWindowWrapper.h
// Author     		: Thomas Hooks
// Last Modified	: 03/18/2020
//============================================================================




#ifndef SDLWINDOWWRAPPER_H_
#define SDLWINDOWWRAPPER_H_


#include <memory>
#include <string>

#include <SDL.h>

#include "Dimension.h"
#include "Position.h"


class SDLWindowWrapper {

public:

	SDLWindowWrapper(class GameLogger* logger_ptr,
			const std::string &title,
			const Dimension &sizeIn,
			Uint32 flags);



	~SDLWindowWrapper();



	SDLWindowWrapper(SDLWindowWrapper &&other) = delete;



	SDLWindowWrapper(const SDLWindowWrapper &other) = delete;



	//Gets the Windows width
	int getWidth();



	//Gets the Windows Height
	int getHeight();



	//Exposes the SDL_Window pointer
	//@nullable
	SDL_Window* get();



	//Gets the camera's position
	Position& getCameraPos();



private:

	Dimension size;

	Position camera;

	SDL_Window* window;

	class GameLogger *logger;
};


#endif /* SDLWINDOWWRAPPER_H_ */




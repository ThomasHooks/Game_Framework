//============================================================================
// Name       		: SDLWindowWrapper.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/18/2020
//============================================================================





#include "SDLWindowWrapper.h"
#include "GameLogger.h"




SDLWindowWrapper::SDLWindowWrapper(GameLogger* logger_ptr, const std::string &title, const Dimension &sizeIn, Uint32 flags)
	: size(sizeIn.width, sizeIn.height),
	  camera(),
	  window(nullptr),
	  logger(logger_ptr) {

	logger->message(Level::INFO, "Initializing Window", Output::TXT_FILE);

	window = SDL_CreateWindow(title.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			size.width,
			size.height,
			flags);

	logger->message(Level::INFO, "Window has been initialized", Output::TXT_FILE);
}



SDLWindowWrapper::~SDLWindowWrapper() {

	logger->message(Level::INFO, "Closing Window", Output::TXT_FILE);
	SDL_DestroyWindow(window);
	window = nullptr;
	logger->message(Level::INFO, "Window has been closed ", Output::TXT_FILE);
}



//Gets the Windows width
int SDLWindowWrapper::getWidth(){
	return this->size.width;
}



//Gets the Windows Height
int SDLWindowWrapper::getHeight(){
	return this->size.height;
}



//Exposes the SDL_Window pointer
//@nullable
SDL_Window* SDLWindowWrapper::get(){
	return this->window;
}



//Gets the Windows position
Position& SDLWindowWrapper::getCameraPos(){
	return this->camera;
}








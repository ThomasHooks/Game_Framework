//============================================================================
// Name       		: SDLWindowWrapper.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/30/2020
//============================================================================





#include "SDLWindowWrapper.h"

#include "../GameLogger.h"




SDLWindowWrapper::SDLWindowWrapper(GameLogger* logger_ptr, const std::string &title, const Dimension &sizeIn, Uint32 flags)
	: size(sizeIn.width, sizeIn.height),
	  window(nullptr),
	  logger(logger_ptr) {

	logger->message(EnumLogLevel::INFO, "Initializing Window", EnumLogOutput::TXT_FILE);

	window = SDL_CreateWindow(title.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			size.width,
			size.height,
			flags);

	logger->message(EnumLogLevel::INFO, "Window has been initialized", EnumLogOutput::TXT_FILE);
}



SDLWindowWrapper::~SDLWindowWrapper() {

	logger->message(EnumLogLevel::INFO, "Closing Window", EnumLogOutput::TXT_FILE);
	SDL_DestroyWindow(window);
	window = nullptr;
	logger->message(EnumLogLevel::INFO, "Window has been closed ", EnumLogOutput::TXT_FILE);
}



/*
 * @return	The Window's width or '0' if the window has not been Initialized
 *
 * Gets the Windows width
 */
int SDLWindowWrapper::width() const {
	return this->window != nullptr ? this->size.width : 0;
}



/*
 * @return	The Window's height or '0' if the window has not been Initialized
 *
 * Gets the Windows height
 */
int SDLWindowWrapper::height() const {
	return this->window != nullptr ? this->size.height : 0;
}



/*
 * @return	True if the Window is open and false if closed
 *
 * Checks if this Window is open
 */
bool SDLWindowWrapper::isOpen() const {
	return this->window != nullptr ? true : false;
}



/*
 * @nullable
 *
 * @return	The SDL_Window pointer inside of this wrapper
 *
 * Exposes the SDL_Window inside of this wrapper
 */
SDL_Window* SDLWindowWrapper::get(){
	return this->window;
}








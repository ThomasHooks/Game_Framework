//============================================================================
// Name       		: RendererManager.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/06/2020
//============================================================================




#include <SDL.h>
#include "SDL_image.h"

#include "RendererManager.h"
#include "../utilities/GameLogger.h"
#include "../utilities/Position.h"
#include "../utilities/Dimension.h"
#include "../utilities/SDLTextureWrapper.h"




RendererManager::RendererManager(class GameLogger *logger_ptr)
	: hasBeenInit(false),
	  scale(1.0f),
	  logger(logger_ptr),
	  renderer(nullptr) {}



RendererManager::~RendererManager() {

	logger->message(Level::INFO, "Freeing renderer", Output::TXT_FILE);
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
}



void RendererManager::init(SDL_Window *windowIn){
	/*
	 *
	 */




	if(!this->hasBeenInit) {
		this->renderer = SDL_CreateRenderer(windowIn, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		logger->message(Level::INFO, "Renderer has been initialized", Output::TXT_FILE);
		this->hasBeenInit = true;
	}
}


//TODO
bool RendererManager::registerTexture(const std::string &tag, const std::string &fileLocation){
	/*
	 *
	 */




	if(this->hasBeenInit){

	}
	return false;
}


//TODO
bool RendererManager::deregisterTexture(const std::string &tag){
	/*
	 *
	 */




	if(this->hasBeenInit){

	}
	return false;
}


//TODO
bool RendererManager::deregisterAllTextures(){
	/*
	 *
	 */




	if(this->hasBeenInit){

	}
	return false;
}



bool RendererManager::setDrawColor(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha){
	/*
	 *
	 */




	if(this->hasBeenInit) {
		SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
		return true;
	}
	else {
		logger->message(Level::ERROR, "Cannot set draw color, Renderer has not been initialized!", Output::TXT_FILE);
		return false;
	}
}



bool RendererManager::clear(){
	/*
	 *
	 */




	if(this->hasBeenInit) {
		SDL_RenderClear(this->renderer);
		return true;
	}
	else {
		logger->message(Level::ERROR, "Cannot clear, Renderer has not been initialized!", Output::TXT_FILE);
		return false;
	}
}



bool RendererManager::present(){
	/*
	 *
	 */




	if(this->hasBeenInit) {
		SDL_RenderPresent(this->renderer);
		return true;
	}
	else {
		logger->message(Level::ERROR, "Cannot present, Renderer has not been initialized!", Output::TXT_FILE);
		return false;
	}
}



void RendererManager::drawPoint(const Position &pos){
	/*
	 * @param	pos		The coordinates of the Point
	 */




	if(this->hasBeenInit) {
		int code = SDL_RenderDrawPoint(this->renderer, pos.xPosN(), pos.yPosN());
		if(code < 0) {
			std::string sdlMessage = SDL_GetError();
			logger->message(Level::ERROR, "SDL Error while trying to draw a point: " + sdlMessage, Output::CONSOLE);
		}
	}

	else logger->message(Level::ERROR, "Cannot draw point, Renderer has not been initialized!", Output::TXT_FILE);
}



void RendererManager::drawLine(const class Position &startPos, const class Position &endPos){
	/*
	 * @param	startPos	The coordinates of the starting point of the Line
	 *
	 * @param	endPos		The coordinates of the ending point of the Line
	 */




	if(this->hasBeenInit) {
		int code = SDL_RenderDrawLine(this->renderer,
				startPos.xPosN(),
				startPos.yPosN(),
				endPos.xPosN(),
				endPos.yPosN());

		if(code < 0) {
			std::string sdlMessage = SDL_GetError();
			logger->message(Level::ERROR, "SDL Error while trying to draw a line: " + sdlMessage, Output::CONSOLE);
		}
	}

	else logger->message(Level::ERROR, "Cannot draw rectangle, Renderer has not been initialized!", Output::TXT_FILE);
}



void RendererManager::drawRect(const class Position &pos, const class Dimension &dim, bool fill){
	/*
	 * @param	pos		The coordinates of the rectangle
	 *
	 * @param	dim		The dimensions of the rectangle
	 *
	 * @param	fill	Flag to draw a filled in rectangle
	 */




	if(this->hasBeenInit) {
		SDL_Rect rect = {pos.xPosN(), pos.yPosN(), dim.width, dim.height};

		int code = fill ? SDL_RenderFillRect(this->renderer, &rect) : SDL_RenderDrawRect(this->renderer, &rect);

		if(code < 0) {
			std::string sdlMessage = SDL_GetError();
			logger->message(Level::ERROR, "SDL Error while trying to draw a rectangle: " + sdlMessage, Output::CONSOLE);
		}
	}

	else logger->message(Level::ERROR, "Cannot draw rectangle, Renderer has not been initialized!", Output::TXT_FILE);
}



void RendererManager::drawSprite(const std::string &tag,
								const Position &pos,
								const Position &cameraOffset,
								const Dimension &spriteSize,
								const Dimension &spriteLocation,
								const bool flipSprite){
	/*
	 * @param	tag				The tag ID of the entity/tile
	 *
	 * @param	pos				The coordinates of the entity/tile
	 *
	 * @param	cameraOffset	The coordinates of the camera
	 *
	 * @param	spriteSize		The dimensions of the sprite on the sprite sheet
	 *
	 * @param	spriteLocation	The location of the sprite in the sprite sheet
	 */




	if(this->hasBeenInit) {
		//Set the draw color to white
		this->setDrawColor(255, 255, 255, 255);

		//Select the right sprite from the sprite sheet
		SDL_Rect spriteRect = {spriteLocation.width * spriteSize.width,
				spriteLocation.height * spriteSize.height,
				spriteSize.width,
				spriteSize.height};

		//calculate the entities/tiles size and location in the world
		int xPos = pos.xPosN() - cameraOffset.xPosN() * spriteSize.width;
		int yPos = pos.yPosN() - cameraOffset.yPosN() * spriteSize.height;
		SDL_Rect entityRect = {xPos,
				yPos,
				static_cast<int>((spriteSize.width * this->scale) + 0.5f),
				static_cast<int>((spriteSize.height * this->scale) + 0.5f)};

		SDL_RendererFlip flip = flipSprite ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

		SDL_RenderCopyEx(this->renderer, this->getTexture(tag), &spriteRect, &entityRect, 0, NULL, flip);
	}

	else logger->message(Level::ERROR, "Cannot render sprite, Renderer has not been initialized!", Output::TXT_FILE);
}



void RendererManager::setScale(float scaleIn){
	/*
	 * @param	scaleIn		The new scale for all rendering
	 *
	 * The new scale cannot be zero or negative, and if scaleIn is either it will default to 1.0
	 */




	scaleIn <= 0.0f ? this->scale = 1.0f : this->scale = scaleIn;
}


//TODO
SDL_Texture* RendererManager::getTexture(const std::string &tag) const {
	/*
	 *
	 */




	return nullptr;
}








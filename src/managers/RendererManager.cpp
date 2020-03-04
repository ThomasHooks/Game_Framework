//============================================================================
// Name       		: RendererManager.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/04/2020
//============================================================================




#include <SDL.h>
#include "SDL_image.h"

#include "RendererManager.h"
#include "../utilities/GameLogger.h"
#include "AssetManager.h"
#include "../utilities/Position.h"
#include "../utilities/Dimension.h"




RendererManager::RendererManager(class GameLogger *logger_ptr,
								class AssetManager *assest_ptr,
								struct SDL_Renderer *renderer_ptr)
	: scale(1.0f),
	  logger(logger_ptr),
	  assests(assest_ptr),
	  renderer(renderer_ptr) {}



RendererManager::~RendererManager() {}



void RendererManager::drawSprite(const std::string &tag,
								const Position &pos,
								const Position &cameraOffset,
								const Dimension &spriteSize,
								const Dimension &spriteLocation,
								const bool flipSprite) const {
	/*
	 * @param	tag
	 *
	 * @param	pos
	 *
	 * @param	cameraOffset
	 *
	 * @param	spriteSize
	 *
	 * @param	spriteLocation
	 */




	//Set the draw color to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

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

	SDL_RenderCopyEx(this->renderer, this->assests->get_texture(tag), &spriteRect, &entityRect, 0, NULL, flip);

	return;
}



void RendererManager::setScale(float scaleIn){
	/*
	 * @param	scaleIn		The new scale for all rendering
	 *
	 * The new scale cannot be zero or negative, and if scaleIn is either it will default to 1.0
	 */




	scaleIn <= 0.0f ? this->scale = 1.0f : this->scale = scaleIn;

	return;
}








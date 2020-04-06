//============================================================================
// Name       		: SDLTextureWrapper.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/06/2020
//============================================================================




#include "SDLTextureWrapper.h"

#include <SDL.h>
#include "SDL_image.h"




SDLTextureWrapper::SDLTextureWrapper(SDL_Renderer *rendererIn, SDL_Surface *surfaceIn, Dimension &sizeIn)
	: tileSize(sizeIn.width, sizeIn.height) {
	texture = SDL_CreateTextureFromSurface(rendererIn, surfaceIn);
}



SDLTextureWrapper::~SDLTextureWrapper() {
	SDL_DestroyTexture(this->texture);
	this->texture = nullptr;
	this->tileSize.width = 0;
	this->tileSize.height = 0;
}



SDL_Texture* SDLTextureWrapper::getTexture() const {
	return this->texture;
}



const Dimension& SDLTextureWrapper::getTileSize() const {
	return this->tileSize;
}







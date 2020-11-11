#include "SDLTextureWrapper.h"

#include <SDL.h>
#include "SDL_image.h"

#include "utilities/Loggers.hpp"




SDLTextureWrapper::SDLTextureWrapper(SDL_Renderer* rendererIn, SDL_Surface* surfaceIn, const Pos2N& sizeIn)
	: m_tileSize(sizeIn.w, sizeIn.h) 
{
	m_texture = SDL_CreateTextureFromSurface(rendererIn, surfaceIn);
	if (m_texture)
		Loggers::getLog()->error("Failed to create texture from SDL Surface: {0}", SDL_GetError());
}



SDLTextureWrapper::~SDLTextureWrapper() 
{
	SDL_DestroyTexture(m_texture);
	m_texture = nullptr;
}



SDL_Texture* SDLTextureWrapper::getTexture() const 
{
	return m_texture;
}



const Pos2N& SDLTextureWrapper::getTileSize() const 
{
	return m_tileSize;
}








#include <SDL.h>
#include "SDL_image.h"

#include "renderer/texture/Texture.h"
#include "utilities/math/Pos2.hpp"
#include "utilities/Loggers.hpp"




Texture::Texture(SDL_Renderer* rendererIn, SDL_Surface* surfaceIn, const Pos2N& sizeIn)
	: m_tileSize(sizeIn.w, sizeIn.h) 
{
	m_texture = SDL_CreateTextureFromSurface(rendererIn, surfaceIn);
	if (!m_texture)
		Loggers::getLog()->error("Failed to create texture from SDL Surface: {0}", SDL_GetError());
}



Texture::~Texture() 
{
	SDL_DestroyTexture(m_texture);
	m_texture = nullptr;
}



SDL_Texture* Texture::expose() const 
{
	return m_texture;
}



const Pos2N& Texture::getTileSize() const 
{
	return m_tileSize;
}








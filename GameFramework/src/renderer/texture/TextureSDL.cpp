#include <SDL.h>
#include "SDL_image.h"

#include "renderer/texture/TextureSDL.h"
#include "utilities/math/Pos2.hpp"
#include "utilities/Loggers.hpp"




TextureSDL::TextureSDL(SDL_Renderer* rendererIn, SDL_Surface* surfaceIn, const Pos2N& sizeIn)
	: m_tileSize(sizeIn.w, sizeIn.h) 
{
	m_texture = SDL_CreateTextureFromSurface(rendererIn, surfaceIn);
	if (!m_texture)
		Loggers::getLog()->error("Failed to create texture from SDL Surface: {0}", SDL_GetError());
}



TextureSDL::~TextureSDL() 
{
	SDL_DestroyTexture(m_texture);
	m_texture = nullptr;
}



SDL_Texture* TextureSDL::expose() const 
{
	return m_texture;
}



const Pos2N& TextureSDL::getTileSize() const 
{
	return m_tileSize;
}








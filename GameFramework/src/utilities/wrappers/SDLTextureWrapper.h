#ifndef SDLTEXTUREWRAPPER_H_
#define SDLTEXTUREWRAPPER_H_

#include "utilities/math/Pos2.hpp"




class SDLTextureWrapper 
{
public:

	SDLTextureWrapper(struct SDL_Renderer* rendererIn, struct SDL_Surface* surfaceIn, const Pos2N &sizeIn);



	~SDLTextureWrapper();



	struct SDL_Texture* getTexture() const;



	const Pos2N& getTileSize() const;



private:

	Pos2N m_tileSize;

	struct SDL_Texture* m_texture;
};


#endif




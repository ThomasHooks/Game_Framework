//============================================================================
// Name       		: SDLTextureWrapper.h
// Author     		: Thomas Hooks
// Last Modified	: 03/06/2020
//============================================================================




#ifndef SDLTEXTUREWRAPPER_H_
#define SDLTEXTUREWRAPPER_H_


#include "Dimension.h"


class SDLTextureWrapper {

public:

	SDLTextureWrapper(struct SDL_Renderer *rendererIn,
			struct SDL_Surface *surfaceIn,
			Dimension &sizeIn);

	~SDLTextureWrapper();

	struct SDL_Texture* getTexture() const;
	const Dimension& getTileSize() const;

private:

	Dimension tileSize;
	struct SDL_Texture* texture;
};


#endif /* SDLTEXTUREWRAPPER_H_ */




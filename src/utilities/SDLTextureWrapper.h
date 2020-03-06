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
			const Dimension &sizeIn);

	~SDLTextureWrapper();

	SDLTextureWrapper(const SDLTextureWrapper &other) = delete;
	SDLTextureWrapper(SDLTextureWrapper &&other) = delete;

	struct SDL_Texture* getTexture() const;
	const Dimension& getSize() const;

private:

	Dimension size;
	struct SDL_Texture* texture;
};


#endif /* SDLTEXTUREWRAPPER_H_ */




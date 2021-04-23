#ifndef TEXTURESDL_H_
#define TEXTURESDL_H_

#include "utilities/math/Pos2.hpp"




class TextureSDL 
{
public:

	TextureSDL(struct SDL_Renderer* rendererIn, struct SDL_Surface* surfaceIn, const Pos2N &sizeIn);



	~TextureSDL();



	struct SDL_Texture* expose() const;



	const Pos2N& getTileSize() const;



private:

	Pos2N m_tileSize;

	struct SDL_Texture* m_texture;
};


#endif /* TEXTURESDL_H_ */




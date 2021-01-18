#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "utilities/math/Pos2.hpp"




class Texture 
{
public:

	Texture(struct SDL_Renderer* rendererIn, struct SDL_Surface* surfaceIn, const Pos2N &sizeIn);



	~Texture();



	struct SDL_Texture* expose() const;



	const Pos2N& getTileSize() const;



private:

	Pos2N m_tileSize;

	struct SDL_Texture* m_texture;
};


#endif




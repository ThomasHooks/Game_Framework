//============================================================================
// Name       		: Game_Tile.h
// Author     		: Thomas Hooks
// Last Modified	: 11/14/2019
//============================================================================




#ifndef TILE_H_
#define TILE_H_


class Tile {

public:

	Tile(bool solid, int index, float x, float y);

	~Tile();

	void draw(struct SDL_Renderer *renderer,
			struct SDL_Texture *tileSheet,
			int width, int height,
			int scale,
			float offSetX, float offSetY);


public:

	bool b_solid;			//Is the tile passable

	int n_tileIndex;		//Location of the tile's sprite in the sprite sheet

	float f_x, f_y;
};


#endif /* TILE_H_ */








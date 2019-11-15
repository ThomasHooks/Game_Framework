//============================================================================
// Name       		: Game_Tile.h
// Author     		: Thomas Hooks
// Version    		: 1
// Last Modified	: 11/14/2019
// Description		:
//============================================================================




#ifndef GAME_TILE_H_
#define GAME_TILE_H_


class Game_Tile {

public:

	Game_Tile(bool solid, int index, float x, float y);

	~Game_Tile();

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


#endif /* GAME_TILE_H_ */








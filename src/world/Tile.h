//============================================================================
// Name       		: Game_Tile.h
// Author     		: Thomas Hooks
// Last Modified	: 03/08/2020
//============================================================================




#ifndef TILE_H_
#define TILE_H_


#include "../utilities/Position.h"
#include "../utilities/Dimension.h"


class Tile {

public:

	Tile(bool solid, int index, float x, float y);

	~Tile();



	int n_tileIndex;		//Location of the tile's sprite in the sprite sheet

	float f_x, f_y;

	Position& getPos();

	bool isSolid() const;
	void setSolidState(bool stateIn);

protected:

	bool solid;

	Position pos;

	//Dimension spriteLocation;
};


#endif /* TILE_H_ */








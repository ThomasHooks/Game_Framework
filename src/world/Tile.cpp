//============================================================================
// Name       		: Game_Tile.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/08/2020
//============================================================================




#include "Tile.h"

#include <SDL.h>
#include "SDL_image.h"





Tile::Tile(bool solid, int index, float x, float y)
	: solid(solid),
	  n_tileIndex(index),
	  f_x(x),
	  f_y(y),
	  pos(x, y) {}



Tile::~Tile() {}



Position& Tile::getPos(){
	return this->pos;
}



bool Tile::isSolid() const {
	return this->solid;
}



void Tile::setSolidState(bool stateIn){
	this->solid = stateIn;
}








//============================================================================
// Name       		: Game_Tile.cpp
// Author     		: Thomas Hooks
// Last Modified	: 11/14/2019
//============================================================================




#include "Tile.h"

#include <SDL.h>
#include "SDL_image.h"





Tile::Tile(bool solid, int index, float x, float y)
	: b_solid(solid), n_tileIndex(index), f_x(x), f_y(y) {
	return;
}



Tile::~Tile() {
	return;
}



void Tile::draw(SDL_Renderer *renderer,
					 SDL_Texture *tileSheet,
					 int width, int height,
					 int scale,
					 float offSetX, float offSetY){
	/*
	 * brief		This method will cause the tile to draw itself
	 *
	 * param		renderer		ptr to the renderer
	 *
	 * param		tileSheet		ptr to the sprite tile sheet
	 *
	 * param		width			width of the tile
	 *
	 * param		height			height of the tile
	 *
	 * param		scale			how much the tile has been scaled
	 *
	 * param		f_offSetX		X coordinate off set from the camera
	 *
	 * param		f_offsetY		Y coordinate off set from the camera
	 */




	//Set the draw color to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


	//Select the right sprite from the sheet
	SDL_Rect TileScr = {n_tileIndex * width/scale,
						0,
						width/scale,
						height/scale};


	//Set the sprite size and location on map
	SDL_Rect TileRect = {(int)(f_x - offSetX * width),
						 (int)(f_y - offSetY * height),
						 width,
						 height};


	//Draw the tile to the screen
	SDL_RenderCopy(renderer, tileSheet, &TileScr, &TileRect);

	return;
}








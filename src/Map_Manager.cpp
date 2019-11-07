//============================================================================
// Name       		: Map_Manager.cpp
// Author     		: Thomas Hooks
// Version    		: 1
// Last Modified	: 11/2/2019
// Description		:
//============================================================================




#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Game.h"
#include "Map_Manager.h"
#include "Game_Map.h"




Map_Manager::Map_Manager(class Game *game_ptr) : Game_Manager(game_ptr) {
	//
	n_scale = 1;

	//
	n_visible_tiles_x = 0;
	n_visible_tiles_y = 0;

	return;
}


Map_Manager::~Map_Manager() {
	//Do nothing
}


void Map_Manager::Draw(void){
	/*
	 *
	 */




	//Calculate the number of tile that are visible on screen
	n_visible_tiles_x = (game->get_windowWidth())/get_tileWidth() + 1;
	n_visible_tiles_y = (game->get_windowHeight())/get_tileHeight();


	//Calculate the top-left visible tile on screen
	float f_offset_x = game->get_cameraX()/get_tileWidth()
			- (float)n_visible_tiles_x/2.0f;

	float f_offset_y = game->get_cameraY()/get_tileHeight()
			- (float)n_visible_tiles_y/2.0f;


	//Keep camera inside of the game window boundaries
	const int leftBoundary = 0, topBoundary = 0;

	if(f_offset_x < leftBoundary) f_offset_x = leftBoundary;

	if(f_offset_y < topBoundary) f_offset_y = topBoundary;

	if(f_offset_x > get_width() - n_visible_tiles_x)
		f_offset_x = get_width() - n_visible_tiles_x;

	if(f_offset_y > get_height() - n_visible_tiles_y)
		f_offset_y = get_height() - n_visible_tiles_y;


	//Draw the map that is currently at the top of the stack
	v_stack.back()->Draw(game->get_renderer(), game->Assets.get_texture("tile_test.png"),
			n_visible_tiles_x, n_visible_tiles_y, f_offset_x,
			f_offset_y, n_scale);

	return;
}


//============================================================================





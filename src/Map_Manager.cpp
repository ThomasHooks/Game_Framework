//============================================================================
// Name       		: Map_Manager.cpp
// Author     		: Thomas Hooks
// Version    		: 1
// Last Modified	: 11/16/2019
// Description		:
//============================================================================




#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Game.h"
#include "Map_Manager.h"
#include "Game_Map.h"




Map_Manager::Map_Manager(class Game *game_ptr)
	: b_hasBeenInit(false),
	  n_visible_tiles_x(0),
	  n_visible_tiles_y(0),
	  n_scale(1),
	  game(game_ptr),
	  log(nullptr),
	  assets(nullptr){
	//Initialize the Map Manager object

	return;
}



Map_Manager::~Map_Manager() {
	//Do nothing
	return;
}



void Map_Manager::init(class Game_Logger *log_ptr, class Asset_Manager *assets_ptr){
	/*
	 * brief		This method initializes the map manager
	 *
	 * param		assets_ptr		pointer to the asset manager
	 *
	 * param		log_ptr			pointer to the logger
	 *
	 * This method will initialize the map manger only once and must be
	 * called before any maps can be added or removed
	 */




	if(!b_hasBeenInit){
		//Only initialize once

		log = log_ptr;

		assets = assets_ptr;

		b_hasBeenInit = true;
	}

	return;
}


//----------------------------------------------------------------------------


void Map_Manager::push_map(std::string tileSheetKey, std::string mapFilePath){
	/*
	 * brief	Adds a new element to the back of the map stack
	 */



	if(!b_hasBeenInit) return;


	v_stack.emplace_back(std::unique_ptr<Game_Map>(new Game_Map(tileSheetKey)));


	v_stack.back()->LoadMap(mapFilePath);


	return;
}


//----------------------------------------------------------------------------


void Map_Manager::pop_map(void){
	/*
	 * brief	Removes the back element from the map stack
	 */



	if(!b_hasBeenInit) return;


	if(v_stack.empty()){

		log->Message(Level::Warning,
						 "Tried to free element, but map stack is empty!",
						 Output::File_txt);
	}

	else v_stack.pop_back();


	return;
}


//----------------------------------------------------------------------------


void Map_Manager::draw(int windowWidth,
					   int windowHeight,
					   float camera_x,
					   float camera_y,
					   struct SDL_Renderer *renderer_ptr) {
	/*
	 *
	 */



	if(!b_hasBeenInit) return;


	//Calculate the number of tile that are visible on screen
	//The x axis is over drawn by 1 to prevent texture popping
	n_visible_tiles_x = (windowWidth)/get_tileWidth() + 1;
	n_visible_tiles_y = (windowHeight)/get_tileHeight();


	//Calculate the top-left visible tile on screen
	float f_offset_x = camera_x/get_tileWidth()
			- (float)n_visible_tiles_x/2.0f;

	float f_offset_y = camera_y/get_tileHeight()
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
	v_stack.back()->Draw(renderer_ptr,
						 assets->get_texture(v_stack.back()->sMapName),
						 n_visible_tiles_x,
						 n_visible_tiles_y,
						 f_offset_x,
						 f_offset_y,
						 n_scale);

	return;
}








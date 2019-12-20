//============================================================================
// Name       		: Map_Manager.cpp
// Author     		: Thomas Hooks
// Last Modified	: 12/19/2019
//============================================================================




#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "Game.h"
#include "Map_Manager.h"
#include "Game_Map.h"




Map_Manager::Map_Manager()
	: b_hasBeenInit(false),
	  n_visible_tiles_x(0),
	  n_visible_tiles_y(0),
	  n_scale(1),
	  log(nullptr),
	  assets(nullptr){

	/* The method 'init' must be called when using this constructor
	 * before using the map_manager object
	 */

	return;
}



Map_Manager::Map_Manager(class Game_Logger *log_ptr, class Asset_Manager *assets_ptr)
	: b_hasBeenInit(true),
	  n_visible_tiles_x(0),
	  n_visible_tiles_y(0),
	  n_scale(1),
	  log(log_ptr),
	  assets(assets_ptr){

	log->Message(Level::Info,
				 "Map Manager has been initialized",
				 Output::File_txt);

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

		log->Message(Level::Info,
					 "Map Manager has been initialized",
					 Output::File_txt);
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


	v_stack.back()->loadMap(mapFilePath);


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
	 * brief	draws the map at the back of the stack
	 *
	 * parma	windowWidth		width of the game window
	 *
	 * parma	windowHeight	height of the game window
	 *
	 * parma	camera_x		x coordinate of the camera
	 *
	 * parma	camera_y		y coordinate of the camera
	 *
	 * parma	renderer_ptr	pointer to the game renderer
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
	v_stack.back()->draw(renderer_ptr,
						 assets->get_texture(v_stack.back()->mapName),
						 n_visible_tiles_x,
						 n_visible_tiles_y,
						 f_offset_x,
						 f_offset_y,
						 n_scale);

	return;
}


//----------------------------------------------------------------------------


void Map_Manager::set_scale(int scale){
	/*
	 * brief	sets the map's scale with the given amount
	 *
	 * parma	scale	the map's new scale
	 */



	static int MIN_SCALE = 1;

	if(scale < MIN_SCALE){
		this->n_scale = MIN_SCALE;
	}
	else this->n_scale = scale;

	return;
}








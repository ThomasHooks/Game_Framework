//============================================================================
// Name       		: MapManager.cpp
// Author     		: Thomas Hooks
// Last Modified	: 12/19/2019
//============================================================================




#include "MapManager.h"

#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "Game_Map.h"
#include "Game.h"




MapManager::MapManager()
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



MapManager::MapManager(class Game_Logger *log_ptr, class Asset_Manager *assets_ptr)
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



MapManager::~MapManager() {
	//Do nothing
	return;
}



void MapManager::init(class Game_Logger *log_ptr, class Asset_Manager *assets_ptr){
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


void MapManager::push_map(std::string tileSheetKey, std::string mapFilePath){
	/*
	 * brief	Adds a new element to the back of the map stack
	 */



	if(!b_hasBeenInit) return;


	v_stack.emplace_back(std::unique_ptr<Game_Map>(new Game_Map(tileSheetKey)));


	v_stack.back()->loadMap(mapFilePath);


	return;
}


//----------------------------------------------------------------------------


void MapManager::pop_map(void){
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


void MapManager::draw(float offsetHor,
					   float offsetVer,
					   int visibleTilesHor,
					   int visibleTilesVer,
					   struct SDL_Renderer *renderer_ptr) {
	/*
	 * brief	draws the map at the back of the stack
	 *
	 * parma	offsetHor			X coordinate of the top left tile
	 *
	 * parma	offsetVer			Y coordinate of the top left tile
	 *
	 * parma	visibleTilesHor		number of horizontal tiles on screen
	 *
	 * parma	visibleTilesVer		number of vertical tiles on screen
	 *
	 * parma	renderer_ptr		pointer to the game renderer
	 */



	if(!b_hasBeenInit) return;

	//Draw the map that is currently at the top of the stack
	v_stack.back()->draw(renderer_ptr,
						 assets->get_texture(v_stack.back()->mapName),
						 visibleTilesHor,
						 visibleTilesVer,
						 offsetHor,
						 offsetVer,
						 n_scale);

	return;
}


//----------------------------------------------------------------------------


void MapManager::set_scale(int scale){
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








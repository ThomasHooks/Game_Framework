//============================================================================
// Name       		: MapManager.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/08/2020
//============================================================================




#include "MapManager.h"

#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "../world/GameMap.h"
#include "../Game.h"
#include "../utilities/Dimension.h"
#include "../utilities/Position.h"
#include "RendererManager.h"




MapManager::MapManager()
	: hasBeenInit(false),
	  visibleTilesX(0),
	  visibleTilesY(0),
	  scale(1),
	  logger(nullptr) {

	/* The method 'init' must be called when using this constructor
	 * before using the map_manager object
	 */
}



MapManager::MapManager(class GameLogger *log_ptr)
	: hasBeenInit(true),
	  visibleTilesX(0),
	  visibleTilesY(0),
	  scale(1),
	  logger(log_ptr) {

	logger->message(Level::INFO,
				 "Map Manager has been initialized",
				 Output::TXT_FILE);
}



MapManager::~MapManager() {}



void MapManager::init(class GameLogger *log_ptr){
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




	if(!hasBeenInit){

		logger = log_ptr;
		hasBeenInit = true;
		logger->message(Level::INFO, "Map Manager has been initialized", Output::TXT_FILE);
	}

	return;
}



void MapManager::push_map(std::string tileSheetKey, std::string mapFilePath){
	/*
	 * brief	Adds a new element to the back of the map stack
	 */



	if(!hasBeenInit) return;


	mapStack.emplace_back(std::unique_ptr<GameMap>(new GameMap(tileSheetKey)));


	mapStack.back()->loadMap(mapFilePath);


	return;
}



void MapManager::pop_map(void){
	/*
	 * brief	Removes the back element from the map stack
	 */



	if(!hasBeenInit) return;


	if(mapStack.empty()){

		logger->message(Level::WARNING,
					 "Tried to free element, but map stack is empty!",
					 Output::TXT_FILE);
	}

	else mapStack.pop_back();


	return;
}



void MapManager::draw(const Position &cameraPos, const Dimension &visibleTiles, RendererManager &renderer){
	/*
	 *
	 */




	if(this->hasBeenInit){

		std::string tag = mapStack.back()->mapName;
		//Over rendering is done to prevent artifacts along the edge of the screen
		for(int y = -1; y < visibleTiles.height; y++){
			for(int x = -1; x < visibleTiles.width; x++){
				int xCord = x + cameraPos.xPosN();
				int yCord = y + cameraPos.yPosN();
				//This is to prevent the map from being indexed out of
				//Note that this can cause some tiles to be rendered twice
				if(xCord < 0) xCord = 0;
				if(yCord < 0) yCord = 0;
				Position tilePos = mapStack.back()->getTilePosition(xCord, yCord);
				Dimension tileSprite(mapStack.back()->get_tileIndex(xCord, yCord), 0);

				renderer.drawSprite(tag, tilePos, cameraPos, tileSprite, false);
			}
		}
	}
}



void MapManager::set_scale(int scale){
	/*
	 * @parma	scale The map's new scale
	 *
	 * Sets the map's scale with the given amount
	 */



	static int MINSCALE = 1;
	scale < MINSCALE ? this->scale = MINSCALE : this->scale = scale;
}








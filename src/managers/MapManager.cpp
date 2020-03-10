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
	  logger(nullptr) {}



MapManager::MapManager(class GameLogger *log_ptr)
	: hasBeenInit(true),
	  logger(log_ptr) {

	logger->message(Level::INFO,
				 "Map Manager has been initialized",
				 Output::TXT_FILE);
}



MapManager::~MapManager() {}



void MapManager::init(class GameLogger *log_ptr){
	/*
	 * @param	assets_ptr Pointer to the asset manager
	 *
	 * @param	log_ptr Pointer to the logger
	 *
	 * Initializes the Map Manager only once and must be called before any maps can be added or removed
	 */




	if(!hasBeenInit){
		logger = log_ptr;
		hasBeenInit = true;
		logger->message(Level::INFO, "Map Manager has been initialized", Output::TXT_FILE);
	}
}



void MapManager::pushMap(std::string tileSheetTag, std::string mapFilePath){
	/*
	 * @param	tileSheetTag The map's/sprite sheet's tag
	 *
	 * @param	mapFilePath The location of the map's sprite sheet
	 *
	 * Adds a new map to the back of the stack
	 */




	if(hasBeenInit){
		mapStack.emplace_back(std::unique_ptr<GameMap>(new GameMap(tileSheetTag)));
		mapStack.back()->loadMap(mapFilePath);
	}
}



void MapManager::popMap(){
	/*
	 * Removes the back map from the stack
	 */




	if(hasBeenInit) {

		if(mapStack.empty())logger->message(Level::WARNING, "Tried to free map, but map stack is empty!", Output::TXT_FILE);

		else mapStack.pop_back();
	}
}



void MapManager::draw(const Position &cameraPos, const Dimension &visibleTiles, RendererManager &renderer){
	/*
	 * @param	cameraPos The position of the camera
	 *
	 * @param	visibleTiles Number of visible tiles on screen
	 *
	 * @param	renderer Reference to the Renderer Manager
	 *
	 * Draws the active map to the screen
	 */




	if(this->hasBeenInit){

		std::string tag = mapStack.back()->getTag();
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
				Dimension tileSprite(mapStack.back()->getTileSprite(xCord, yCord), 0);

				renderer.drawSprite(tag, tilePos, cameraPos, tileSprite, false);
			}
		}
	}
}



int MapManager::getTileSolid(int x, int y) const {
	/*
	 * @param	x The X coordinate of the tile in map space
	 *
	 * @param	y The Y coordinate of the tile in map space
	 *
	 * @return If the tile is solid or not
	 */




	return mapStack.back()->isTileSolid(x, y);
}



void MapManager::setTileSolid(int x, int y, bool solid){
	/*
	 * @param	x The X coordinate of the tile in map space
	 *
	 * @param	y The Y coordinate of the tile in map space
	 *
	 * @param 	solid The tile's new solid state
	 *
	 * Changes the given tile's solid state
	 */




	mapStack.back()->setTileSolid(x, y, solid);
}



int MapManager::getTileSprite(int x, int y) const {
	/*
	 * @param	x The X coordinate of the tile in map space
	 *
	 * @param	y The Y coordinate of the tile in map space
	 *
	 * @return 	The tile's sprite's location in the sprite sheet
	 */




	return mapStack.back()->getTileSprite(x, y);
}



int MapManager::getWidth() const {
	return mapStack.back()->getWidth();
}



int MapManager::getHeight() const {
	return mapStack.back()->getHeight();
}



const Dimension& MapManager::getSize() const {
	return mapStack.back()->getSize();
}



int MapManager::getTileWidth() const {
	return mapStack.back()->getTileWidth();
}



int MapManager::getTileHeight() const {
	return mapStack.back()->getTileHeight();
}



const Dimension& MapManager::getTileSize() const {
	return mapStack.back()->getTileSize();
}



std::string MapManager::getTag() const {
	return mapStack[mapStack.size()]->getTag();
}








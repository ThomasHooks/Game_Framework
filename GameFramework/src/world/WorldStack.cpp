//============================================================================
// Name       		: WorldStack
// Author     		: Thomas Hooks
// Last Modified	: 03/21/2020
//============================================================================





#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "../renderer/Renderer.h"
#include "../utilities/physics/Dimension.h"
#include "../utilities/physics/Position.h"
#include "../world/WorldStack.h"

#include "../utilities/Logger.h"
#include "../world/TileMap.h"




WorldStack::WorldStack(class Logger *log_ptr)
	: logger(log_ptr) {

	logger->message(Logger::Level::INFO,
				 "Map Manager has been initialized",
				 Logger::Output::TXT_FILE);
}



WorldStack::~WorldStack() {}



/*
 * @param	tileSheetTag The map's/sprite sheet's tag
 *
 * @param	mapFilePath The location of the map's sprite sheet
 *
 * Adds a new map to the back of the world stack
 */
void WorldStack::pushMap(std::string tileSheetTag, std::string mapFilePath){
	worldStack.emplace_back(std::unique_ptr<TileMap>(new TileMap(logger, tileSheetTag, mapFilePath)));
}



//Removes the back world from the stack
void WorldStack::popMap(){
	worldStack.empty() ? logger->message(Logger::Level::WARNING, "Tried to free map, but map stack is empty!", Logger::Output::TXT_FILE) : worldStack.pop_back();
}



/*
 * @param	cameraPos The position of the camera
 *
 * @param	windowSize Size of the window
 *
 * @param	renderer Reference to the Renderer Manager
 *
 * Draws the active map to the screen
 */
void WorldStack::draw(const Position &cameraPos, const Dimension &windowSize, Renderer &renderer){
	
	TileMap* world = this->getWorld();
	if(world == nullptr) {
		logger->message(Logger::Level::FATAL, "Null Pointer exception: Tried to render World, but world stack is empty!", Logger::Output::TXT_FILE);
		return;
	}

	//Calculate the top-left visible tile
	Dimension tileSize(world->tileWidth(), world->tileHeight());
	Dimension numberOfVisibleTiles(windowSize.width/tileSize.width + 1, windowSize.height/tileSize.height);
	double offsetX = cameraPos.xPos()/tileSize.width;
	double offsetY = cameraPos.yPos()/tileSize.height;
	
	//Keep the camera inside the World boundaries
	if(offsetX < 0) offsetX = 0;

	if(offsetY < 0) offsetY = 0;

	if(offsetX > world->width() - numberOfVisibleTiles.width)
		offsetX = world->width() - numberOfVisibleTiles.width;

	if(offsetY > world->height() - numberOfVisibleTiles.height)
		offsetY = world->height() - numberOfVisibleTiles.height;

	Position tileOffset(offsetX, offsetY);
	//Over rendering is done to prevent artifacts along the edge of the screen
	for(int y = -1; y < numberOfVisibleTiles.height; y++) {
		for(int x = -1; x < numberOfVisibleTiles.width; x++) {
			int xCord = x + tileOffset.xPosN();
			int yCord = y + tileOffset.yPosN();
			/*
			 * This is to prevent the map from being indexed out of
			 * also doing this can cause some tiles to be rendered more than once
			 */
			if(xCord < 0) xCord = 0;
			else if(xCord > world->width()) xCord = world->width();

			if(yCord < 0) yCord = 0;
			else if(yCord > world->height()) yCord = world->height();

			ITile *tile = world->getTile(xCord, yCord);

			if(tile == nullptr) {
				//std::string xLocation = std::to_string(xCord);
				//std::string yLocation = std::to_string(yCord);
				logger->message(Logger::Level::WARNING,
						"Null Pointer exception: Tried to get tile, but tile does not exist",
						Logger::Output::TXT_FILE);
			}
			else {
				renderer.drawSprite(world->getTag(), tile->getPos(), cameraPos, tile->getSprite(), false);
			}
		}
	}
}



/*
 * @return	The current world or null if there are no maps
 *
 * Gets the current world
 */
class TileMap* WorldStack::getWorld(){
	return this->worldStack.empty() ? nullptr : this->worldStack.back().get();
}








//============================================================================
// Name       		: TileMap.h
// Author     		: Thomas Hooks
// Last Modified	: 03/21/2020
//============================================================================




#include <iostream>
#include <sstream>
#include <fstream>

#include "TileMap.h"
#include "../utilities/GameLogger.h"




TileMap::TileMap(class GameLogger *loggerIn, const std::string &tagIn, const std::string &filePath)
	: logger(loggerIn),
	  tag(tagIn),
	  sizeMap(),
	  sizeTile() {

	this->buildTileMap(filePath);
}



TileMap::~TileMap() {}



/*
 * @return	Size of the world
 *
 * Gets the TileMaps size in tile-space
 */
const Dimension& TileMap::size()const {
	return this->sizeMap;
}



/*
 * @return	Width of the TileMap
 *
 * Gets the TileMaps width in tile-space
 */
int TileMap::width() const {
	return this->sizeMap.width;
}



/*
 * @return	Height of the TileMap
 *
 * Gets the TileMaps height in tile-space
 */
int TileMap::height() const {
	return this->sizeMap.height;
}



//Gets the TileMaps tile size
const Dimension& TileMap::tileSize() const {
	return this->sizeTile;
}



//Gets the TileMaps tile width
int TileMap::tileWidth() const {
	return this->sizeTile.width;
}



//Gets the TileMaps tile height
int TileMap::tileHeight() const {
	return this->sizeTile.height;
}



//Gets the TileMap's tag
const std::string& TileMap::getTag() const {
	return this->tag;
}



/*
 * @nullable
 *
 * @param	posIn The coordinates of the Tile
 *
 * @return	The Tile at that location or null if the Tile does not exist
 */
ITile* TileMap::getTile(const Position& posIn) {
	return this->getTile(posIn.xPos(), posIn.yPos());
}



/*
 * @nullable
 *
 * @param	x, y The tile-space coordinates of the Tile
 *
 * @return	The Tile at that location or null if the Tile does not exist
 */
ITile* TileMap::getTile(int x, int y) {
	return (std::abs(x) > this->width() || std::abs(y) > this->height()) ? nullptr : &this->tileMap[x][y];
}



/*
 * @nullable
 *
 * @param	x, y The coordinates of the Tile
 *
 * @return	The Tile at that location or null if the Tile does not exist
 */
ITile* TileMap::getTile(double x, double y) {
	return this->getTile(static_cast<int>(x/this->tileWidth() + 0.5), static_cast<int>(y/this->tileHeight() + 0.5));
}



/*
 * @param	filePath Path to the tile map file
 *
 * Creates a tile map using the given filePath
 */
void TileMap::buildTileMap(const std::string &filePath){

	logger->message(Level::INFO, "Building map '" + this->tag + "' at '" + filePath + "'", Output::TXT_FILE);

	std::ifstream mapFile(filePath);
	if(!mapFile.is_open()){
		logger->message(Level::ERROR, "Unable to load/find map '" + this->tag + "' at '" + filePath + "'", Output::TXT_FILE);
		return;
	}

	//Read the map size from the file
	int mapWidth = 0;
	mapFile>>mapWidth;
	this->sizeMap.width = mapWidth;
	int mapHeight = 0;
	mapFile>>mapHeight;
	this->sizeMap.height = mapHeight;
	if(mapFile.fail()) logger->message(Level::ERROR, "Unable to read map '" + this->tag + "' at MAPSIZE", Output::TXT_FILE);

	//Read the tile size from the file
	int tileWidth = 0;
	mapFile>>tileWidth;
	this->sizeTile.width = tileWidth;
	int tileHeight = 0;
	mapFile>>tileHeight;
	this->sizeTile.height = tileHeight;
	if(mapFile.fail()) logger->message(Level::ERROR, "Unable to read map '" + this->tag + "' at TILESIZE", Output::TXT_FILE);

	//Read the tile and add it to the tile map
	for(int y = 0; y < sizeMap.height; y++){
		this->tileMap.push_back(std::vector<ITile>());
		for(int x = 0; x < sizeMap.width; x++){
			bool opaque = true;
			bool solid = false;
			EnumSide pass = EnumSide::NONE;
			Dimension sprite(0, 0);
			mapFile>>sprite.width;
			if(mapFile.fail()) logger->message(Level::ERROR, "Unable to read map '" + this->tag + "' at TILESPRITE", Output::TXT_FILE);
			if(sprite.width > 1) solid = true;
			this->tileMap[y].push_back(ITile(x * sizeTile.width,
					y * sizeTile.height,
					sizeTile.width,
					sizeTile.height,
					sprite,
					pass,
					opaque,
					solid));
		}
	}
	logger->message(Level::INFO, "Map '" + this->tag + "' has been built", Output::TXT_FILE);
}








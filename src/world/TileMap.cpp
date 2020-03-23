//============================================================================
// Name       		: TileMap.h
// Author     		: Thomas Hooks
// Last Modified	: 03/22/2020
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



TileMap::~TileMap() {
	logger->message(Level::INFO, "World '"+ this->tag + "' has been removed", Output::TXT_FILE);
}



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

	if(x < 0 || x > this->width() || y < 0 || y > this->height()) return nullptr;
	auto itr = this->tileMap.find({x, y});
	return itr == this->tileMap.end() ? nullptr : &itr->second;
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
 * @nullable
 *
 * @param	posIn The coordinates to be offset by one tile
 *
 * @param	direction The offset direction
 *
 * @return	The Tile offset from that location or null if the Tile does not exist
 */
ITile* TileMap::getOffsetTile(const Position& posIn, EnumSide direction){

	switch(direction){

	case EnumSide::UP:
		return this->getTile(posIn.xPos(), posIn.yPos() - this->tileHeight());

	case EnumSide::RIGHT:
		return this->getTile(posIn.xPos() + this->tileWidth(), posIn.xPos());

	case EnumSide::DOWN:
		return this->getTile(posIn.xPos(), posIn.yPos() + this->tileHeight());

	case EnumSide::LEFT:
		return this->getTile(posIn.xPos() - this->tileWidth(), posIn.yPos());

	default:
		return nullptr;
	}
}



/*
 * @param	filePath Path to the tile map file
 *
 * Creates a tile map using the given filePath
 */
void TileMap::buildTileMap(const std::string &filePath){

	logger->message(Level::INFO, "Building World '" + this->tag + "' at '" + filePath + "'", Output::TXT_FILE);

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
	for(int y = 0; y < sizeMap.height; y++) {
		for(int x = 0; x < sizeMap.width; x++) {
			bool opaque = true;
			bool solid = false;
			EnumSide pass = EnumSide::NONE;
			Dimension sprite(0, 0);

			int index = 0;
			mapFile>>index;
			sprite.width = index;
			if(mapFile.fail()) {
				logger->message(Level::ERROR, "Unable to read map '" + this->tag + "' at TILESPRITE", Output::TXT_FILE);
				return;
			}

			if(sprite.width > 1) solid = true;
			this->tileMap.insert({{x, y}, ITile(x * sizeTile.width,
					y * sizeTile.height,
					sizeTile.width,
					sizeTile.height,
					sprite,
					pass,
					opaque,
					solid)});
		}
	}
	logger->message(Level::INFO, "World '" + this->tag + "' has been built", Output::TXT_FILE);
}








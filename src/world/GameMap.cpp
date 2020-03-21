//============================================================================
// Name       		: GameMap.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/09/2020
//============================================================================




#include "GameMap.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#include "Tile.h"
#include "../utilities/Position.h"
#include "../utilities/Dimension.h"




GameMap::GameMap(std::string name)
	: mapWidth(5),
	  mapHeight(5),
	  tileWidth(32),
	  tileHeight(32),
	  mapSize(mapWidth, mapHeight),
	  tileSize(32, 32),
	  mapTag(name) {}



GameMap::~GameMap() {}



bool GameMap::isTileSolid(int x, int y) const {
	/*
	 * @param	x Specifies the tile's X coordinate in the map
	 *
	 * @param	y Specifies the tile's Y coordinate in the map
	 *
	 * @return True if the given tile is solid
	 *
	 * Checks if a tile is solid
	 */




	if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight && !tileMap.empty())
		return tileMap[x][y].isSolid();
	else return false;
}



void GameMap::setTileSolid(int x, int y, bool solid){
	/*
	 * @param	x Specifies the tile's X coordinate in the map
	 *
	 * @param	y Specifies the tile's Y coordinate in the map
	 *
	 * @param	solid Specifies if the tile is solid or not
	 *
	 * Sets the give tile's solid state
	 */




	if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight && !tileMap.empty())
		//Check if the tile is a valid tile if it is set the tile
		tileMap[x][y].setSolidState(solid);


	return;
}



int GameMap::getTileSprite(int x, int y){
	/*
	 * @param	x The tile's X coordinate in the map
	 *
	 * @param	y The tile's Y coordinate in the map
	 *
	 * @return The location of the tile's sprite
	 */




	if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight && !tileMap.empty())
		//Check if the tile is a valid tile if it is set the tile
		return tileMap[x][y].n_tileIndex;

	else return 0;
}



void GameMap::setTileSprite(int x, int y, int index){
	/*
	 * @param	x The tile's X coordinate in the map
	 *
	 * @param	y The tile's Y coordinate in the map
	 *
	 * @param	index The location of the tile's sprite in the sprite sheet
	 *
	 * Changes the given tile's sprite
	 */




	if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight && !tileMap.empty())
		//Check if the tile is a valid tile if it is set the tile
		tileMap[x][y].n_tileIndex = index;
}



Position GameMap::getTilePosition(int x, int y){
	return Position(tileMap[x][y].f_x, tileMap[x][y].f_y);
}



int GameMap::getWidth() const {
	return mapWidth;
}



int GameMap::getHeight() const {
	return mapHeight;
}



const Dimension& GameMap::getSize() const {
	return this->mapSize;
}



int GameMap::getTileWidth() const {
	return tileWidth;
}



int GameMap::getTileHeight() const {
	return tileHeight;
}



const Dimension& GameMap::getTileSize() const {
	return this->tileSize;
}



const std::string& GameMap::getTag() const {
	return mapTag;
}



bool GameMap::loadMap(std::string FileName){
	/*
	 * @param	FileName Path to the tile map file
	 *
	 * @return True if successful and False if it fails to load
	 *
	 * load the map file given by the user
	 */




	bool bMapLoaded = true;		//Flag for map loading

	//Try to load map file
	std::ifstream map(FileName);

	if(!map.is_open()){
		//Map file failed to load
		std::cout<<"*Error* Unable to load map file: "
				<<FileName<<std::endl;
		bMapLoaded = false;
	}
	else{
		//Map file was successfully loaded
		//Read map size
		map>>mapWidth;
		map>>mapHeight;
		mapSize.width = mapWidth;
		mapSize.height = mapHeight;

		//Read tile size
		map>>tileWidth;
		map>>tileHeight;
		tileSize.width = tileWidth;
		tileSize.height = tileHeight;

		if(map.fail()){
			//Check if there was a problem reading the map file
			std::cout<<"*Error* Unable to read map file: "
					<<FileName<<std::endl;
			bMapLoaded = false;
		}
		else{
			//Resize the tile map with the data provided in the map file
			tileMap.clear();
			tileMap.resize(mapWidth, std::vector<Tile>(tileHeight, Tile{false, 0, 0, 0}));
		}

		//Populate map with tiles
		for(int y = 0; y < mapHeight && bMapLoaded; y++){
			for(int x = 0; x < mapWidth && bMapLoaded; x++){
				//This specifies if the tile is solid
				bool bTileSolid = false;
				//map>>bTileSolid;

				//This specifies which tile to use from the tile sprite sheet
				int nTileIndex = 0;
				map>>nTileIndex;

				if(map.fail()){
					//Check if there was a problem reading the map file
					std::cout<<"*Error* Unexpected end of map file: "
							<<FileName<<std::endl;
					bMapLoaded = false;
					break;
				}
				else{
					//Populate tile data

					//----All of this should be removed later----
					if(nTileIndex > 1) bTileSolid = true;
					//----All of this should be removed later----

					tileMap[x][y].setSolidState(bTileSolid);
					tileMap[x][y].n_tileIndex = nTileIndex;
					tileMap[x][y].f_x = (float)(x * tileWidth);
					tileMap[x][y].f_y = (float)(y * tileHeight);
				}
			}
		}
	}

	return bMapLoaded;
}



void GameMap::setWidth(const int width){
	width > 0 ? this->mapWidth = width : this->mapWidth = 1;
}



void GameMap::setHeight(const int height){
	height > 0 ? this->mapHeight = height : this->mapHeight = 1;
}



void GameMap::setSize(const Dimension &sizeIn){
	sizeIn.width > 0 ? this->mapSize.width = sizeIn.width : this->mapSize.width = 1;
	sizeIn.height > 0 ? this->mapSize.height = sizeIn.height : this->mapSize.height = 1;
}








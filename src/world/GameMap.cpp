//============================================================================
// Name       		: GameMap.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/08/2020
//============================================================================




#include "GameMap.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#include <SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include "../Game.h"
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
	  mapName(name) {}



GameMap::~GameMap() {}



bool GameMap::is_tileSolid(int x, int y){
	/*
	 * brief	Checks if a tile is solid
	 *
	 * param	x	Specifies the tile's X coordinate in the map
	 *
	 * param	y	Specifies the tile's Y coordinate in the map
	 *
	 */




	if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight && !tileMap.empty())
		return tileMap[x][y].isSolid();
	else return false;
}



void GameMap::set_tileSolid(int x, int y, bool solid){
	/*
	 * brief	This method will set the give tile's solid state
	 *
	 *
	 * param	x		Specifies the tile's X coordinate in the map
	 *
	 * param	y		Specifies the tile's Y coordinate in the map
	 *
	 * param	solid	Specifies if the tile is solid or not
	 *
	 * */




	if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight && !tileMap.empty())
		//Check if the tile is a valid tile if it is set the tile
		tileMap[x][y].setSolidState(solid);


	return;
}



int GameMap::get_tileIndex(int x, int y){
	/*
	 *
	 */




	if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight && !tileMap.empty())
		//Check if the tile is a valid tile if it is set the tile
		return tileMap[x][y].n_tileIndex;

	else return 0;
}



void GameMap::set_tileIndex(int x, int y, int index){
	/*
	 *
	 */




	if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight && !tileMap.empty())
		//Check if the tile is a valid tile if it is set the tile
		tileMap[x][y].n_tileIndex = index;
}



Position GameMap::getTilePosition(int x, int y){
	/*
	 *
	 */




	return Position(tileMap[x][y].f_x, tileMap[x][y].f_y);
}



bool GameMap::loadMap(std::string FileName){
	/*
	 * brief	This method load the map file given by the user and will return
	 * 		    true if successful, false otherwise
	 *
	 *
	 * param	FileName	Path to the tile map file
	 *
	 * */




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



const Dimension& GameMap::getSize() const {
	return this->mapSize;
}



const Dimension& GameMap::getTileSize() const {
	return this->tileSize;
}








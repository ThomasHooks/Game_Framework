//============================================================================
// Name       		: GameMap.cpp
// Author     		: Thomas Hooks
// Last Modified	: 12/19/2019
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




GameMap::GameMap(std::string name)
	: n_mapWidth(5),
	  n_mapHeight(5),
	  n_tileWidth(32),
	  n_tileHeight(32),
	  mapName(name){

	return;
}





GameMap::~GameMap() {
	return;
}





bool GameMap::is_tileSolid(int x, int y){
	/*
	 * brief	Checks if a tile is solid
	 *
	 * param	x	Specifies the tile's X coordinate in the map
	 *
	 * param	y	Specifies the tile's Y coordinate in the map
	 *
	 */




	if (x >= 0 && x < n_mapWidth && y >= 0 && y < n_mapHeight && !v_tileMap.empty())
		return v_tileMap[x][y].b_solid;
	else return false;
}


//----------------------------------------------------------------------------


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




	if (x >= 0 && x < n_mapWidth && y >= 0 && y < n_mapHeight && !v_tileMap.empty())
		//Check if the tile is a valid tile if it is set the tile
		v_tileMap[x][y].b_solid = solid;


	return;
}


//----------------------------------------------------------------------------


int GameMap::get_tileIndex(int x, int y){
	/*
	 *
	 */




	if (x >= 0 && x < n_mapWidth && y >= 0 && y < n_mapHeight && !v_tileMap.empty())
		//Check if the tile is a valid tile if it is set the tile
		return v_tileMap[x][y].n_tileIndex;

	else return 0;
}


//----------------------------------------------------------------------------


void GameMap::set_tileIndex(int x, int y, int index){
	/*
	 *
	 */




	if (x >= 0 && x < n_mapWidth && y >= 0 && y < n_mapHeight && !v_tileMap.empty())
		//Check if the tile is a valid tile if it is set the tile
		v_tileMap[x][y].n_tileIndex = index;
}


//----------------------------------------------------------------------------


void GameMap::draw(SDL_Renderer *renderer, SDL_Texture *tTileSheet,
		int nVisibleTilesX, int nVisibleTilesY, float fOffSetX,
		float fOffSetY, int scale){
	//

	//Loop through the map and draw only the visible tiles
	for(int y = 0; y < nVisibleTilesY; y++){
		for(int x = 0; x < nVisibleTilesX; x++){
			v_tileMap[x + (int)fOffSetX][y + (int)fOffSetY].draw(renderer,
					tTileSheet, n_tileWidth, n_tileHeight, scale,
					fOffSetX, fOffSetY);
		}
	}
	return;
}


//----------------------------------------------------------------------------


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
		map>>n_mapWidth;
		map>>n_mapHeight;

		//Read tile size
		map>>n_tileWidth;
		map>>n_tileHeight;

		if(map.fail()){
			//Check if there was a problem reading the map file
			std::cout<<"*Error* Unable to read map file: "
					<<FileName<<std::endl;
			bMapLoaded = false;
		}
		else{
			//Resize the tile map with the data provided in the map file
			v_tileMap.clear();
			v_tileMap.resize(n_mapWidth,
					std::vector<Tile>(n_tileHeight,
							Tile{false, 0, 0, 0}));
		}

		//Populate map with tiles
		for(int y = 0; y < n_mapHeight && bMapLoaded; y++){
			for(int x = 0; x < n_mapWidth && bMapLoaded; x++){
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

					v_tileMap[x][y].b_solid = bTileSolid;
					v_tileMap[x][y].n_tileIndex = nTileIndex;
					v_tileMap[x][y].f_x = (float)(x * n_tileWidth);
					v_tileMap[x][y].f_y = (float)(y * n_tileHeight);
				}
			}
		}
	}

	return bMapLoaded;
}








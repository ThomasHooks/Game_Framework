//============================================================================
// Name       		: Game_Map.cpp
// Author     		: Thomas Hooks
// Version    		: 1
// Last Modified	: 11/16/2019
// Description		:
//============================================================================




#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#include <SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include "Game.h"
#include "Game_Map.h"
#include "Game_Tile.h"




Game_Map::Game_Map(std::string name) {
	//

	nMapWidth = 5; nMapHeight= 5;
	sMapName = name;
	nTileWidth = 32; nTileHeight = 32;

	return;
}





Game_Map::~Game_Map() {
	//

	return;
}





bool Game_Map::IsTileSoilid(int x, int y){
	/*
	 *
	 */




	if (x >= 0 && x < nMapWidth && y >= 0 && y < nMapHeight && !v_tileMap.empty())
		return v_tileMap[x][y].b_solid;
	else return false;
}


//----------------------------------------------------------------------------


void Game_Map::SetTileSoilid(int x, int y, bool solid){
	/*
	 * *brief*			This method will set the give tile's solid state
	 *
	 *
	 * *param: x*		specifies the tile's X coordinate in the map
	 * *param: y*		specifies the tile's Y coordinate in the map
	 * *param: solid*	specifies if the tile is solid or not
	 * */




	if (x >= 0 && x < nMapWidth && y >= 0 && y < nMapHeight && !v_tileMap.empty())
		//Check if the tile is a valid tile if it is set the tile
		v_tileMap[x][y].b_solid = solid;


	return;
}


//----------------------------------------------------------------------------


int Game_Map::GetTileIndex(int x, int y){
	/*
	 *
	 */




	if (x >= 0 && x < nMapWidth && y >= 0 && y < nMapHeight && !v_tileMap.empty())
		//Check if the tile is a valid tile if it is set the tile
		return v_tileMap[x][y].n_tileIndex;

	else return 0;
}


//----------------------------------------------------------------------------


void Game_Map::SetTileIndex(int x, int y, int index){
	/*
	 *
	 */




	if (x >= 0 && x < nMapWidth && y >= 0 && y < nMapHeight && !v_tileMap.empty())
		//Check if the tile is a valid tile if it is set the tile
		v_tileMap[x][y].n_tileIndex = index;
}


//----------------------------------------------------------------------------


void Game_Map::Draw(SDL_Renderer *renderer, SDL_Texture *tTileSheet,
		int nVisibleTilesX, int nVisibleTilesY, float fOffSetX,
		float fOffSetY, int scale){
	//

	//Loop through the map and draw only the visible tiles
	for(int y = 0; y < nVisibleTilesY; y++){
		for(int x = 0; x < nVisibleTilesX; x++){
			v_tileMap[x + (int)fOffSetX][y + (int)fOffSetY].draw(renderer,
					tTileSheet, nTileWidth, nTileHeight, scale,
					fOffSetX, fOffSetY);
		}
	}
	return;
}


//----------------------------------------------------------------------------


bool Game_Map::LoadMap(std::string FileName){
	/*
	 * *brief* This method load the map file given by the user and will return
	 * 		   true if successful, false otherwise
	 *
	 *
	 * 	param FileName is the directory to the tile map file
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
		map>>nMapWidth;
		map>>nMapHeight;

		//Read tile size
		map>>nTileWidth;
		map>>nTileHeight;

		if(map.fail()){
			//Check if there was a problem reading the map file
			std::cout<<"*Error* Unable to read map file: "
					<<FileName<<std::endl;
			bMapLoaded = false;
		}
		else{
			//Resize the tile map with the data provided in the map file
			v_tileMap.clear();
			v_tileMap.resize(nMapWidth,
					std::vector<Game_Tile>(nTileHeight,
							Game_Tile{false, 0, 0, 0}));
		}

		//Populate map with tiles
		for(int y = 0; y < nMapHeight && bMapLoaded; y++){
			for(int x = 0; x < nMapWidth && bMapLoaded; x++){
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
					v_tileMap[x][y].f_x = (float)(x * nTileWidth);
					v_tileMap[x][y].f_y = (float)(y * nTileHeight);
				}
			}
		}
	}

	return bMapLoaded;
}








//============================================================================
// Name       		: Game_Map.cpp
// Author     		: Thomas Hooks
// Version    		: 1
// Last Modified	: 11/2/2019
// Description		:
//============================================================================


#include "Game_Map.h"

#include <iostream>
#include <sstream>
#include <list>
#include <SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <ctime>
#include <math.h>
#include <vector>
#include <list>
#include <memory>
#include <string>
#include <fstream>

#include "Game.h"


//============================================================================
//                              Class Game_Map


Game_Map::Game_Map(std::string name) {
	//

	nMapWidth = 5; nMapHeight= 5;
	sMapName = name;
	nTileWidth = 32; nTileHeight = 32;

	return;
}


//============================================================================


Game_Map::~Game_Map() {

}


//============================================================================


bool Game_Map::IsTileSoilid(int x, int y){
	//

	if (x >= 0 && x < nMapWidth && y >= 0 && y < nMapHeight && !vTileMap.empty())
		return vTileMap[x][y].bSoilid;
	else return false;
}


//============================================================================


void Game_Map::SetTileSoilid(int x, int y, bool solid){
	/*
	 * *brief*			This method will set the give tile's solid state
	 *
	 *
	 * *param: x*		specifies the tile's X coordinate in the map
	 * *param: y*		specifies the tile's Y coordinate in the map
	 * *param: solid*	specifies if the tile is solid or not
	 * */


	if (x >= 0 && x < nMapWidth && y >= 0 && y < nMapHeight && !vTileMap.empty())
		//Check if the tile is a valid tile if it is set the tile
			vTileMap[x][y].bSoilid = solid;

	return;
}
//============================================================================


int Game_Map::GetTileIndex(int x, int y){
	//

	if (x >= 0 && x < nMapWidth && y >= 0 && y < nMapHeight && !vTileMap.empty())
		//Check if the tile is a valid tile if it is set the tile
		return vTileMap[x][y].nTileIndex;

	else return 0;
}


//============================================================================


void Game_Map::SetTileIndex(int x, int y, int index){
	//

	if (x >= 0 && x < nMapWidth && y >= 0 && y < nMapHeight && !vTileMap.empty())
		//Check if the tile is a valid tile if it is set the tile
		vTileMap[x][y].nTileIndex = index;
}


//============================================================================


void Game_Map::Draw(SDL_Renderer *renderer, SDL_Texture *tTileSheet,
		int nVisibleTilesX, int nVisibleTilesY, float fOffSetX,
		float fOffSetY, int scale){
	//

	//Loop through the map and draw only the visible tiles
	for(int y = 0; y < nVisibleTilesY; y++){
		for(int x = 0; x < nVisibleTilesX; x++){
			vTileMap[x + (int)fOffSetX][y + (int)fOffSetY].Draw(renderer,
					tTileSheet, nTileWidth, nTileHeight, scale,
					fOffSetX, fOffSetY);
		}
	}
	return;
}


//============================================================================


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
			vTileMap.clear();
			vTileMap.resize(nMapWidth,
					std::vector<class cTile>(nTileHeight,
							cTile{false, 0, 0, 0}));
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

					vTileMap[x][y].bSoilid = bTileSolid;
					vTileMap[x][y].nTileIndex = nTileIndex;
					vTileMap[x][y].fX = (float)(x * nTileWidth);
					vTileMap[x][y].fY = (float)(y * nTileHeight);
				}
			}
		}
	}

	return bMapLoaded;
}



//////////////////////////////////////////////////////////////////////////////
//============================================================================
//                              Class cTile



cTile::cTile(bool soilid, int index, float x, float y){
	//

	bSoilid = soilid;
	nTileIndex = index;
	fX = x; fY = y;

	return;
}


//============================================================================


cTile::~cTile(){
	//

	return;
}


//============================================================================


void cTile::Draw(SDL_Renderer *renderer, SDL_Texture *TileSheet,
		int width, int height, int scale, float fOffSetX, float fOffSetY){
	//

	//Set the draw color to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	//Select the right sprite from the sheet
	SDL_Rect TileScr = {nTileIndex * width/scale, 0,
			width/scale, height/scale};

	//Set the sprite size and location on map
	SDL_Rect TileRect = {(int)(fX - fOffSetX*width), (int)(fY - fOffSetY*height),
			width, height};//

	//Draw the tile to the screen
	SDL_RenderCopy(renderer, TileSheet, &TileScr, &TileRect);

	return;
}





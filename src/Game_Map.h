//============================================================================
// Name       		: Game_Map.h
// Author     		: Thomas Hooks
// Version    		: 1
// Last Modified	: 11/16/2019
// Description		:
//============================================================================




#ifndef GAME_MAP_H_
#define GAME_MAP_H_


#include <iostream>
#include <vector>
#include <string>

#include <SDL.h>

#include "Game_Tile.h"




class Game_Map {
public:
	Game_Map(std::string name); //class Game_State *State
	~Game_Map();

	bool IsTileSoilid(int x, int y);
	void SetTileSoilid(int x, int y, bool solid);

	int GetTileIndex(int x, int y);
	void SetTileIndex(int x, int y, int index);

	bool LoadMap(std::string FileName);
	void Draw(SDL_Renderer *renderer, SDL_Texture *tTileSheet,
			int nVisibleTilesX, int nVisibleTilesY,
			float fOffSetX, float fOffSetY, int scale);

	int nMapWidth, nMapHeight;		//Size of the map
	int nTileWidth, nTileHeight;		//Size of the tile in px
	std::string sMapName;		//Name of map

private:
	//2D vector that contains the tile map
	std::vector<std::vector<Game_Tile>> v_tileMap;
};


#endif /* GAME_MAP_H_ */








//============================================================================
// Name       		: Game_Map.h
// Author     		: Thomas Hooks
// Version    		: 1
// Last Modified	: 11/2/2019
// Description		:
//============================================================================




#ifndef GAME_MAP_H_
#define GAME_MAP_H_


#include <iostream>
#include <SDL.h>
#include <vector>
#include <string>




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
	std::vector<std::vector<class cTile>> vTileMap;
};

//============================================================================

class cTile{
public://Method
	cTile(bool soilid, int index, float x, float y);
	~cTile();
	void Draw(SDL_Renderer *renderer, SDL_Texture *TileSheet, int width, int height, int scale, float fOffSetX, float fOffSetY);

public://Data
	bool bSoilid;		//Is the tile passable
	int nTileIndex;		//Location of the tile's sprite in the sprite sheet
	float fX, fY;
};



#endif /* GAME_MAP_H_ */

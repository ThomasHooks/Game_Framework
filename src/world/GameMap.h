//============================================================================
// Name       		: GameMap.h
// Author     		: Thomas Hooks
// Last Modified	: 03/08/2020
//============================================================================




#ifndef GAMEMAP_H_
#define GAMEMAP_H_




#include <iostream>
#include <vector>
#include <string>

#include <SDL.h>

#include "Tile.h"




class GameMap {

public:
	GameMap(std::string name);

	~GameMap();


	bool is_tileSolid(int x, int y);
	void set_tileSolid(int x, int y, bool solid);

	int get_tileIndex(int x, int y);
	void set_tileIndex(int x, int y, int index);

	class Position getTilePosition(int x, int y);

	bool loadMap(std::string FileName);

	void draw(SDL_Renderer *renderer, SDL_Texture *tTileSheet,
			int nVisibleTilesX, int nVisibleTilesY,
			float fOffSetX, float fOffSetY, int scale);


	int get_mapWidth(void) const {return n_mapWidth;}

	void set_mapWidth(const int width) {n_mapWidth = width;}


	int get_mapHeight(void) const {return n_mapHeight;}

	void set_mapHeight(const int height) {n_mapHeight = height;}


	int get_tileWidth(void) const {return n_tileWidth;}

	void set_tileWidth(const int width) {n_tileWidth = width;}


	int get_tileHeight(void) const {return n_tileHeight;}

	void set_tileHeight(const int height) {n_tileHeight = height;}


	std::string get_mapName(void) const {return mapName;}

	void set_mapName(const std::string &name) {mapName = name;}


	//Size of the map
	int n_mapWidth, n_mapHeight;

	//Size of the tile in pixel
	int n_tileWidth, n_tileHeight;

	//Name of map
	std::string mapName;

private:

	//2D vector that contains the tile map
	std::vector<std::vector<Tile>> v_tileMap;
};


#endif /* GAMEMAP_H_ */








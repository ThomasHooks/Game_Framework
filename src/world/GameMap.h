//============================================================================
// Name       		: GameMap.h
// Author     		: Thomas Hooks
// Last Modified	: 03/08/2020
//============================================================================




#ifndef GAMEMAP_H_
#define GAMEMAP_H_




#include <vector>
#include <string>

#include <SDL.h>

#include "Tile.h"
#include "../utilities/Dimension.h"




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

	int get_mapWidth(void) const {return mapWidth;}
	void set_mapWidth(const int width) {mapWidth = width;}

	int get_mapHeight(void) const {return mapHeight;}
	void set_mapHeight(const int height) {mapHeight = height;}
	const Dimension& getSize() const;

	int get_tileWidth(void) const {return tileWidth;}
	void set_tileWidth(const int width) {tileWidth = width;}
	const Dimension& getTileSize() const;

	int get_tileHeight(void) const {return tileHeight;}
	void set_tileHeight(const int height) {tileHeight = height;}

	std::string get_mapName(void) const {return mapName;}
	void set_mapName(const std::string &name) {mapName = name;}

	int mapWidth, mapHeight;
	int tileWidth, tileHeight;

private:

	Dimension mapSize;
	Dimension tileSize;

	std::string mapName;

	std::vector<std::vector<Tile>> tileMap;
};


#endif /* GAMEMAP_H_ */








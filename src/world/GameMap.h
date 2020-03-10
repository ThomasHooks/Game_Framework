//============================================================================
// Name       		: GameMap.h
// Author     		: Thomas Hooks
// Last Modified	: 03/09/2020
//============================================================================




#ifndef GAMEMAP_H_
#define GAMEMAP_H_




#include <vector>
#include <string>

#include "Tile.h"
#include "../utilities/Dimension.h"




class GameMap {

public:

	GameMap(std::string name);

	~GameMap();

	bool isTileSolid(int x, int y);
	void setTileSolid(int x, int y, bool solid);

	int getTileSprite(int x, int y);
	void setTileSprite(int x, int y, int index);

	class Position getTilePosition(int x, int y);

	int getWidth() const;
	int getHeight() const;
	const Dimension& getSize() const;

	int getTileWidth() const;
	int getTileHeight() const;
	const Dimension& getTileSize() const;

	const std::string& getTag() const;

	bool loadMap(std::string FileName);

	int mapWidth, mapHeight;
	int tileWidth, tileHeight;

protected:

	void setWidth(const int width);
	void setHeight(const int height);
	void setSize(const Dimension &sizeIn);

private:

	Dimension mapSize;
	Dimension tileSize;

	std::string mapTag;

	std::vector<std::vector<Tile>> tileMap;
};


#endif /* GAMEMAP_H_ */








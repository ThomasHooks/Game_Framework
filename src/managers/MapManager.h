//============================================================================
// Name       		: MapManager.h
// Author     		: Thomas Hooks
// Last Modified	: 03/08/2020
//============================================================================




#ifndef SRC_MAPMANAGER_H_
#define SRC_MAPMANAGER_H_




#include <vector>
#include <memory>
#include <string>

#include "../world/GameMap.h"




class MapManager {

public:

	MapManager();

	MapManager(class GameLogger *log_ptr);

	~MapManager();

	MapManager(const MapManager &other) = delete;

	MapManager(MapManager &&other) = delete;


	void init(class GameLogger *log_ptr);

	void push_map(std::string tileSheetKey, std::string mapFilePath);

	void pop_map(void);

	void draw(const class Position &cameraPos,
			const struct Dimension &visibleTiles,
			class RendererManager &renderer);

	int get_tileSolid(int tile_x, int tile_y) const
		{return mapStack.back()->is_tileSolid(tile_x, tile_y);}

	void set_tileSolid(int tile_x, int tile_y, bool solid)
		{mapStack.back()->set_tileSolid(tile_x, tile_y, solid);}


	//This method will be changed
	//Eventually it return a Position2D strut of which sprite the tile is
	int get_tileIndex(int tile_x, int tile_y) const
		{return mapStack.back()->get_tileIndex(tile_x, tile_y);}


	//These method will be changed to return a Dimension2D strut
	int get_width(void) const {return mapStack.back()->get_mapWidth();}

	int get_height(void) const {return mapStack.back()->get_mapHeight();}


	int get_tileWidth(void) const {return mapStack.back()->get_tileWidth();}

	int get_tileHeight(void) const {return mapStack.back()->get_tileHeight();}


	std::string get_Name(void) const
		{return mapStack[mapStack.size()]->get_mapName();}


	int get_scale(void) const {return scale;}

	void set_scale(int scale);


private:

	bool hasBeenInit;

	//Number of tiles that are visible on screen
	int visibleTilesX, visibleTilesY;

	//The amount the tiles are scaled up by
	int scale;

	class GameLogger *logger;

	std::vector<std::unique_ptr<GameMap>> mapStack;
};




#endif /* SRC_MAPMANAGER_H_ */








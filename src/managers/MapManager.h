//============================================================================
// Name       		: MapManager.h
// Author     		: Thomas Hooks
// Last Modified	: 12/19/2019
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

	MapManager(class GameLogger *log_ptr, class AssetManager *assets_ptr);

	~MapManager();

	MapManager(const MapManager &other) = delete;

	MapManager(MapManager &&other) = delete;


	void init(class GameLogger *log_ptr, class AssetManager *assets_ptr);

	void push_map(std::string tileSheetKey, std::string mapFilePath);

	void pop_map(void);

	void draw(float offsetHor,
			  float offsetVer,
			  int visibleTilesHor,
			  int visibleTilesVer,
			  struct SDL_Renderer *renderer_ptr);


	//Getters and Setters
	int get_tileSolid(int tile_x, int tile_y) const
		{return v_stack.back()->is_tileSolid(tile_x, tile_y);}

	void set_tileSolid(int tile_x, int tile_y, bool solid)
		{v_stack.back()->set_tileSolid(tile_x, tile_y, solid);}


	//This method will be changed
	//Eventually it return a Position2D strut of which sprite the tile is
	int get_tileIndex(int tile_x, int tile_y) const
		{return v_stack.back()->get_tileIndex(tile_x, tile_y);}


	//These method will be changed to return a Dimension2D strut
	int get_width(void) const {return v_stack.back()->get_mapWidth();}

	int get_height(void) const {return v_stack.back()->get_mapHeight();}


	int get_tileWidth(void) const {return v_stack.back()->get_tileWidth();}

	int get_tileHeight(void) const {return v_stack.back()->get_tileHeight();}


	std::string get_Name(void) const
		{return v_stack[v_stack.size()]->get_mapName();}


	int get_scale(void) const {return n_scale;}

	void set_scale(int scale);


private:

	bool b_hasBeenInit;

	//Number of tiles that are visible on screen
	int n_visible_tiles_x, n_visible_tiles_y;

	//The amount the tiles are scaled up by
	int n_scale;

	class GameLogger *log;

	class AssetManager *assets;

	std::vector<std::unique_ptr<GameMap>> v_stack;
};




#endif /* SRC_MAPMANAGER_H_ */








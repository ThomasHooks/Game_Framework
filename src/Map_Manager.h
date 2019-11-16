//============================================================================
// Name       		: Map_Manager.h
// Author     		: Thomas Hooks
// Version    		: 1
// Last Modified	: 11/16/2019
// Description		:
//============================================================================




#ifndef SRC_MAP_MANAGER_H_
#define SRC_MAP_MANAGER_H_




#include <vector>
#include <memory>
#include <string>
#include "Game_Map.h"




class Map_Manager {

public:

	Map_Manager(class Game *game_ptr);

	virtual ~Map_Manager();

	Map_Manager(const Map_Manager &other) = delete;

	Map_Manager(Map_Manager &&other) = delete;


	void init(class Game_Logger *log_ptr, class Asset_Manager *assets_ptr);

	void push_map(std::string tileSheetKey, std::string mapFilePath);

	void pop_map(void);

	void draw(int windowWidth, int windowHeight, float camera_x, float camera_y, struct SDL_Renderer *renderer_ptr);


	//Getters and Setters
	int get_tileSolid(int tile_x, int tile_y) const
		{return v_stack.back()->IsTileSoilid(tile_x, tile_y);}

	void set_tileSolid(int tile_x, int tile_y, bool solid)
		{v_stack.back()->SetTileSoilid(tile_x, tile_y, solid);}


	//This method will be changed
	//Eventually it return a 2D position strut of which sprite the tile is
	int get_tileIndex(int tile_x, int tile_y) const
		{return v_stack.back()->GetTileIndex(tile_x, tile_y);}


	int get_width(void) const {return v_stack.back()->nMapWidth;}

	int get_height(void) const {return v_stack.back()->nMapHeight;}


	int get_tileWidth(void) const {return v_stack.back()->nTileWidth;}

	int get_tileHeight(void) const {return v_stack.back()->nTileHeight;}


	std::string get_Name(void) const
		{return v_stack[v_stack.size()]->sMapName;}


	int get_scale(void) const {return n_scale;}

	void set_scale(int scale) {n_scale = scale;}


private:

	bool b_hasBeenInit;

	//Number of tiles that are visible on screen
	int n_visible_tiles_x, n_visible_tiles_y;

	//The amount the tiles are scaled up by
	int n_scale;

	Game *game;

	Game_Logger *log;

	class Asset_Manager *assets;

	std::vector<std::unique_ptr<Game_Map>> v_stack;
};




#endif /* SRC_MAP_MANAGER_H_ */








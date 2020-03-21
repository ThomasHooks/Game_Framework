//============================================================================
// Name       		: TileMap.h
// Author     		: Thomas Hooks
// Last Modified	: 03/21/2020
//============================================================================




#ifndef TILEMAP_H_
#define TILEMAP_H_


#include <string>
#include <map>
#include <memory>

#include "ITile.h"


class TileMap {

public:

	TileMap(class GameLogger *loggerIn,
			const std::string &tagIn,
			const std::string &filePath);



	~TileMap();



	TileMap(const TileMap &other) = delete;



	/*
	 * @return	Size of the world
	 *
	 * Gets the TileMaps size in tile-space
	 */
	const Dimension& size() const;



	/*
	 * @return	Width of the TileMap
	 *
	 * Gets the TileMaps width in tile-space
	 */
	int width() const;



	/*
	 * @return	Height of the TileMap
	 *
	 * Gets the TileMaps height in tile-space
	 */
	int height() const;



	/*
	 * @return	Size of the world
	 *
	 * Gets the TileMaps size in tile-space
	 */
	const Dimension& tileSize() const;



	//Gets the TileMaps tile width
	int tileWidth() const;



	//Gets the TileMaps tile height
	int tileHeight() const;



	//Gets the TileMap's tag
	const std::string& getTag() const;



	/*
	 * @nullable
	 *
	 * @param	posIn The coordinates of the Tile
	 *
	 * @return	The Tile at that location or null if the Tile does not exist
	 */
	ITile* getTile(const Position& posIn);



	/*
	 * @nullable
	 *
	 * @param	x, y The tile-space coordinates of the Tile
	 *
	 * @return	The Tile at that location or null if the Tile does not exist
	 */
	ITile* getTile(int x, int y);



	/*
	 * @nullable
	 *
	 * @param	x, y The coordinates of the Tile
	 *
	 * @return	The Tile at that location or null if the Tile does not exist
	 */
	ITile* getTile(double x, double y);



protected:

	/*
	 * @param	filePath Path to the tile map file
	 *
	 * Creates a tile map using the given filePath
	 */
	void buildTileMap(const std::string &filePath);



private:

	class GameLogger *logger;

	std::string tag;

	Dimension sizeMap;

	Dimension sizeTile;

	std::map<std::pair<int, int>, ITile> tileMap;
};


#endif /* TILEMAP_H_ */




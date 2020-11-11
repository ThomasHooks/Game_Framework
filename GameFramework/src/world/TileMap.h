#ifndef TILEMAP_H_
#define TILEMAP_H_




#include <string>
#include <map>
#include <memory>

#include "ITile.h"
#include "utilities/Loggers.hpp"




class TileMap 
{
public:

	TileMap(const std::string &tagIn, const std::string &filePath);



	~TileMap();



	TileMap(const TileMap &other) = delete;



	/// <returns></returns>
	/// /// <summary>
	/// Gets this TileMaps size in tile-space
	/// </summary>
	/// <returns></returns>
	const Pos2N& size() const;



	/// <summary>
	 /// Gets this TileMaps width in tile-space
	 /// </summary>
	 /// <returns></returns>
	int width() const;



	/// <summary>
	/// Gets this TileMaps height in tile-space
	/// </summary>
	/// <returns></returns>
	int height() const;



	/// <summary>
	 /// Gets this TileMaps Tile size
	 /// </summary>
	 /// <returns></returns>
	const Pos2N& tileSize() const;



	/// <summary>
	/// Gets this TileMaps tile width
	/// </summary>
	/// <returns></returns>
	int tileWidth() const;



	/// <summary>
	/// Gets this TileMaps tile height
	/// </summary>
	/// <returns></returns>
	int tileHeight() const;



	/// <summary>
	/// Gets this TileMap's ID tag
	/// </summary>
	/// <returns></returns>
	const std::string& getTag() const;



	/// <summary>
	 /// <para>nullable</para>
	 /// Gets the Tile at the specified location or null if that Tile does not exist
	 /// </summary>
	 /// <param name="posIn">Specifies the coordinates to be offset by one tile</param>
	 /// <returns></returns>
	ITile* getTile(const TilePos& posIn);



	/// <summary>
	/// <para>nullable</para>
	/// Gets the Tile at the specified location or null if that Tile does not exist
	/// </summary>
	/// <param name="x">Specifies the X coordinate</param>
	/// <param name="y">Specifies the Y coordinate</param>
	/// <returns></returns>
	ITile* getTile(int x, int y);



	/// <summary>
	/// <para>nullable</para>
	/// Gets the Tile at the specified location or null if that Tile does not exist
	/// </summary>
	/// <param name="x">Specifies the X coordinate</param>
	/// <param name="y">Specifies the Y coordinate</param>
	/// <returns></returns>
	ITile* getTile(double x, double y);



	/// <summary>
	/// <para>nullable</para>
	/// Gets the Tile that is offset from the specified location or null if that Tile does not exist
	/// </summary>
	/// <param name="posIn">Specifies the coordinates to be offset by one tile</param>
	/// <param name="direction">Specifies the offset direction</param>
	/// <returns></returns>
	ITile* getOffsetTile(const TilePos& posIn, EnumSide direction);



protected:

	/// <summary>
	/// Creates a tile map using the given filePath
	/// </summary>
	/// <param name="filePath">Path to the tile map file</param>
	void buildTileMap(const std::string &filePath);



private:

	std::string m_tag;

	Pos2N m_sizeMap;

	Pos2N m_sizeTile;

	std::map<std::pair<int, int>, ITile> m_tileMap;

	std::shared_ptr<spdlog::logger> m_logger;
};


#endif




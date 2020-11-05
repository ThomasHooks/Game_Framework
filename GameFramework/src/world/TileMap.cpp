#include <iostream>
#include <sstream>
#include <fstream>

#include "world/TileMap.h"




TileMap::TileMap(const std::string &tagIn, const std::string &filePath)
	: m_tag(tagIn), m_sizeMap(), m_sizeTile() 
{
	m_logger = Loggers::getLog();
	this->buildTileMap(filePath);
}



TileMap::~TileMap() 
{
	m_logger->info("World '{0}' has been removed", m_tag);
}



/*
 * @return	Size of the world
 *
 * Gets the TileMaps size in tile-space
 */
const Dimension& TileMap::size() const 
{
	return m_sizeMap;
}



/*
 * @return	Width of the TileMap
 *
 * Gets the TileMaps width in tile-space
 */
int TileMap::width() const 
{
	return m_sizeMap.width;
}



/*
 * @return	Height of the TileMap
 *
 * Gets the TileMaps height in tile-space
 */
int TileMap::height() const 
{
	return m_sizeMap.height;
}



//Gets the TileMaps tile size
const Dimension& TileMap::tileSize() const 
{
	return m_sizeTile;
}



//Gets the TileMaps tile width
int TileMap::tileWidth() const 
{
	return m_sizeTile.width;
}



//Gets the TileMaps tile height
int TileMap::tileHeight() const 
{
	return m_sizeTile.height;
}



//Gets the TileMap's tag
const std::string& TileMap::getTag() const 
{
	return m_tag;
}



/*
 * @nullable
 *
 * @param	posIn The coordinates of the Tile
 *
 * @return	The Tile at that location or null if the Tile does not exist
 */
ITile* TileMap::getTile(const Position& posIn) 
{
	return this->getTile(posIn.xPos(), posIn.yPos());
}



/*
 * @nullable
 *
 * @param	x, y The tile-space coordinates of the Tile
 *
 * @return	The Tile at that location or null if the Tile does not exist
 */
ITile* TileMap::getTile(int x, int y) 
{
	if (x < 0 || x > this->width() || y < 0 || y > this->height()) 
		return nullptr;
	auto itr = m_tileMap.find({x, y});
	return itr == m_tileMap.end() ? nullptr : &itr->second;
}



/*
 * @nullable
 *
 * @param	x, y The coordinates of the Tile
 *
 * @return	The Tile at that location or null if the Tile does not exist
 */
ITile* TileMap::getTile(double x, double y) 
{
	return this->getTile(static_cast<int>(x/this->tileWidth() + 0.5), static_cast<int>(y/this->tileHeight() + 0.5));
}



/*
 * @nullable
 *
 * @param	posIn The coordinates to be offset by one tile
 *
 * @param	direction The offset direction
 *
 * @return	The Tile offset from that location or null if the Tile does not exist
 */
ITile* TileMap::getOffsetTile(const Position& posIn, EnumSide direction)
{
	switch (direction)
	{
	case EnumSide::UP:
		return this->getTile(posIn.xPos(), posIn.yPos() - this->tileHeight());

	case EnumSide::RIGHT:
		return this->getTile(posIn.xPos() + this->tileWidth(), posIn.yPos());

	case EnumSide::DOWN:
		return this->getTile(posIn.xPos(), posIn.yPos() + this->tileHeight());

	case EnumSide::LEFT:
		return this->getTile(posIn.xPos() - this->tileWidth(), posIn.yPos());

	default:
		return nullptr;
	}
}



/*
 * @param	filePath Path to the tile map file
 *
 * Creates a tile map using the given filePath
 */
void TileMap::buildTileMap(const std::string &filePath)
{
	m_logger->info("Building World '{0}' at ''", m_tag, filePath);

	std::ifstream mapFile(filePath);
	if (!mapFile.is_open())
	{
		m_logger->error("Unable to load/find map '{0}' at '{1}'", m_tag, filePath);
		return;
	}

	//Read the map size from the file
	int mapWidth = 0;
	mapFile>>mapWidth;
	m_sizeMap.width = mapWidth;
	int mapHeight = 0;
	mapFile>>mapHeight;
	m_sizeMap.height = mapHeight;
	if (mapFile.fail()) 
		m_logger->error("Unable to read map '{0}' at '{1}' in element 'MAPSIZE'", m_tag, filePath);

	//Read the tile size from the file
	int tileWidth = 0;
	mapFile>>tileWidth;
	m_sizeTile.width = tileWidth;
	int tileHeight = 0;
	mapFile>>tileHeight;
	m_sizeTile.height = tileHeight;
	if (mapFile.fail()) 
		m_logger->error("Unable to read map '{0}' at '{1}' in element 'TILESIZE'", m_tag, filePath);

	//Read the tile and add it to the tile map
	for (int y = 0; y < m_sizeMap.height; y++) 
	{
		for (int x = 0; x < m_sizeMap.width; x++) 
		{
			bool opaque = true;
			bool solid = false;
			EnumSide pass = EnumSide::NONE;
			Dimension sprite(0, 0);

			int index = 0;
			mapFile>>index;
			sprite.width = index;
			if (mapFile.fail()) 
			{
				m_logger->error("Unable to read map '{0}' at '{1}' in element 'TILESPRITE'", m_tag, filePath);
				return;
			}

			if (sprite.width > 1) 
				solid = true;
			m_tileMap.insert({
				{ x, y }, 
				ITile(x * static_cast<double>(m_sizeTile.width), y * static_cast<double>(m_sizeTile.height), m_sizeTile.width, m_sizeTile.height, sprite, pass, opaque, solid)
			});
		}
	}
	m_logger->info("World '{0}' has been built", m_tag);
}








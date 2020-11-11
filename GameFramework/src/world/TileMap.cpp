#include <iostream>
#include <sstream>
#include <fstream>

#include "world/TileMap.h"
#include "utilities/math/Pos2.hpp"
#include "utilities/physics/TilePos.h"




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



const Pos2N& TileMap::size() const 
{
	return m_sizeMap;
}



int TileMap::width() const 
{
	return m_sizeMap.w;
}



int TileMap::height() const 
{
	return m_sizeMap.h;
}



const Pos2N& TileMap::tileSize() const 
{
	return m_sizeTile;
}



int TileMap::tileWidth() const 
{
	return m_sizeTile.w;
}



int TileMap::tileHeight() const 
{
	return m_sizeTile.h;
}



const std::string& TileMap::getTag() const 
{
	return m_tag;
}



ITile* TileMap::getTile(const TilePos& posIn)
{
	return this->getTile(posIn.x(), posIn.y());
}



ITile* TileMap::getTile(int x, int y) 
{
	if (x < 0 || x > this->width() || y < 0 || y > this->height()) 
		return nullptr;
	auto itr = m_tileMap.find({x, y});
	return itr == m_tileMap.end() ? nullptr : &itr->second;
}



ITile* TileMap::getTile(double x, double y) 
{
	return this->getTile(static_cast<int>(x/this->tileWidth() + 0.5), static_cast<int>(y/this->tileHeight() + 0.5));
}



ITile* TileMap::getOffsetTile(const TilePos& posIn, EnumSide direction)
{
	switch (direction)
	{
	case EnumSide::UP:
		return this->getTile(posIn.x(), posIn.y() - this->tileHeight());

	case EnumSide::RIGHT:
		return this->getTile(posIn.x() + this->tileWidth(), posIn.y());

	case EnumSide::DOWN:
		return this->getTile(posIn.x(), posIn.y() + this->tileHeight());

	case EnumSide::LEFT:
		return this->getTile(posIn.x() - this->tileWidth(), posIn.y());

	default:
		return nullptr;
	}
}



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
	m_sizeMap.w = mapWidth;
	int mapHeight = 0;
	mapFile>>mapHeight;
	m_sizeMap.h = mapHeight;
	if (mapFile.fail()) 
		m_logger->error("Unable to read map '{0}' at '{1}' in element 'MAPSIZE'", m_tag, filePath);

	//Read the tile size from the file
	int tileWidth = 0;
	mapFile>>tileWidth;
	m_sizeTile.w = tileWidth;
	int tileHeight = 0;
	mapFile>>tileHeight;
	m_sizeTile.h = tileHeight;
	if (mapFile.fail()) 
		m_logger->error("Unable to read map '{0}' at '{1}' in element 'TILESIZE'", m_tag, filePath);

	//Read the tile and add it to the tile map
	for (int y = 0; y < m_sizeMap.h; y++) 
	{
		for (int x = 0; x < m_sizeMap.w; x++) 
		{
			bool opaque = true;
			bool solid = false;
			EnumSide pass = EnumSide::NONE;
			Pos2N sprite(0, 0);

			int index = 0;
			mapFile>>index;
			sprite.w = index;
			if (mapFile.fail()) 
			{
				m_logger->error("Unable to read map '{0}' at '{1}' in element 'TILESPRITE'", m_tag, filePath);
				return;
			}

			if (sprite.w > 1) 
				solid = true;
			m_tileMap.insert({
				{ x, y }, 
				ITile(x * static_cast<double>(m_sizeTile.w), y * static_cast<double>(m_sizeTile.h), m_sizeTile.w, m_sizeTile.h, sprite, pass, opaque, solid)
			});
		}
	}
	m_logger->info("World '{0}' has been built", m_tag);
}








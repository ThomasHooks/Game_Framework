#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "renderer/Renderer.h"
#include "utilities/physics/TilePos.h"
#include "world/WorldStack.h"
#include "world/TileMap.h"




WorldStack::WorldStack()
{
	m_logger = Loggers::getLog();
	m_logger->info("Map Manager has been initialized");
}



void WorldStack::pushMap(std::string tileSheetTag, std::string mapFilePath)
{
	m_worldStack.emplace_back(std::unique_ptr<TileMap>(new TileMap(tileSheetTag, mapFilePath)));
}



void WorldStack::popMap()
{
	if (m_worldStack.empty())
		m_logger->warn("Tried to free map, but map stack is empty!");
	else
		m_worldStack.pop_back();
}



void WorldStack::draw(const TilePos& cameraPos, const Pos2N& windowSize, Renderer& renderer)
{
	TileMap* world = this->getWorld();
	if (world == nullptr) 
	{
		m_logger->critical("Null Pointer exception: Tried to render World, but world stack is empty!");
		return;
	}

	//Calculate the top-left visible tile
	Pos2N tileSize(world->tileWidth(), world->tileHeight());
	Pos2N numberOfVisibleTiles(windowSize.w/tileSize.w + 1, windowSize.h/tileSize.h);
	double offsetX = cameraPos.x()/tileSize.w;
	double offsetY = cameraPos.y()/tileSize.h;
	
	//Keep the camera inside the World boundaries
	if (offsetX < 0) 
		offsetX = 0;

	if (offsetY < 0) 
		offsetY = 0;

	if (offsetX > static_cast<double>(world->width()) - static_cast<double>(numberOfVisibleTiles.w))
		offsetX = static_cast<double>(world->width()) - static_cast<double>(numberOfVisibleTiles.w);

	if (offsetY > static_cast<double>(world->height()) - static_cast<double>(numberOfVisibleTiles.h))
		offsetY = static_cast<double>(world->height()) - static_cast<double>(numberOfVisibleTiles.h);

	Pos2D tileOffset(offsetX, offsetY);
	//Over rendering is done to prevent artifacts along the edge of the screen
	for (int y = -1; y < numberOfVisibleTiles.h; y++) 
	{
		for (int x = -1; x < numberOfVisibleTiles.w; x++) 
		{
			int xCord = x + static_cast<int>(tileOffset.x + 0.5);
			int yCord = y + static_cast<int>(tileOffset.y + 0.5);
			/*
			 * This is to prevent the map from being indexed out of
			 * also doing this can cause some tiles to be rendered more than once
			 */
			if (xCord < 0) 
				xCord = 0;
			else if (xCord > world->width()) 
				xCord = world->width();

			if (yCord < 0) 
				yCord = 0;
			else if (yCord > world->height()) 
				yCord = world->height();

			ITile *tile = world->getTile(xCord, yCord);

			if (tile == nullptr) 
				m_logger->warn("Null Pointer exception: Tried to get tile in WorldStack::draw, but tile does not exist");
			else
				renderer.drawSprite(world->getTag(), tile->getPos(), cameraPos, tile->getSprite(), false);
		}
	}
}



class TileMap* WorldStack::getWorld()
{
	return m_worldStack.empty() ? nullptr : m_worldStack.back().get();
}








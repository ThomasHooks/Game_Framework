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

	void pushMap(std::string tileSheetTag, std::string mapFilePath);
	void popMap();

	void draw(const class Position &cameraPos,
			const struct Dimension &visibleTiles,
			class RendererManager &renderer);

	int getTileSolid(int x, int y) const;
	void setTileSolid(int x, int y, bool solid);


	//Eventually it return a Dimension of which sprite the tile is
	int getTileSprite(int x, int y) const;

	int getWidth() const;
	int getHeight() const;
	const Dimension& getSize() const;

	int getTileWidth() const;
	int getTileHeight() const;
	const Dimension& getTileSize() const;

	std::string getTag() const;

private:

	bool hasBeenInit;

	class GameLogger *logger;

	std::vector<std::unique_ptr<GameMap>> mapStack;
};




#endif /* SRC_MAPMANAGER_H_ */








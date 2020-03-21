//============================================================================
// Name       		: MapManager.h
// Author     		: Thomas Hooks
// Last Modified	: 03/21/2020
//============================================================================




#ifndef SRC_MAPMANAGER_H_
#define SRC_MAPMANAGER_H_




#include <vector>
#include <memory>
#include <string>




class MapManager {

public:

	MapManager(class GameLogger *log_ptr);



	~MapManager();



	MapManager(const MapManager &other) = delete;



	MapManager(MapManager &&other) = delete;



	/*
	 * @param	tileSheetTag The map's/sprite sheet's tag
	 *
	 * @param	mapFilePath The location of the map's sprite sheet
	 *
	 * Adds a new map to the back of the stack
	 */
	void pushMap(std::string tileSheetTag, std::string mapFilePath);



	//Removes the back map from the stack
	void popMap();



	/*
	 * @param	cameraPos The position of the camera
	 *
	 * @param	windowSize Size of the window
	 *
	 * @param	renderer Reference to the Renderer Manager
	 *
	 * Draws the active map to the screen
	 */
	void draw(const class Position &cameraPos,
			const struct Dimension &visibleTiles,
			class RendererManager &renderer);



	/*
	 * @return	The current world or null if there are no maps
	 *
	 * Gets the current world
	 */
	class TileMap* getWorld();



private:

	class GameLogger *logger;

	std::vector<std::unique_ptr<class TileMap>> worldStack;
};




#endif /* SRC_MAPMANAGER_H_ */








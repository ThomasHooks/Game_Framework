#ifndef SRC_WORLDSTACK_H_
#define SRC_WORLDSTACK_H_




#include <vector>
#include <memory>
#include <string>

#include <utilities/Loggers.hpp>




class WorldStack 
{
public:

	WorldStack();



	~WorldStack();



	WorldStack(const WorldStack &other) = delete;



	WorldStack(WorldStack &&other) = delete;



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
			class Renderer &renderer);



	/*
	 * @return	The current world or null if there are no maps
	 *
	 * Gets the current world
	 */
	class TileMap* getWorld();



private:

	std::vector<std::unique_ptr<class TileMap>> m_worldStack;

	std::shared_ptr<spdlog::logger> m_logger;
};


#endif /* SRC_WORLDSTACK_H_ */




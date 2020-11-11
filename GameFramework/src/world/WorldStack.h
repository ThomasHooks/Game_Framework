#ifndef SRC_WORLDSTACK_H_
#define SRC_WORLDSTACK_H_




#include <vector>
#include <memory>
#include <string>

#include <utilities/Loggers.hpp>
#include "utilities/math/Pos2.hpp"




class WorldStack 
{
public:

	WorldStack();



	WorldStack(const WorldStack &other) = delete;



	WorldStack(WorldStack &&other) = delete;



	/// <summary>
	/// Adds a new map to the back of the stack
	/// </summary>
	/// <param name="tileSheetTag">The map's/sprite sheet's tag</param>
	/// <param name="mapFilePath">The location of the map's sprite sheet</param>
	void pushMap(std::string tileSheetTag, std::string mapFilePath);



	/// <summary>
	/// Removes the back map from the stack
	/// </summary>
	void popMap();



	/// <summary>
	/// Draws the active map to the screen
	/// </summary>
	/// <param name="cameraPos">The position of the camera</param>
	/// <param name="visibleTiles">Size of the window</param>
	/// <param name="renderer">Reference to the Renderer</param>
	void draw(const class TilePos& cameraPos, const Pos2N& windowSize, class Renderer& renderer);



	/// <summary>
	/// <para>nullable</para>
	/// Gets the current world
	/// </summary>
	class TileMap* getWorld();



private:

	std::vector<std::unique_ptr<class TileMap>> m_worldStack;

	std::shared_ptr<spdlog::logger> m_logger;
};


#endif




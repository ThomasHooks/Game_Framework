#ifndef GAME_HPP_
#define GAME_HPP_


#include <string>
#include <memory>
#include <vector>

#include <spdlog/spdlog.h>

#include "utilities/math/Pos2.hpp"
#include "layers/LayerStack.hpp"
#include "utilities/Timer.h"




struct GameBuilder
{
	GameBuilder();



	/// <summary>
	/// Initializes the game window
	/// </summary>
	/// <param name="titleIn">Specifies the name of the game window</param>
	/// <param name="widthIn">Specifies the game windows width</param>
	/// <param name="heightIn">Specifies the game windows height</param>
	/// <param name="flagsIn">
	/// Specifies the SDL window flags, when set to a value of '0' no flags are set
	/// <para>See "https://wiki.libsdl.org/SDL_WindowFlags" for a full list of SDL window flags</para>
	/// </param>
	/// <returns>A referance to this GameBuilder</returns>
	GameBuilder& setWindow(const std::string& titleIn, int widthIn, int heightIn, unsigned int flagsIn = 0);



	/// <summary>
	/// Initializes the logger
	/// </summary>
	/// <param name="fileLocationIn">Specifies the logger's log file location</param>
	/// <param name="levelIn">Specifies the logger's logging level</param>
	/// <returns>A referance to this GameBuilder</returns>
	GameBuilder& setLogger(const std::string& fileLocationIn, spdlog::level::level_enum levelIn);



	/// <summary>
	/// Sets the number of game ticks per second
	/// </summary>
	/// <param name="ticksIn">Specifies the game tick rate in ticks per second</param>
	/// <returns>A referance to this GameBuilder</returns>
	GameBuilder& setTickRate(unsigned int ticksIn);



	/// <summary>
	/// Determines the name of the game window
	/// </summary>
	std::string windowTitle;



	/// <summary>
	/// Determines the starting size of the game window
	/// </summary>
	Pos2N windowSize;



	/// <summary>
	/// Specifies the SDL window flags, when set to a value of '0' no flags are set
	/// <para>See "https://wiki.libsdl.org/SDL_WindowFlags" for a full list of SDL window flags</para>
	/// </summary>
	unsigned int windowFlags;



	/// <summary>
	/// Specifies the logger's log file location
	/// </summary>
	std::string logFileLocation;



	/// <summary>
	/// Specifies the logger's logging level
	/// </summary>
	spdlog::level::level_enum logLevel;



	/// <summary>
	/// Determines the number of game ticks per second
	/// <para>By default it is 20 ticks per second</para>
	/// </summary>
	unsigned int tickRate;
};



class Game 
{
public:

	Game(const GameBuilder& builderIn);



	~Game();



	/// <summary>
	/// Adds a new Game Layer to this Game
	/// </summary>
	/// <typeparam name="LayerType">Specifies the Game Layer</typeparam>
	/// <typeparam name="...Args"></typeparam>
	/// <param name="...args">Specifies constructor arguments</param>
	template<class LayerType, typename... Args>
	void addLayer(Args&&... args) { m_layerStack.push<LayerType>(*this, std::forward<Args>(args)...); }


	
	/// <summary>
	/// Starts the game loop which will continue running until Game::markOver is called
	/// </summary>
	void run();



	/// <summary>
	/// Checks if the game has endded
	/// </summary>
	/// <returns>True if the game has endded</returns>
	bool isDone() const;



	/// <summary>
	/// Marks the game to be stopped
	/// </summary>
	void markOver();



	/// <summary>
	/// Checks if the specified key has been pressed on the keyboard
	/// </summary>
	/// <param name="scancode">Specifies which key</param>
	/// <returns></returns>
	static bool isKeyPressed(int scancode);



	/// <summary>
	/// Gets this game's renderer
	/// </summary>
	class Renderer& renderer();



	/// <summary>
	/// Gets this game's audio manager
	/// </summary>
	class AudioMixer& audioMixer();



	/// <summary>
	/// Gets this game's world manager
	/// </summary>
	class WorldStack& worldStack();



	/// <summary>
	/// Gets this game's entity manager
	/// </summary>
	class EntityManager& entities();



	/// <summary>
	/// <para>nullable</para>
	/// Gets this game's Window
	/// </summary>
	const class SDLWindowWrapper* getWindow() const;



	/// <summary> 
	/// <para>nullable</para>
	/// Gets this game's Camera
	/// </summary>
	class GameCamera* getCamera();



private:

	/// <summary>
	/// Initializes this games window
	/// </summary>
	/// <param name="title">Specifies title of the window</param>
	/// <param name="Window_Height">Specifies the height of the window measured in pixels</param>
	/// <param name="Window_Width">Specifies the width of the window measured in pixels</param>
	/// <param name="flags">
	/// <para>Specifies SDL window flags</para>
	/// <para>See "https://wiki.libsdl.org/SDL_WindowFlags" for a full list of all SDL window flags</para>
	/// </param>
	void initWindow(const std::string& title, int Window_Height, int Window_Width, uint32_t flags);



	void updateSDL();



	std::shared_ptr<spdlog::logger> m_logger;

	LayerStack m_layerStack;

	std::unique_ptr<class Renderer> m_renderer;

	std::unique_ptr<class AudioMixer> m_audioManager;

	std::unique_ptr<class WorldStack> m_worlds;

	std::unique_ptr<class EntityManager> m_entityManager;

	std::unique_ptr<class SDLWindowWrapper> m_windowWrap;

	std::unique_ptr<class GameCamera> m_cameraWrap;

	Timer m_timer;

	bool m_gameOver;

	unsigned int m_tickRate;

	int m_onWindowEvent = 0;
};


#endif




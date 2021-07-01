#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_


#include <string>
#include <memory>
#include <vector>

#include <spdlog/spdlog.h>
#include <glm/glm.hpp>

#include "utilities/math/Pos2.hpp"
#include "layers/LayerStack.hpp"
#include "renderer/AssetLibrarian.h"
#include "utilities/Timer.h"




struct ApplicationBuilder
{
	ApplicationBuilder();



	/// <summary>
	/// Initializes the application's window
	/// </summary>
	/// <param name="titleIn">Specifies the name of the application's window</param>
	/// <param name="widthIn">Specifies the application windows width</param>
	/// <param name="heightIn">Specifies the application windows height</param>
	/// <param name="flagsIn">
	/// Specifies the SDL window flags, when set to a value of '0' no flags are set
	/// <para>See "https://wiki.libsdl.org/SDL_WindowFlags" for a full list of SDL window flags</para>
	/// </param>
	/// <returns>A referance to this ApplicationBuilder</returns>
	ApplicationBuilder& setWindow(const std::string& titleIn, int widthIn, int heightIn, unsigned int flagsIn = 0);



	/// <summary>
	/// Initializes the logger
	/// </summary>
	/// <param name="fileLocationIn">Specifies the logger's log file location</param>
	/// <param name="levelIn">Specifies the logger's logging level</param>
	/// <returns>A referance to this ApplicationBuilder</returns>
	ApplicationBuilder& setLogger(const std::string& fileLocationIn, spdlog::level::level_enum levelIn);



	/// <summary>
	/// Sets the number of application ticks per second
	/// </summary>
	/// <param name="ticksIn">Specifies the application tick rate in ticks per second</param>
	/// <returns>A referance to this ApplicationBuilder</returns>
	ApplicationBuilder& setTickRate(unsigned int ticksIn);



	/// <summary>
	/// Determines the name of the application's window
	/// </summary>
	std::string windowTitle;



	/// <summary>
	/// Determines the starting size of the application's window
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
	/// Determines the number of application ticks per second
	/// <para>By default it is 20 ticks per second</para>
	/// </summary>
	unsigned int tickRate;
};



class Application 
{
public:

	Application(const ApplicationBuilder& builderIn);



	~Application();



	/// <summary>
	/// Adds a new layer to this application
	/// </summary>
	/// <typeparam name="LayerType">Specifies the Application Layer</typeparam>
	/// <typeparam name="...Args"></typeparam>
	/// <param name="...args">Specifies constructor arguments</param>
	template<class LayerType, typename... Args>
	void addLayer(Args&&... args) { m_layerStack.push<LayerType>(*this, std::forward<Args>(args)...); }


	
	/// <summary>
	/// Starts the application loop which will continue running until Application::markOver is called
	/// </summary>
	void run();



	/// <summary>
	/// Checks if this application has endded
	/// </summary>
	/// <returns>True if the game has endded</returns>
	bool isDone() const;



	/// <summary>
	/// Tell's this application to stop
	/// </summary>
	void markOver();



	/// <summary>
	/// Checks if the specified key has been pressed on the keyboard
	/// </summary>
	/// <param name="scancode">Specifies which key</param>
	/// <returns></returns>
	static bool isKeyPressed(int scancode);



	/// <summary>
	/// Gets the mouse's current location inside of the window
	/// </summary>
	/// <returns></returns>
	static glm::ivec2 getMouseLocation();



	/// <summary>
	/// Gets this application's renderer
	/// </summary>
	class Renderer& renderer();



	/// <summary>
	/// Loads and register the specified texture
	/// </summary>
	/// <param name="fileLocationIn">Specifies the location of the texture/texture atlas file</param>
	void registerTexture(const std::string& fileLocationIn);



	/// <summary>
	/// Gets this application's asset manager
	/// </summary>
	/// <returns></returns>
	AssetLibrarian& assetLibrarian();



	/// <summary>
	/// Gets this application's audio manager
	/// </summary>
	class AudioMixer& audioMixer();



	/// <summary>
	/// Gets this application's world manager
	/// </summary>
	class WorldStack& worldStack();



	/// <summary>
	/// Gets this application's entity manager
	/// </summary>
	class EntityJournal& entities();



	/// <summary>
	/// <para>nullable</para>
	/// Gets this application's Window
	/// </summary>
	const class Window* getWindow() const;



	/// <summary> 
	/// <para>nullable</para>
	/// Gets this application's Camera
	/// </summary>
	class Camera* getCamera();



private:

	/// <summary>
	/// Initializes this application's window
	/// </summary>
	/// <param name="title">Specifies title of the window</param>
	/// <param name="Window_Height">Specifies the height of the window measured in pixels</param>
	/// <param name="Window_Width">Specifies the width of the window measured in pixels</param>
	/// <param name="flags">
	/// <para>Specifies SDL window flags</para>
	/// <para>See "https://wiki.libsdl.org/SDL_WindowFlags" for a full list of all SDL window flags</para>
	/// </param>
	void initWindow(const std::string& title, int Window_Height, int Window_Width, uint32_t flags);



	std::shared_ptr<spdlog::logger> m_logger;

	LayerStack m_layerStack;

	std::unique_ptr<class Renderer> m_renderer;

	std::unique_ptr<class AudioMixer> m_audioManager;

	std::unique_ptr<class WorldStack> m_worlds;

	std::unique_ptr<class EntityJournal> m_entities;

	std::unique_ptr<class Window> m_window;

	std::shared_ptr<class Camera> m_camera;

	Timer m_timer;

	bool m_gameOver;

	unsigned int m_tickRate;

	int m_onWindowEvent = 0;
};


#endif /* APPLICATION_HPP_ */




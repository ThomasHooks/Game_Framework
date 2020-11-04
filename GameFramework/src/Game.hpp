#ifndef GAME_H_
#define GAME_H_


#include <string>
#include <memory>
#include <vector>




class Game 
{
public:

	/// <summary>
	/// </summary>
	/// <param name="titleIn">Specifies title of the window</param>
	/// <param name="windowHeight">Specifies the height of the window measured in pixels</param>
	/// <param name="windowWidth">Specifies the width of the window measured in pixels</param>
	/// <param name="flags">
	/// <para>Specifies SDL window flags</para>
	/// <para>See "https://wiki.libsdl.org/SDL_WindowFlags" for a full list of all SDL window flags</para>
	/// </param>
	/// <param name="MaxFPS">Specifies the number of game ticks per second</param>
	Game(const std::string &titleIn, int windowHeight, int windowWidth, uint32_t flags, int MaxFPS);



	~Game();



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
	void initWindow(const std::string &title, int Window_Height, int Window_Width, uint32_t flags);


	
	/// <summary>
	/// Starts the game loop which will continue running until Game::markOver is called
	/// </summary>
	void run();



	/// <summary>
	/// Adds a new Game State to this Game
	/// </summary>
	/// <param name="stateIn">A pointer to the new Game State</param>
	void addState(class IGameState* stateIn);



	/// <summary>
	/// Removes the current Game State
	/// </summary>
	void removeState();



	/// <summary>
	/// Checks if the game has endded
	/// </summary>
	/// <returns>True if the game has endded</returns>
	bool isOver() const;



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
	/// Gets this game's logger
	/// </summary>
	class Logger& getLogger();



	/// <summary>
	/// Gets this game's renderer
	/// </summary>
	class Renderer& getRenderManager();



	/// <summary>
	/// Gets this game's audio manager
	/// </summary>
	class AudioMixer& getMixer();



	/// <summary>
	/// Gets this game's world manager
	/// </summary>
	class WorldStack& getWorldStack();



	/// <summary>
	/// Gets this game's entity manager
	/// </summary>
	class EntityManager& getEntityManager();



	/// <summary>
	/// Gets this game's timer
	/// </summary>
	class GameTimer& getTimer();



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



protected:

	/// <summary>
	/// Gets the current Game State
	/// </summary>
	class IGameState& getState();



	/// <summary>
	/// Checks if the Game State stack is empty
	/// </summary>
	/// <returns>True if it's empty</returns>
	bool isNullState() const;



private:

	mutable std::unique_ptr<class Logger> logger;

	std::unique_ptr<class Renderer> renderer;

	std::unique_ptr<class AudioMixer> audioManager;

	std::unique_ptr<class WorldStack> worlds;

	std::unique_ptr<class EntityManager> entityManager;

	std::unique_ptr<class GameTimer> timer;

	std::unique_ptr<class SDLWindowWrapper> windowWrap;

	std::unique_ptr<class GameCamera> cameraWrap;

	bool gameOver;

	bool hasBeenInit;

	unsigned int tickRate;

	std::vector<std::unique_ptr<class IGameState>> states;

	int m_onWindowEvent = 0;
};


#endif /* GAME_H_ */




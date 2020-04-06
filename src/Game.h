//============================================================================
// Name       		: Game.h
// Author     		: Thomas Hooks
// Last Modified	: 04/05/2020
//============================================================================




#ifndef GAME_H_
#define GAME_H_


#include <string>
#include <memory>
#include <vector>


class Game {

public:

	Game();



	/*
	 * @param	title The title of the window
	 *
	 * @param	Window_Height The height of the window measured in pixels
	 *
	 * @param 	Window_Width The width of the window measured in pixels
	 *
	 * @param 	flag The flags for the window, mask of any of the following:
	 *          see "https://wiki.libsdl.org/SDL_WindowFlags" for window flags
	 *
	 * Constructor for the game framework that create a window defined by the caller
	 */
	Game(const std::string &titleIn, int windowHeight, int windowWidth, uint32_t flags, int MaxFPS);



	~Game();



	/*
	 * @param	titleIn The title of the window
	 *
	 * @param	widthIn The width of the window measured in pixels
	 *
	 * @param	heightIn The height of the window measured in pixels
	 *
	 * @param	flags The flags for the window, OR any of the following:
	 *				::SDL_WINDOW_FULLSCREEN,    ::SDL_WINDOW_OPENGL,
	 *              ::SDL_WINDOW_HIDDEN,        ::SDL_WINDOW_BORDERLESS,
	 *              ::SDL_WINDOW_RESIZABLE,     ::SDL_WINDOW_MAXIMIZED,
	 *              ::SDL_WINDOW_MINIMIZED,     ::SDL_WINDOW_INPUT_GRABBED,
	 *              ::SDL_WINDOW_ALLOW_HIGHDPI, ::SDL_WINDOW_VULKAN.
	 *    	  	see "https://wiki.libsdl.org/SDL_WindowFlags" for window flags
	 *
	 * Initializes the Window
	 */
	void initWindow(const std::string &title, int Window_Height, int Window_Width, uint32_t flags);



	/*
	 * Starts the game loop
	 * which will continue running until Game::markOver is called
	 */
	void run();



	/*
	 * @param	stateIn A pointer to the new Game State
	 *
	 * Adds a new Game State to this Game
	 */
	void addState(class IGameState* stateIn);



	//Removes the current Game State
	void removeState();



	// @return	True if the game has ended
	bool isOver() const;



	//Marks the game to be stopped
	void markOver();



	// @return	Gets this game's logger
	class GameLogger& getLogger();



	// @return	Gets this game's renderer
	class RendererManager& getRenderManager();



	// @return	Gets this game's audio manager
	class AudioManager& getMixer();



	// @return	Gets this game's world manager
	class MapManager& getWorldManager();



	// @return	Gets this game's entity manager
	class EntityManager& getEntityManager();



	// @return	Gets this game's timer
	class GameTimer& getTimer();



	/*
	 * @nullable
	 *
	 * @return	Gets this game's Window
	 */
	const class SDLWindowWrapper* getWindow() const;



	/*
	 * @nullable
	 *
	 * @return	Gets this game's Camera
	 */
	class GameCamera* getCamera();



protected:

	// @return	Gets the current Game State
	class IGameState& getState();



	// @return	True if the Game State stack is empty
	bool isNullState() const;



private:

	mutable std::unique_ptr<class GameLogger> logger;

	std::unique_ptr<class RendererManager> renderManager;

	std::unique_ptr<class AudioManager> audioManager;

	std::unique_ptr<class MapManager> worldManager;

	std::unique_ptr<class EntityManager> entityManager;

	std::unique_ptr<class GameTimer> timer;

	std::unique_ptr<class SDLWindowWrapper> windowWrap;

	std::unique_ptr<class GameCamera> cameraWrap;

	bool gameOver;

	bool hasBeenInit;

	unsigned int tickRate;

	std::vector<std::unique_ptr<class IGameState>> states;
};


#endif /* GAME_H_ */




//============================================================================
// Name       		: Game.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/21/2020
//============================================================================




#include <SDL.h>

#include "Game.h"

#include "entities/Game_Dynamic.h"
#include "gamestates/BlankGameState.h"
#include "gamestates/IGameState.h"
#include "managers/StateManager.h"




/*
 * Default constructor, game will need to be initialized by calling init
 */
Game::Game()
		: Log(Level::TRACE),
		  Render(&Log),
		  State(this),
		  Map(&Log),
		  Entities(&Log),
		  Timer(),
		  b_gameOver(false),
		  b_hasBeenInit(false),
		  f_cameraX(0),
		  f_cameraY(0),
		  n_maxFPS(60),
		  window(nullptr),
		  WindowHeight(0),
		  WindowWidth(0) {

	Log.message(Level::INFO, "Initializing SDL", Output::TXT_FILE);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	const int startingStateID = 0;
	State.Push(new BlankGameState(this, startingStateID));
}



/*
 * @param	title  				The title of the window
 *
 * @param	Window_Height		The height of the window measured in pixels
 *
 * @param 	Window_Width		The width of the window measured in pixels
 *
 * @param 	flag				The flags for the window, mask of any of the following:
 *               				::SDL_WINDOW_FULLSCREEN,    ::SDL_WINDOW_OPENGL,
 *               				::SDL_WINDOW_HIDDEN,        ::SDL_WINDOW_BORDERLESS,
 *               				::SDL_WINDOW_RESIZABLE,     ::SDL_WINDOW_MAXIMIZED,
 *               				::SDL_WINDOW_MINIMIZED,     ::SDL_WINDOW_INPUT_GRABBED,
 *               				::SDL_WINDOW_ALLOW_HIGHDPI, ::SDL_WINDOW_VULKAN.
 *
 *               			See "https://wiki.libsdl.org/SDL_WindowFlags" for more window flags
 *
 *
 * Constructor for the game engine class that create a window defined by the caller, and sets SDL flags
 */
Game::Game(const char * title, int Window_Height, int Window_Width, Uint32 flags, int Max_FPS)
		: Log(Level::TRACE),
		  Render(&Log),
		  State(this),
		  Map(&Log),
		  Entities(&Log),
		  Timer(),
		  b_gameOver(false),
		  b_hasBeenInit(true),
		  f_cameraX(0),
		  f_cameraY(0),
		  n_maxFPS(Max_FPS) {

	WindowHeight = Window_Height;
	WindowWidth = Window_Width;

	//Start SDL2
	Log.message(Level::INFO, "Initializing SDL", Output::TXT_FILE);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	//Create a Window in the middle of the screen that is Window_Width by Window_Height in (px)
	Log.message(Level::INFO, "Initializing Window", Output::TXT_FILE);
	window = SDL_CreateWindow(title,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WindowWidth, WindowHeight,
			flags);

	this->Render.init(this->window);

	const int startingStateID = 0;
	State.Push(new BlankGameState(this, startingStateID));
}



Game::~Game(){

	Log.message(Level::INFO, "Closing window", Output::TXT_FILE);
	SDL_DestroyWindow(window);
	window = nullptr;

	Log.message(Level::INFO, "Terminating SDL", Output::TXT_FILE);
	SDL_Quit();
}



/*
 *
 */
bool Game::init(const char * title, int Window_Height, int Window_Width, Uint32 flags, int Max_FPS){

	if (!b_hasBeenInit){

		b_hasBeenInit = true;
		Log.message(Level::INFO, "Initializing Window", Output::TXT_FILE);

		WindowHeight = Window_Height;
		WindowWidth = Window_Width;

		//Create a Window in the middle of the screen that is Window_Width by Window_Height in (px)
		window = SDL_CreateWindow(title,
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				WindowWidth, WindowHeight,
				flags);

		this->Render.init(this->window);

		set_maxFPS(Max_FPS);

		return true;
	}

	else return false;
}



/*
 *
 */
void Game::run(){

	if (b_hasBeenInit){
		while(!get_gameOver()){

			//Update current time in (ms)
			Timer.Start();

			//Update the current game state
			State.Process();

			//Check if the current game state needs to be change
			State.Check();

			//Check the frame rate and limit if necessary
			Timer.Check(get_maxFPS());
		}
	}

	else {
		Log.message(Level::FATAL, "Object Game has not been initialized", Output::TXT_FILE);
		set_gameOver(true);
	}

	return;
}








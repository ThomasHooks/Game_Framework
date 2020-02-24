//============================================================================
// Name       		: Game.cpp
// Author     		: Thomas Hooks
// Last Modified	: 02/22/2020
//============================================================================




#include <SDL.h>

#include "Game.h"

#include "BlankGameState.h"
#include "Game_Dynamic.h"
#include "GameState.h"
#include "State_Manager.h"




Game::Game()
		: State(this),
		  Map(),
		  Assets(),
		  Timer(),
		  Log(Level::Trace),
		  b_gameOver(false),
		  b_hasBeenInit(false),
		  f_cameraX(0),
		  f_cameraY(0),
		  n_maxFPS(60),
		  window(nullptr),
		  renderer(nullptr),
		  WindowHeight(0),
		  WindowWidth(0) {
	/*
	 * brief	Default constructor, game will need to be initialized by calling init
	 */




	//Start SDL2
	Log.Message(Level::Info, "Initializing SDL", Output::File_txt);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	//Starting game state
	const int startingStateID = 0;
	//State.Push(new cGSBlack(this, startingStateID));
	State.Push(new BlankGameState(this, startingStateID));

	return;
}


//----------------------------------------------------------------------------


Game::Game(const char * title, int Window_Height, int Window_Width, Uint32 flags, int Max_FPS)
		: State(this),
		  Map(&Log, &Assets),
		  Assets(),
		  Timer(),
		  Log(Level::Trace),
		  b_gameOver(false),
		  b_hasBeenInit(true),
		  f_cameraX(0),
		  f_cameraY(0),
		  n_maxFPS(Max_FPS) {
	/*
	 * brief	Constructor for the game engine class that create a window defined by the caller, and sets SDL flags
	 *
	 * param	title  				The title of the window
	 *
	 * param	Window_Height		The height of the window measured in pixels
	 *
	 * param 	Window_Width		The width of the window measured in pixels
	 *
	 * param 	flag				The flags for the window, mask of any of the following:
	 *               				::SDL_WINDOW_FULLSCREEN,    ::SDL_WINDOW_OPENGL,
 	 *               				::SDL_WINDOW_HIDDEN,        ::SDL_WINDOW_BORDERLESS,
 	 *               				::SDL_WINDOW_RESIZABLE,     ::SDL_WINDOW_MAXIMIZED,
 	 *               				::SDL_WINDOW_MINIMIZED,     ::SDL_WINDOW_INPUT_GRABBED,
 	 *               				::SDL_WINDOW_ALLOW_HIGHDPI, ::SDL_WINDOW_VULKAN.
 	 *
 	 *               			See "https://wiki.libsdl.org/SDL_WindowFlags" for more window flags
	 */




	WindowHeight = Window_Height;
	WindowWidth = Window_Width;

	//Start SDL2
	Log.Message(Level::Info, "Initializing SDL", Output::File_txt);
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	//Create a Window in the middle of the screen that is Window_Width by Window_Height in (px)
	Log.Message(Level::Info, "Initializing window", Output::File_txt);
	window = SDL_CreateWindow(title,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WindowWidth, WindowHeight,
			flags);

	renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED);


	Assets.init(&Log, renderer);


	//Starting game state
	const int startingStateID = 0;
	//State.Push(new cGSBlack(this, startingStateID));
	State.Push(new BlankGameState(this, startingStateID));


	//----All of this should be removed later----
	//Load the test sprite
	Assets.add_texture("Mario.png", "./data/gfx/Mario.png");

	//Load the test tile sheet
	Assets.add_texture("tile_test.png", "./data/gfx/tile_test.png");
	//----All of this should be removed later----

	return;
}


//----------------------------------------------------------------------------


Game::~Game(){
	/*
	 *
	 */




	Log.Message(Level::Info, "Closing window", Output::File_txt);
	SDL_DestroyWindow(window);
	window = nullptr;


	Log.Message(Level::Info, "Freeing renderer", Output::File_txt);
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;


	Log.Message(Level::Info, "Freeing all assets", Output::File_txt);
	Assets.remove_allTextures();

	//TODO free all sound effects Mix_Chunk

	//TODO free all music Mix_Music

	//TODO free all true type font


	Log.Message(Level::Info, "Terminating SDL", Output::File_txt);
	SDL_Quit();

	return;
}


//----------------------------------------------------------------------------


bool Game::init(const char * title, int Window_Height, int Window_Width, Uint32 flags, int Max_FPS){
	/*
	 *
	 */




	if (!b_hasBeenInit){

		b_hasBeenInit = true;
		Log.Message(Level::Info, "Initializing window", Output::File_txt);

		WindowHeight = Window_Height;
		WindowWidth = Window_Width;

		//Create a Window in the middle of the screen that is Window_Width by Window_Height in (px)
		window = SDL_CreateWindow(title,
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				WindowWidth, WindowHeight,
				flags);


		renderer = SDL_CreateRenderer(window, -1,
				SDL_RENDERER_ACCELERATED);


		Assets.init(&Log, renderer);

		Map.init(&Log, &Assets);


		set_maxFPS(Max_FPS);

		return true;
	}

	else return false;
}


//----------------------------------------------------------------------------


void Game::run(void){
	/*
	 *
	 */




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
		Log.Message(Level::Fatal, "Object Game has not been initialized", Output::File_txt);
		set_gameOver(true);
	}

	return;
}








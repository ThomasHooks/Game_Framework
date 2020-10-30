//============================================================================
// Name       		: main.cpp
// Author     		: Thomas Hooks
// Last Modified	: 11/2/2019
// Description		: An example of how the Game class should be used in main
//============================================================================




#include <SDL.h>
#include "Game.h"
//#include "myState.h"




int main(int argc, char** argv) {

	const int Window_Height = 480;
	const int Window_Width = 640;
	const int Max_FPS = 60;

	//See "https://wiki.libsdl.org/SDL_WindowFlags" for more window flags
	//To add multiple flags use the bitwise or operator
	//when SDL_WindowFlags = 0 no flags are set

	const Uint32 SDL_WindowFlags = 0;

	Game gameTest("Name of Game", Window_Height, Window_Width,
			SDL_WindowFlags, Max_FPS);


	//If the default constructor was used call the init method
	/*gameTest.initWindow("Name of Game", Window_Height, Window_Width,
			SDL_WindowFlags, Max_FPS);*/


	//Push the introduction game state here before loop
	//gameTest.addState(new myState(&gameTest, 0));


	//Game Loop
	gameTest.run();


	return EXIT_SUCCESS;
}







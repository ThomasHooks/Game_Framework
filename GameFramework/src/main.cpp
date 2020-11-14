#include <SDL.h>

#include "Game.hpp"
#include "layers/ExampleLayer.hpp"



//This is an example of how the main function can be set up
//Also make sure to add main's arguments as they are required by SDL
int main(int argc, char** argv) 
{
	//See "https://wiki.libsdl.org/SDL_WindowFlags" for SDL window flags
	//To add multiple flags use the bitwise or operator
	//when windowFlags = 0 no flags are set
	const unsigned int windowFlags = 0;
	const int windowWidth = 640;
	const int windowHeight = 480;

	GameBuilder builder;
	builder
		.setWindow("Name of Game", windowWidth, windowHeight, windowFlags)
		.setTickRate(20)
		.setLogger("logs/log.txt", spdlog::level::trace);

	Game gameTest(builder);

	//Add all Game Layers before calling run
	gameTest.addLayer<ExampleLayer>(gameTest);

	gameTest.run();

	return EXIT_SUCCESS;
}








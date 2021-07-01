#include <SDL.h>

#include "Application.hpp"
#include "layers/ExampleLayer.hpp"




/*
This is an example of how the main function can be set up

Also make sure to add main's arguments as they are required by SDL
*/
int main(int argc, char** argv) 
{
	/*
	See "https://wiki.libsdl.org/SDL_WindowFlags" for SDL window flags

	To add multiple flags use the bitwise or operator

	when windowFlags = 0 no flags are set
	*/
	const unsigned int windowFlags = 0;

	const int windowWidth = 1280;
	const int windowHeight = 960;

	ApplicationBuilder builder;
	builder.setWindow("Name of Application", windowWidth, windowHeight, windowFlags)
		   .setTickRate(20)
		   .setLogger("logs/log.txt", spdlog::level::trace);

	Application appTest(builder);

	//Add all application layers before calling run
	appTest.addLayer<ExampleLayer>(appTest);

	appTest.run();

	return EXIT_SUCCESS;
}




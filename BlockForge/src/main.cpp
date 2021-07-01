#include <SDL.h>

#include "Application.hpp"
#include "layers/ExampleLayer.hpp"




int main(int argc, char** argv) 
{
	ApplicationBuilder builder;
	builder.setWindow("BlockForge", 1280, 960, 0)
		   .setTickRate(20)
		   .setLogger("logs/log.txt", spdlog::level::trace);

	Application blockForge(builder);

	blockForge.addLayer<ExampleLayer>(blockForge);

	blockForge.run();

	return EXIT_SUCCESS;
}




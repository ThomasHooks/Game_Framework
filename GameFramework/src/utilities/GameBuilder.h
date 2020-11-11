#ifndef GAMEBUILDER_H_
#define GAMEBUILDER_H_


#include <string>

#include "utilities/Loggers.hpp"
#include "utilities/math/Pos2.hpp"




class GameBuilder 
{
public:

	GameBuilder();



	GameBuilder& setLogFile(const std::string& location);



	GameBuilder& setWindowName(const std::string& nameIn);



	GameBuilder& setWindowSize(const Pos2N& size);



	GameBuilder& setWindowFlags(uint32_t flagsIn);



	GameBuilder& setFPSLimit(int FPSLimit);



protected:

	std::string logFileLocation;

	spdlog::level::level_enum level = spdlog::level::trace;

	std::string windowName;

	Pos2N windowSize;

	uint32_t windowFlags;

	int maxFPS;

	friend class Game;
};


#endif




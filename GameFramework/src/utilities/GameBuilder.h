#ifndef GAMEBUILDER_H_
#define GAMEBUILDER_H_


#include <string>

#include "utilities/Loggers.hpp"
#include "physics/Dimension.h"




class GameBuilder 
{
public:

	GameBuilder();



	~GameBuilder();



	//GameBuilder& setLoggerLevel(Logger::Level levelIn);



	GameBuilder& setLogFile(const std::string &location);



	GameBuilder& setWindowName(const std::string &nameIn);



	GameBuilder& setWindowSize(const Dimension &size);



	GameBuilder& setWindowFlags(uint32_t flagsIn);



	GameBuilder& setFPSLimit(int FPSLimit);



protected:

	std::string logFileLocation;

	std::string windowName;

	Dimension windowSize;

	uint32_t windowFlags;

	int maxFPS;

	friend class Game;
};


#endif /* GAMEBUILDER_H_ */




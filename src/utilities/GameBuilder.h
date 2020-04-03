//============================================================================
// Name       		: GameBuilder.h
// Author     		: Thomas Hooks
// Last Modified	: Mar 31, 2020
//============================================================================




#ifndef GAMEBUILDER_H_
#define GAMEBUILDER_H_


#include <string>

#include "GameLogger.h"
#include "Dimension.h"


class GameBuilder {

public:

	GameBuilder();



	~GameBuilder();



	GameBuilder& setLoggerLevel(EnumLogLevel levelIn);



	GameBuilder& setLogFile(const std::string &location);



	GameBuilder& setWindowName(const std::string &nameIn);



	GameBuilder& setWindowSize(const Dimension &size);



	GameBuilder& setWindowFlags(uint32_t flagsIn);



	GameBuilder& setFPSLimit(int FPSLimit);



protected:

	EnumLogLevel logLevel;

	std::string logFileLocation;

	std::string windowName;

	Dimension windowSize;

	uint32_t windowFlags;

	int maxFPS;

	friend class Game;
};


#endif /* GAMEBUILDER_H_ */




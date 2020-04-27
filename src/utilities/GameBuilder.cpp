//============================================================================
// Name       		: GameBuilder.cpp
// Author     		: Thomas Hooks
// Last Modified	: Mar 31, 2020
//============================================================================




#include "GameBuilder.h"




GameBuilder::GameBuilder()
	: logLevel(Logger::Level::TRACE),
	  logFileLocation("./log.txt"),
	  windowName(""),
	  windowSize(640, 480),
	  windowFlags(0),
	  maxFPS(60) {}



GameBuilder::~GameBuilder() {}



GameBuilder& GameBuilder::setLoggerLevel(Logger::Level levelIn){
	this->logLevel = levelIn;
	return *this;
}



GameBuilder& GameBuilder::setLogFile(const std::string &location){
	this->logFileLocation = location;
	return *this;
}



GameBuilder& GameBuilder::setWindowName(const std::string &nameIn){
	this->windowName = nameIn;
	return *this;
}



GameBuilder& GameBuilder::setWindowSize(const Dimension &size){
	this->windowSize.width = size.width;
	this->windowSize.height = size.height;
	return *this;
}



GameBuilder& GameBuilder::setWindowFlags(uint32_t flagsIn){
	this->windowFlags = flagsIn;
	return *this;
}



GameBuilder& GameBuilder::setFPSLimit(int FPSLimit){
	std::abs(FPSLimit) < 10 ? this->maxFPS = 10 : this->maxFPS = std::abs(FPSLimit);
	return *this;
}








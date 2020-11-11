#include "GameBuilder.h"




GameBuilder::GameBuilder()
	: logFileLocation("./log.txt"), windowName(""), windowSize(640, 480), windowFlags(0), maxFPS(60) 
{}



GameBuilder& GameBuilder::setLogFile(const std::string& location)
{
	this->logFileLocation = location;
	return *this;
}



GameBuilder& GameBuilder::setWindowName(const std::string& nameIn)
{
	this->windowName = nameIn;
	return *this;
}



GameBuilder& GameBuilder::setWindowSize(const Pos2N& size)
{
	this->windowSize.x = size.x;
	this->windowSize.y = size.y;
	return *this;
}



GameBuilder& GameBuilder::setWindowFlags(uint32_t flagsIn)
{
	this->windowFlags = flagsIn;
	return *this;
}



GameBuilder& GameBuilder::setFPSLimit(int FPSLimit)
{
	std::abs(FPSLimit) < 10 ? this->maxFPS = 10 : this->maxFPS = std::abs(FPSLimit);
	return *this;
}








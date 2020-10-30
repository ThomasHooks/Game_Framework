//============================================================================
// Name       		: GameTimer.cpp
// Author     		: Thomas Hooks
// Last Modified	: 04/04/2020
//============================================================================




#include <SDL.h>
#include <ctime>

#include "GameTimer.h"




GameTimer::GameTimer()
	: tickStart(0),
	  stopped(true) {}



GameTimer::~GameTimer() {}



//Starts a Timer that measure the number of a ticks in milliseconds
void GameTimer::start() {
	this->stopped = false;
	this->tickStart = SDL_GetTicks();
}



//Stops this timer
void GameTimer::stop() {
	this->stopped = true;
	this->tickStart = 0;
}



//@return	Gets the number of seconds since this Timer was started
float GameTimer::getDelta() const {
	return getTicks()/1000.0f;
}



//@return	Gets the number of ticks since this Timer was started
unsigned int GameTimer::getTicks() const {
	return this->stopped ? 0 : SDL_GetTicks() - this->tickStart;
}



//@return	True if this Timer is running
bool GameTimer::isRunning() const {
	return !this->stopped;
}








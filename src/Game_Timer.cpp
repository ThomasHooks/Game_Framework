//============================================================================
// Name       		: Game_Timer.cpp
// Author     		: Thomas Hooks
// Version    		: 1
// Last Modified	: 11/2/2019
// Description		:
//============================================================================




#include "Game_Timer.h"
#include <SDL.h>
#include <ctime>




Game_Timer::Game_Timer() {
	//Initialize clock

	frameStart = SDL_GetTicks();
	f_deltaTime = 0.0f;

	return;
}


Game_Timer::~Game_Timer() {
	//Nothing to free
	//Do nothing
}


void Game_Timer::Start(void){
	/*
	 * *brief* Starts a timer that measure the length of a frame in (ms)
	 *
	 * This method is to be called at the beginning of the loop
	 * so that the engine can measure the time it takes to complete one frame
	 *
	 * */



	//Update current time in (ms) since SDL was initialized
	frameStart = SDL_GetTicks();

	return;

}


void Game_Timer::Check(const int Max_FPS){
	/*
	 * *brief* Prevents the game from exceeding its maximum frames rate
	 *
	 * This method is to be called at the end of the game loop
	 * to slow the system down
	 *
	 * */



	const int frameDelay = 1000/Max_FPS;

	//Calculate this frames time length
	f_deltaTime = SDL_GetTicks() - frameStart;

	//Check if the frame rate needs to be limited
	if(frameDelay > f_deltaTime){
		//The frame rate is above the maximum limit
		//So the game is delayed by the difference
		SDL_Delay(frameDelay - f_deltaTime);

		//Update delta time to reflect the delay
		f_deltaTime = f_deltaTime + (frameDelay - f_deltaTime);
	}

	return;
}


//============================================================================





//============================================================================
// Name       		: GameTimer.h
// Author     		: Thomas Hooks
// Last Modified	: 04/03/2020
//============================================================================




#ifndef SRC_GAME_TIMER_H_
#define SRC_GAME_TIMER_H_


#include <stdint.h>


class GameTimer {

public:

	GameTimer();



	~GameTimer();



	//Starts a Timer that measure the number of a ticks in milliseconds
	void start();



	//Stops this timer
	void stop();



	//@return	Gets the number of seconds since this Timer was started
	float getDelta() const;



	//@return	Gets the number of ticks since this Timer was started
	unsigned int getTicks() const;



	//@return	True if this Timer is running
	bool isRunning() const;



private:

	unsigned int tickStart;

	bool stopped;
};


#endif /* SRC_GAME_TIMER_H_ */




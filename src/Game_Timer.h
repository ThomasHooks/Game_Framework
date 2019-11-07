//============================================================================
// Name       		: Game_Timer.h
// Author     		: Thomas Hooks
// Version    		: 1
// Last Modified	: 11/2/2019
// Description		:
//============================================================================




#ifndef SRC_GAME_TIMER_H_
#define SRC_GAME_TIMER_H_


#include <stdint.h>


class Game_Timer {

public:

	Game_Timer();
	~Game_Timer();

	//Starts a timer that measure the length of a frame in (ms)
	void Start(void);

	//Prevents the game from exceeding its maximum frames rate
	void Check(const int Max_FPS);

	//Getters and setters for the timer
	float get_deltaTime(void) const {return f_deltaTime/1000.0f;}

private:

	//Current time since SDL was Initialized
	uint32_t frameStart;

	//Time since the last frame
	float f_deltaTime;
};




#endif /* SRC_GAME_TIMER_H_ */


//============================================================================





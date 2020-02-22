//============================================================================
// Name       		: State_Manager.h
// Author     		: Thomas Hooks
// Version    		: 1
// Last Modified	: 11/2/2019
// Description		:
//============================================================================





#ifndef SRC_STATE_MANAGER_H_
#define SRC_STATE_MANAGER_H_




#include <vector>
#include <memory>
#include "Game_Manager.h"
#include "GameState.h"




class State_Manager : public Game_Manager<class GameState> {
public:

	State_Manager(class Game *gamePtr);

	~State_Manager();

	State_Manager(const State_Manager &other) = delete;

	State_Manager(State_Manager &&other) = delete;

	//------------------------------------------------------------------------

	//Processes the current state
	void Process(void);

	//Checks if the current state needs to be changed
	void Check(void);

	//Getters and setters
	int get_stateFlag(void) const {return n_gameStateFlag;}

	void set_steateFlag(int newFlag) {n_gameStateFlag = newFlag;}

	//------------------------------------------------------------------------

private:

	int n_gameStateFlag;		//Stores the current or next game state ID

};




#endif /* SRC_STATE_MANAGER_H_ */








//============================================================================
// Name       		: State_Manager.h
// Author     		: Thomas Hooks
// Last Modified	: 11/2/2019
//============================================================================





#ifndef SRC_STATE_MANAGER_H_
#define SRC_STATE_MANAGER_H_




#include <vector>
#include <memory>

#include "../gamestates/GameState.h"
#include "GameManager.h"




class StateManager : public GameManager<class GameState> {
public:

	StateManager(class Game *gamePtr);

	~StateManager();

	StateManager(const StateManager &other) = delete;

	StateManager(StateManager &&other) = delete;

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








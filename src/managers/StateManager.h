//============================================================================
// Name       		: StateManager.h
// Author     		: Thomas Hooks
// Last Modified	: 03/22/2020
//============================================================================




#ifndef SRC_STATE_MANAGER_H_
#define SRC_STATE_MANAGER_H_




#include <vector>
#include <memory>

#include "../gamestates/IGameState.h"
#include "GameManager.h"




class StateManager : public GameManager<IGameState> {
public:

	StateManager(class Game *gamePtr);



	~StateManager();



	StateManager(const StateManager &other) = delete;



	StateManager(StateManager &&other) = delete;



	/*
	 * Processes the current game state in the stack
	 * by calling its method's that gets user inputs, processes
	 * physics, processes events, processes AI, and rendering all
	 * changes in the game window
	 */
	void Process();



	//Checks if the current state needs to be changed
	void Check();



	//Gets the current GameState ID
	int getStateID() const;



protected:

	//Sets the current GameState ID
	void setStateID(int stateIDIn);



private:

	int stateID;
};


#endif /* SRC_STATE_MANAGER_H_ */




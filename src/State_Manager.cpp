//============================================================================
// Name       		: State_Manager.cpp
// Author     		: Thomas Hooks
// Version    		: 1
// Last Modified	: 11/2/2019
// Description		:
//============================================================================




#include "State_Manager.h"
#include "Game_Manager.h"
#include "Game.h"
#include "GameState.h"




State_Manager::State_Manager(class Game *gamePtr)
	: Game_Manager(gamePtr) {
	//Initialize the state manager object

	const int initialFlag = 0;

	n_gameStateFlag = initialFlag;

	return;
}


State_Manager::~State_Manager() {
	// Do Nothing
	return;
}


//----------------------------------------------------------------------------


void State_Manager::Process(void){
	/*
	 * *brief*	Processes the current game state
	 *
	 *	retrn	This method can change the bGameOver flag
	 *
	 *			This method will process the current game state in the stack
	 *			by calling its method's that gets user inputs, processes
	 *			physics, processes events, processes AI, and rendering all
	 *			changes in the game window
	 */




	if(Empty()){

		game->Log.Message(Level::Fatal,
				"State stack is empty, application is in an unknown state!",
				Output::File_txt);
		/*
		 * End the game because of the fatal error
		 *
		 * When the state stack is empty the user will be unable to terminate
		 * the application without causing a memory leak
		 */
		game->set_gameOver(true);
	}

	else{
		//Check for player input
		v_stack.back()->GetUserInput();

		//Process physics and events
		v_stack.back()->Process();

		//Render current game state
		v_stack.back()->Draw();
	}

	return;
}


//----------------------------------------------------------------------------


void State_Manager::Check(void){
	/*
	 * *brief*	Checks if the current game state needs to be changed
	 *
	 * 	retrn	This method can change the bGameOver flag
	 *
	 *			This method will check the current game state in the stack
	 *			if the stack is empty it will print an error message to the
	 *			console stating that the game is in an unknown is state
	 *			and will set the game over flag to true
	 * */




	if(Empty()){

		game->Log.Message(Level::Fatal,
				"State stack is empty, application is in an unknown state!",
				Output::File_txt);
		/*
		 * End the game because of the fatal error
		 *
		 * When the state stack is empty the user will be unable to terminate
		 * the application without causing a memory leak
		 */
		game->set_gameOver(true);
	}

	//Check if the game state needs to be changed
	//and change it as needed
	else v_stack.back()->ChangeState(n_gameStateFlag, game);

	return;
}


//----------------------------------------------------------------------------























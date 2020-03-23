//============================================================================
// Name       		: StateManager.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/21/2020
//============================================================================




#include "StateManager.h"
#include "../Game.h"
#include "../utilities/Dimension.h"
#include "../utilities/Position.h"
#include "../world/TileMap.h"




StateManager::StateManager(class Game *gamePtr)
	: GameManager(gamePtr) {

	const int initialFlag = 0;
	stateID = initialFlag;
}


StateManager::~StateManager() {}



/*
 * Processes the current game state in the stack
 * by calling its method's that gets user inputs, processes
 * physics, processes events, processes AI, and rendering all
 * changes in the game window
 */
void StateManager::Process(){

	if(Empty()) {

		game->Log.message(Level::FATAL, "State stack is empty, application is in an unknown state!", Output::TXT_FILE);
		game->set_gameOver(true);
		return;
	}

	TileMap* world = game->Map.getWorld();
	if(world == nullptr) {
		game->Log.message(Level::FATAL, "Null Pointer exception: Tried to render World, but world stack is empty!", Output::TXT_FILE);
		game->set_gameOver(true);
		return;
	}
	Dimension worldSize(world->width() * world->tileWidth(), world->height() * world->tileHeight());

	//Keep camera inside game boundaries
	Dimension windowSize(game->get_windowWidth(), game->get_windowHeight());
	double cameraX = game->get_cameraX() - windowSize.width/2.0;
	double cameraY = game->get_cameraY() - windowSize.height/2.0;

	if(cameraX < 0) cameraX = 0.0;
	else if(cameraX > worldSize.width - windowSize.width) cameraX = worldSize.width - windowSize.width;

	if(cameraY < 0) cameraY = 0.0;
	else if(cameraY > worldSize.height - windowSize.height) cameraY = worldSize.height - windowSize.height;

	Position cameraPos(cameraX, cameraY);
	v_stack.back()->render(cameraPos);
	v_stack.back()->GetUserInput();
	v_stack.back()->tick(cameraPos);
}



/*
 * Check the current game state in the stack
 * if the stack is empty it will print an error message to the
 * console stating that the game is in an unknown is state
 * and will set the game over flag to true
 */
void StateManager::Check(){

	if(Empty()) {
		game->Log.message(Level::FATAL, "State stack is empty, application is in an unknown state!", Output::TXT_FILE);
		game->set_gameOver(true);
	}

	//Check if the game state needs to be changed
	//and change it as needed
	else v_stack.back()->ChangeState(stateID, game);
}



//Gets the current GameState ID
int StateManager::getStateID() const {
	return this->stateID;
}



//Sets the current GameState ID
void StateManager::setStateID(int stateIDIn){
	this->stateID = stateIDIn;
}








//============================================================================
// Name       		: StateManager.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/31/2020
//============================================================================




#include "StateManager.h"
#include "../Game.h"
#include "../managers/MapManager.h"
#include "../world/TileMap.h"
#include "../utilities/Dimension.h"
#include "../utilities/Position.h"
#include "../utilities/SDLWindowWrapper.h"
#include "../utilities/GameCamera.h"
#include "../utilities/GameTimer.h"




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

		game->getLogger().message(Level::FATAL, "State stack is empty, application is in an unknown state!", Output::TXT_FILE);
		game->markOver();
		return;
	}

	TileMap* world = game->getWorldManager().getWorld();
	if(world == nullptr) {
		game->getLogger().message(Level::FATAL, "Null Pointer exception: Tried to render World, but world stack is empty!", Output::TXT_FILE);
		game->markOver();
		return;
	}

	Dimension worldSize(world->width() * world->tileWidth(), world->height() * world->tileHeight());
	GameCamera* camera = this->game->getCamera();
	camera->updatePos(worldSize, this->game->getTimer().get_deltaTime(), true);
	v_stack.back()->render(camera->getPos());
	v_stack.back()->onInputEvent();
	v_stack.back()->tick(camera->getPos());
}



/*
 * Check the current game state in the stack
 * if the stack is empty it will print an error message to the
 * console stating that the game is in an unknown is state
 * and will set the game over flag to true
 */
void StateManager::Check(){

	if(Empty()) {
		game->getLogger().message(Level::FATAL, "State stack is empty, application is in an unknown state!", Output::TXT_FILE);
		game->markOver();
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








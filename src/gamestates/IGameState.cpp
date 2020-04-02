//============================================================================
// Name       		: IGameState.cpp
// Author     		: Thomas Hooks
// Last Modified	: 04/01/2020
//============================================================================




#include "IGameState.h"
#include "../Game.h"
#include "../managers/RendererManager.h"
#include "../managers/EntityManager.h"
#include "../managers/MapManager.h"
#include "../world/TileMap.h"
#include "../utilities/Dimension.h"
#include "../utilities/Position.h"
#include "../utilities/GameLogger.h"
#include "../utilities/SDLWindowWrapper.h"
#include "../utilities/GameCamera.h"
#include "../utilities/GameTimer.h"




IGameState::IGameState(class Game *Game, int StateID)
	: nGameStateID(StateID),
	  game(Game) {}



/*
 * @param	camera The coordinates of the camera
 *
 * Renders the current GameState
 */
void IGameState::render(const Position &camera){

	this->game->getRenderManager().setDrawColor(0, 0, 0, 255);
	this->game->getRenderManager().clear();

	Dimension windowSize(game->getWindow()->width(), game->getWindow()->height());
	this->customDraw(camera, windowSize);

	//SDL_RenderPresent(game->get_renderer());
	this->game->getRenderManager().present();
}



//Gets the Entity Manager
class EntityManager& IGameState::getEntities(){
	return this->game->getEntityManager();
}



//Gets the World Manager
class MapManager& IGameState::getWorlds(){
	return this->game->getWorldManager();
}



//Gets the Renderer
class RendererManager& IGameState::getRenderer(){
	return this->game->getRenderManager();
}



//Gets the Logger
class GameLogger& IGameState::getLogger(){
	return this->game->getLogger();
}



//Gets the Timer
class GameTimer& IGameState::getTimer(){
	return this->game->getTimer();
}








//============================================================================
// Name       		: IGameState.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/30/2020
//============================================================================




#include "IGameState.h"

#include "../Game.h"
#include "../utilities/Dimension.h"
#include "../utilities/Position.h"
#include "../world/TileMap.h"
#include "../utilities/SDLWindowWrapper.h"




IGameState::IGameState(class Game *Game, int StateID)
	: nGameStateID(StateID),
	  game(Game) {}



/*
 * @param	camera The coordinates of the camera
 *
 * Renders the current GameState
 */
void IGameState::render(const Position &camera){

	this->game->Render.setDrawColor(0, 0, 0, 255);
	this->game->Render.clear();

	Dimension windowSize(game->getWindow()->width(), game->getWindow()->height());
	this->customDraw(camera, windowSize);

	//SDL_RenderPresent(game->get_renderer());
	this->game->Render.present();
}



//Gets the Entity Manager
class EntityManager& IGameState::getEntities(){
	return this->game->Entities;
}



//Gets the World Manager
class MapManager& IGameState::getWorlds(){
	return this->game->Map;
}



//Gets the Renderer
class RendererManager& IGameState::getRenderer(){
	return this->game->Render;
}



//Gets the Logger
class GameLogger& IGameState::getLogger(){
	return this->game->Log;
}



//Gets the Timer
class GameTimer& IGameState::getTimer(){
	return this->game->Timer;
}








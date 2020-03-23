//============================================================================
// Name       		: IGameState.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/22/2020
//============================================================================




#include "IGameState.h"

#include "../entities/Game_Dynamic.h"
#include "../Game.h"
#include "../utilities/Dimension.h"
#include "../utilities/Position.h"
#include "../world/TileMap.h"




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

	Dimension windowSize(game->get_windowWidth(), game->get_windowHeight());
	this->customDraw(camera, windowSize);

	//SDL_RenderPresent(game->get_renderer());
	this->game->Render.present();
}








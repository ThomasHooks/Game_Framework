//============================================================================
// Name       		: GameState.cpp
// Author     		: Thomas Hooks
// Last Modified	: 02/24/2020
//============================================================================




#include "GameState.h"

#include "../entities/Game_Dynamic.h"
#include "../Game.h"
#include "../utilities/Dimension.h"
#include "../world/GameMap.h"




void GameState::Draw(){
	//




	//Set the window to black
	SDL_SetRenderDrawColor(game->get_renderer(), 0, 0, 0, 255);
	SDL_RenderClear(game->get_renderer());


	//Calculate the number of visible tiles on the screen
	Dimension tile(this->game->Map.get_tileWidth(), this->game->Map.get_tileHeight());
	int visibleTilesHor = (game->get_windowWidth())/tile.width + 1;
	int visibleTilesVer = (game->get_windowHeight())/tile.height;

	//Calculate the top-left visible tile
	float offsetHor = this->game->get_cameraX()/tile.width - (float)visibleTilesHor/2.0f;
	float offsetVer = this->game->get_cameraY()/tile.height - (float)visibleTilesVer/2.0f;


	//Keep camera inside game boundaries
	Dimension map(this->game->Map.get_width(), this->game->Map.get_height());

	if(offsetHor < 0) offsetHor = 0;

	if(offsetVer < 0) offsetVer = 0;

	if(offsetHor > map.width - visibleTilesHor)
		offsetHor = map.width - visibleTilesHor;

	if(offsetVer > map.height - visibleTilesVer)
		offsetVer = map.height - visibleTilesVer;


	this->customDraw(offsetHor, offsetVer, visibleTilesHor, visibleTilesVer);

	SDL_RenderPresent(game->get_renderer());

	return;
}








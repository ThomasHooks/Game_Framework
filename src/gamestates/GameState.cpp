//============================================================================
// Name       		: GameState.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/08/2020
//============================================================================




#include "GameState.h"

#include "../entities/Game_Dynamic.h"
#include "../Game.h"
#include "../utilities/Dimension.h"
#include "../utilities/Position.h"
#include "../world/GameMap.h"




void GameState::Draw(){
	//




	this->game->Render.setDrawColor(0, 0, 0, 255);
	this->game->Render.clear();


	//Calculate the number of visible tiles on the screen
	Dimension tile(this->game->Map.getTileWidth(), this->game->Map.getTileHeight());
	int visibleTilesHor = (game->get_windowWidth())/tile.width + 1;
	int visibleTilesVer = (game->get_windowHeight())/tile.height;

	//Calculate the top-left visible tile
	float offsetHor = this->game->get_cameraX()/tile.width - (float)visibleTilesHor/2.0f;
	float offsetVer = this->game->get_cameraY()/tile.height - (float)visibleTilesVer/2.0f;


	//Keep camera inside game boundaries
	Dimension map(this->game->Map.getWidth(), this->game->Map.getHeight());

	if(offsetHor < 0) offsetHor = 0;

	if(offsetVer < 0) offsetVer = 0;

	if(offsetHor > map.width - visibleTilesHor)
		offsetHor = map.width - visibleTilesHor;

	if(offsetVer > map.height - visibleTilesVer)
		offsetVer = map.height - visibleTilesVer;


	this->customDraw(offsetHor, offsetVer, visibleTilesHor, visibleTilesVer);

	//SDL_RenderPresent(game->get_renderer());
	this->game->Render.present();
}








//============================================================================
// Name       		: GameState.cpp
// Author     		: Thomas Hooks
// Last Modified	: 02/22/2020
//============================================================================




#include <sstream>
#include <list>
#include <ctime>
#include <math.h>
#include <vector>
#include <memory>

#include <SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include "Game.h"
#include "Game_Dynamic.h"
#include "Game_Map.h"
#include "GameState.h"




void GameState::Draw(){
	/*
	 *
	 */




	//Set the window to black
	SDL_SetRenderDrawColor(game->get_renderer(), 0, 0, 0, 255);
	SDL_RenderClear(game->get_renderer());


	int tileWidth = this->game->Map.get_tileWidth();
	int tileHeight = this->game->Map.get_tileHeight();
	int mapWidth = this->game->Map.get_width();
	int mapHeight = this->game->Map.get_height();

	//Calculate the number of visible tiles on the screen
	int visibleTilesHor = (game->get_windowWidth())/tileWidth + 1;
	int visibleTilesVer = (game->get_windowHeight())/tileHeight;

	//Calculate the top-left visible tile
	float offsetHor = this->game->get_cameraX()/tileWidth - (float)visibleTilesHor/2.0f;
	float offsetVer = this->game->get_cameraY()/tileHeight - (float)visibleTilesVer/2.0f;


	//Keep camera inside game boundaries
	if(offsetHor < 0) offsetHor = 0;

	if(offsetVer < 0) offsetVer = 0;

	if(offsetHor > mapWidth - visibleTilesHor)
		offsetHor = mapWidth - visibleTilesHor;

	if(offsetVer > mapHeight - visibleTilesVer)
		offsetVer = mapHeight - visibleTilesVer;


	this->customDraw(offsetHor, offsetVer, visibleTilesHor, visibleTilesVer);

	SDL_RenderPresent(game->get_renderer());

	return;
}








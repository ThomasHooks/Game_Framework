//============================================================================
// Name       		: GameState.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/21/2020
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


	Dimension windowSize(game->get_windowWidth(), game->get_windowHeight());
	Dimension map(game->Map.getWidth() * game->Map.getTileWidth(), game->Map.getHeight() * game->Map.getTileHeight());


	//Keep camera inside game boundaries
	double cameraX = game->get_cameraX() - windowSize.width/2.0;
	double cameraY = game->get_cameraY() - windowSize.height/2.0;

	if(cameraX < 0) cameraX = 0.0;
	else if(cameraX > map.width - windowSize.width) cameraX = map.width - windowSize.width;

	if(cameraY < 0) cameraY = 0.0;
	else if(cameraY > map.height - windowSize.height) cameraY = map.height - windowSize.height;

	Position camera(cameraX, cameraY);


	this->customDraw(camera, windowSize);

	//SDL_RenderPresent(game->get_renderer());
	this->game->Render.present();
}








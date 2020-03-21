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
#include "../world/TileMap.h"




void GameState::Draw(){
	//




	this->game->Render.setDrawColor(0, 0, 0, 255);
	this->game->Render.clear();


	Dimension windowSize(game->get_windowWidth(), game->get_windowHeight());

	TileMap* world = game->Map.getWorld();
	if(world == nullptr) {
		game->Log.message(Level::FATAL, "Null Pointer exception: Tried to render World, but world stack is empty!", Output::TXT_FILE);
		game->set_gameOver(true);
		return;
	}

	Dimension worldSize(world->width() * world->tileWidth(), world->height() * world->tileHeight());


	//Keep camera inside game boundaries
	double cameraX = game->get_cameraX() - windowSize.width/2.0;
	double cameraY = game->get_cameraY() - windowSize.height/2.0;

	if(cameraX < 0) cameraX = 0.0;
	else if(cameraX > worldSize.width - windowSize.width) cameraX = worldSize.width - windowSize.width;

	if(cameraY < 0) cameraY = 0.0;
	else if(cameraY > worldSize.height - windowSize.height) cameraY = worldSize.height - windowSize.height;

	Position camera(cameraX, cameraY);


	this->customDraw(camera, windowSize);

	//SDL_RenderPresent(game->get_renderer());
	this->game->Render.present();
}








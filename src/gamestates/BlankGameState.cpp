//============================================================================
// Name       		: BlankGameState.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/08/2020
//============================================================================




#include "BlankGameState.h"

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

#include "../entities/Game_Dynamic.h"
#include "../Game.h"
#include "../world/GameMap.h"
#include "../utilities/Dimension.h"
#include "../utilities/Position.h"
#include "../entities/PlayerEntity.h"




BlankGameState::BlankGameState(class Game *Game, int StateID) : GameState(Game, StateID) {

	//----All of this should be removed later----
	//This is still here because it is needed for tile v entity collision this will be changed later
	vMap.emplace_back(GameMap("Test"));
	vMap[0].loadMap("data/map/test.map");

	this->vEntity.emplace_back(std::unique_ptr<class Game_Dynamic>(new cPlayerCharacter(64.0f, 224.0f, 32, 32, 0)));

	this->game->Map.pushMap("tile_test.png","data/map/test.map");

	Dimension tileDim(16, 16);
	this->game->Render.registerTexture("mario", "./data/gfx/Mario.png", tileDim);
	this->game->Render.registerTexture("tile_test.png", "./data/gfx/tile_test.png", tileDim);
	this->game->Render.setScale(2.0f);

	this->game->Entities.registerEntity("mario", new EntityBuilder<PlayerEntity>());
	this->game->Entities.spawn("mario", Position(64.0, 224.0), EnumSide::RIGHT);
	//----All of this should be removed later----

	return;
}



BlankGameState::~BlankGameState() {}



void BlankGameState::GetUserInput(){
	//

	//Begin polling
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
		case SDL_WINDOWEVENT_CLOSE:{
			if(game->get_window()){
				//Window has been closed by user
				game->set_gameOver(true);
			}
		}
		break;
		case SDL_KEYDOWN:{
			switch(event.key.keysym.sym){
			case SDLK_ESCAPE:
				//Escape has been pressed by user
				game->set_gameOver(true);
				break;
			}
		}
		break;
		case SDL_QUIT:
			//SDL has been closed
			game->set_gameOver(true);
			break;
		}
	}

	//----All of this should be removed later----
	const Uint8*state = SDL_GetKeyboardState(NULL);
	if(state[SDL_SCANCODE_SPACE]){
		vEntity[0]->fdY = -128.0f;
	}

	if(state[SDL_SCANCODE_A]){
		vEntity[0]->fdX = -192.0f;
	}
	else if(state[SDL_SCANCODE_D]){
		vEntity[0]->fdX = 192.0f;
	}
	//----All of this should be removed later----

	return;
}



void BlankGameState::Process(){
	//

	//----All of this should be removed later----
	this->game->set_cameraX(vEntity[0]->fX);
	this->game->set_cameraY(vEntity[0]->fY);

	//Keep player x position inside the map
	if(vEntity[0]->fX < 0.0f) vEntity[0]->fX = 0.0f;
	else if((vEntity[0]->fX + vEntity[0]->nWidth*2) > (vMap[0].mapWidth * vMap[0].tileWidth)){
		vEntity[0]->fX = vMap[0].mapWidth * vMap[0].tileWidth - vEntity[0]->nWidth*2;
	}

	//Keep player Y position inside the map
	if(vEntity[0]->fY < 0.0f) vEntity[0]->fY = 0.0f;
	else if((vEntity[0]->fY + vEntity[0]->nHeight) > vMap[0].mapHeight * vMap[0].tileHeight)
		vEntity[0]->fY = vMap[0].mapHeight * vMap[0].tileHeight - vEntity[0]->nHeight;

	vEntity[0]->Update(game->Timer.get_deltaTime());

	EntityMapCollisionRect(0, 0);
	//----All of this should be removed later----

	return;
}



void BlankGameState::customDraw(float offsetX, float offsetY, int visibleTilesHor, int visibleTilesVer){
	/*
	 *
	 */


	//----All of this should be removed later----
	this->game->Map.draw(Position(offsetX, offsetY), Dimension(visibleTilesHor, visibleTilesVer), this->game->Render);

	this->game->Render.drawSprite("mario", Position(vEntity[0]->fX, vEntity[0]->fY), Position(offsetX, offsetY), Dimension(0, 0), false);

	Position camera(offsetX, offsetY);
	Dimension window(this->game->get_windowWidth(), this->game->get_windowHeight());
	this->game->Entities.drawAll(camera, window, this->game->Render);
	//----All of this should be removed later----
}



void BlankGameState::ChangeState(int StateFlag, Game *Game) {
	//

	return;
}



void BlankGameState::EntityMapCollisionRect(int EntityIndex, int MapIndex){
	/*
	 * *brief*	This method checks if an entity has collided with any of the
	 * 			tiles around them in a 3x3 grid
	 *
	 * 	param:	EntityIndex specifies which entity in the entity stack is
	 * 			to be tested
	 *
	 * 	param:	MapIndex specifies which map in the map stack the tiles are
	 * 			being tested against
	 *
	 *
	 * */


	//Set the entity's bounding box
	float RectA_X1 = vEntity[EntityIndex]->fX;
	float RectA_X2 = vEntity[EntityIndex]->fX + vEntity[EntityIndex]->nWidth -8;
	float RectA_Y1 = vEntity[EntityIndex]->fY;
	float RectA_Y2 = vEntity[EntityIndex]->fY + vEntity[EntityIndex]->nHeight;
	float RectA_XCenter = vEntity[EntityIndex]->fX + vEntity[EntityIndex]->nWidth/2;
	float RectA_YCenter = vEntity[EntityIndex]->fY + vEntity[EntityIndex]->nHeight/2;

	//Set bottom left tile
	int MaxX = 2;
	int MaxY = 2;

	//Set top right tile
	int MinX = -1;
	int MinY = -1;

	//This puts the entity into the maps tile unit coordinate
	int tX = vEntity[EntityIndex]->fX / vMap[MapIndex].tileWidth;
	int tY = vEntity[EntityIndex]->fY / vMap[MapIndex].tileHeight;

	//Check if the entity collides with any of the tiles around it
	for(int y = MinY; y < MaxY; y++){
		for(int x = MinX; x < MaxX; x++){
			//Check if coordinate is valid
			//Check x coordinate
			if((x + tX) < 0) x = 0;
			else if((x + tX) > (vMap[MapIndex].mapWidth)) MaxX--;
			//Check y coordinate
			if((y + tY) < 0) y = 0;
			else if((y + tY) > (vMap[MapIndex].mapHeight)) MaxY--;

			//Check for collision if the tile is solid
			if(vMap[MapIndex].isTileSolid(x + tX, y + tY)){
				//Set the Tiles bounding Box
				float RectB_X1 = (x + tX) * vMap[MapIndex].tileWidth;
				float RectB_X2 = (x + tX) * vMap[MapIndex].tileWidth + vMap[MapIndex].tileWidth;
				float RectB_Y1 = (y + tY) * vMap[MapIndex].tileHeight;
				float RectB_Y2 = (y + tY) * vMap[MapIndex].tileHeight + vMap[MapIndex].tileHeight;
				float RectB_XCenter = (x + tX) * vMap[MapIndex].tileWidth + vMap[MapIndex].tileWidth/2;
				float RectB_YCenter = (y + tY) * vMap[MapIndex].tileHeight + vMap[MapIndex].tileHeight/2;

				//Check if the entity collides with the tile
				if(RectA_X1 < RectB_X2 && RectA_X2 > RectB_X1 &&
				   RectA_Y1 < RectB_Y2 && RectA_Y2 > RectB_Y1){
					//Entity has collided with the tile
					//Which axis is the overlap greatest?
					if(abs(RectA_YCenter - RectB_YCenter) > abs(RectA_XCenter - RectB_XCenter)){
						//The Y axis overlap is greater
						//Is the entity above the tile?
						if(RectA_YCenter < RectB_YCenter){
							//Entity is above the tile
							//Check if there is a solid tile above the ledge
							if(!vMap[MapIndex].isTileSolid(x + tX, y + tY - 1)){
								//There isn't a solid tile
								vEntity[EntityIndex]->fY = RectB_Y1 - vEntity[EntityIndex]->nHeight;
								vEntity[EntityIndex]->fdY = 0.0f;
								vEntity[EntityIndex]->fd2Y = 0.0f;
							}
						}
						else{
							//Entity is below the tile
							//Check if there is a solid tile below the ledge
							if(!vMap[MapIndex].isTileSolid(x + tX, y + tY + 1)){
								//There isn't a solid tile
								vEntity[EntityIndex]->fY = RectB_Y2;
								vEntity[EntityIndex]->fdY = 0.0f;
								vEntity[EntityIndex]->fd2Y = 0.0f;
							}
						}
					}

					else{
						//The X axis overlap is greater
						//Is the entity left of the tile?
						if(RectA_XCenter <= RectB_XCenter){
							//Entity is left of the tile
							//Check if there is a solid tile to the left of the ledge
							if(!vMap[MapIndex].isTileSolid(x + tX - 1, y + tY)){
								//There isn't a solid tile
								vEntity[EntityIndex]->fX = RectB_X1 - vEntity[EntityIndex]->nWidth +8; // made a change +8
								vEntity[EntityIndex]->fdX = 0.0f;
								vEntity[EntityIndex]->fd2X = 0.0f;
							}
						}
						else{
							//Entity is right of the tile
							//Check if there is a solid tile to the right of the ledge
							if(!vMap[MapIndex].isTileSolid(x + tX + 1, y + tY)){
								//There isn't a solid tile
								vEntity[EntityIndex]->fX = RectB_X2;
								vEntity[EntityIndex]->fdX = 0.0f;
								vEntity[EntityIndex]->fd2X = 0.0f;
							}
						}
					}
				}
				//Else there was no collision
			}
		}
	}

	return;
}








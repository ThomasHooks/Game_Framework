//============================================================================
// Name       		: BlankGameState.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/31/2020
//============================================================================




#include <SDL.h>

#include "BlankGameState.h"
#include "../Game.h"
#include "../managers/RendererManager.h"
#include "../managers/EntityManager.h"
#include "../managers/MapManager.h"
#include "../entities/PlayerEntity.h"
#include "../world/TileMap.h"
#include "../utilities/Dimension.h"
#include "../utilities/Position.h"
#include "../utilities/SDLWindowWrapper.h"
#include "../utilities/GameCamera.h"
#include "../utilities/GameTimer.h"




BlankGameState::BlankGameState(class Game *Game, int StateID)
	: IGameState(Game, StateID) {

	//----All of this should be removed later----
	getWorlds().pushMap("tiletest","data/map/test.map");

	Dimension tileDim(16, 16);
	getRenderer().registerTexture("mario", "./data/gfx/Mario.png", tileDim);
	getRenderer().registerTexture("tiletest", "./data/gfx/tile_test.png", tileDim);
	getRenderer().setScale(2.0f);

	getEntities().registerEntity("mario", new EntityBuilder<PlayerEntity>());
	this->player = getEntities().spawn("mario", Position(128.0, 224.0), EnumSide::RIGHT);
	this->game->getCamera()->trackEntity(player);
	//----All of this should be removed later----
}



BlankGameState::~BlankGameState() {}



/*
 *
 */
void BlankGameState::onInputEvent(){

	//Begin polling
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
		case SDL_WINDOWEVENT_CLOSE:{
			if(game->getWindow()->isOpen()){
				//Window has been closed by user
				game->markOver();
			}
		}
		break;
		case SDL_KEYDOWN:{
			switch(event.key.keysym.sym){
			case SDLK_ESCAPE:
				//Escape has been pressed by user
				game->markOver();
				break;
			}
		}
		break;
		case SDL_QUIT:
			//SDL has been closed
			game->markOver();
			break;
		}
	}

	//----All of this should be removed later----
	const Uint8*state = SDL_GetKeyboardState(NULL);
	if(state[SDL_SCANCODE_W]) {
		player->updateVel(Position(0.0, -576.0), 0.93f, getTimer().get_deltaTime());
	}
	else if(state[SDL_SCANCODE_S]) {
		player->updateVel(Position(0.0, 576.0), 0.93f, getTimer().get_deltaTime());
	}

	if(state[SDL_SCANCODE_A]) {
		player->updateVel(Position(-576.0, 0.0), 0.93f, getTimer().get_deltaTime());
	}
	else if(state[SDL_SCANCODE_D]) {
		player->updateVel(Position(576.0, 0.0), 0.93f, getTimer().get_deltaTime());
	}
	//----All of this should be removed later----
}



/*
 *
 */
void BlankGameState::tick(const Position &cameraPos){
	//----All of this should be removed later----
	TileMap *world = getWorlds().getWorld();
	Dimension windowSize(game->getWindow()->width(), game->getWindow()->height());
	this->getEntities().tickAll(cameraPos, windowSize, *world, getTimer().get_deltaTime());
	//----All of this should be removed later----
}



/*
 *
 */
void BlankGameState::customDraw(const Position &cameraPos, const Dimension &windowSize){
	//----All of this should be removed later----
	getWorlds().draw(cameraPos, windowSize, getRenderer());
	getEntities().drawAll(cameraPos, windowSize, getRenderer(), true);
	//----All of this should be removed later----
}



/*
 *
 */
void BlankGameState::ChangeState(int StateFlag, Game *Game){}








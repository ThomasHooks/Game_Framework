//============================================================================
// Name       		: BlankGameState.cpp
// Author     		: Thomas Hooks
// Last Modified	: 04/05/2020
//============================================================================




#include <SDL.h>

#include "BlankGameState.h"
#include "../Game.h"
#include "../managers/RendererManager.h"
#include "../managers/EntityManager.h"
#include "../managers/MapManager.h"
#include "../managers/AudioManager.h"
#include "../entities/PlayerEntity.h"
#include "../world/TileMap.h"
#include "../utilities/GameCamera.h"
#include "../utilities/GameTimer.h"
#include "../utilities/physics/Dimension.h"
#include "../utilities/physics/Position.h"
#include "../utilities/wrappers/SDLWindowWrapper.h"




BlankGameState::BlankGameState(class Game *Game, int StateID)
	: IGameState(Game, StateID) {

	//----All of this should be removed later----
	getWorlds().pushMap("tiletest","data/map/test.map");

	Dimension tileDim(16, 16);
	getRenderer().registerTexture("mario", "./data/gfx/Mario.png", tileDim);
	getRenderer().registerTexture("tiletest", "./data/gfx/tile_test.png", tileDim);
	getRenderer().setScale(2.0f);

	getMixer().registerSample("hit01", "./data/sfx/hit01.wav");
	getMixer().setSampleVolume("hit01", 32);

	getEntities().registerEntity("mario", new EntityBuilder<PlayerEntity>());
	this->player = getEntities().spawn("mario", Position(128.0, 224.0), EnumSide::RIGHT);
	this->game->getCamera()->trackEntity(player);
	//----All of this should be removed later----
}



BlankGameState::~BlankGameState() {}



/*
 *
 */
void BlankGameState::onInputEvent() {

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

			case SDLK_SPACE:
				getMixer().playSample("hit01", 0);
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
		player->updateVel(Position(0.0, -576.0), 0.93f, getTimer().getDelta());
	}
	else if(state[SDL_SCANCODE_S]) {
		player->updateVel(Position(0.0, 576.0), 0.93f, getTimer().getDelta());
	}

	if(state[SDL_SCANCODE_A]) {
		player->updateVel(Position(-288.0, 0.0), 0.93f, getTimer().getDelta());
	}
	else if(state[SDL_SCANCODE_D]) {
		player->updateVel(Position(288.0, 0.0), 0.93f, getTimer().getDelta());
	}
	//----All of this should be removed later----
}



/*
 * @param	camera Reference to the Game's Camera
 *
 * @param	worldIn The current World
 *
 * @param	deltaTime Amount of time that has elapsed since the last tick
 *
 * Causes the current Game State to update
 */
void BlankGameState::tick(const GameCamera &camera, TileMap &worldIn, float deltaTime) {

	//----All of this should be removed later----
	Dimension windowSize(camera.width(), camera.height());
	this->getEntities().tickAll(camera.getPos(), windowSize, worldIn, deltaTime);
	//----All of this should be removed later----
}



/*
 * @param	camera Reference to the Game's Camera
 *
 * Renders the current GameState
 */
void BlankGameState::render(const GameCamera &camera) {

	getRenderer().setDrawColor(0, 0, 0, 255);
	getRenderer().clear();

	//----All of this should be removed later----
	Dimension windowSize(camera.width(), camera.height());
	getWorlds().draw(camera.getPos(), windowSize, getRenderer());
	getEntities().drawAll(camera.getPos(), windowSize, getRenderer(), true);
	//----All of this should be removed later----

	getRenderer().present();
}



/*
 *
 */
void BlankGameState::ChangeState(int StateFlag, Game *Game) {}








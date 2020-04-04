//============================================================================
// Name       		: IGameState.cpp
// Author     		: Thomas Hooks
// Last Modified	: 04/04/2020
//============================================================================




#include "IGameState.h"
#include "../Game.h"
#include "../managers/RendererManager.h"
#include "../managers/EntityManager.h"
#include "../managers/MapManager.h"
#include "../world/TileMap.h"
#include "../utilities/Dimension.h"
#include "../utilities/Position.h"
#include "../utilities/GameLogger.h"
#include "../utilities/SDLWindowWrapper.h"
#include "../utilities/GameCamera.h"
#include "../utilities/GameTimer.h"




IGameState::IGameState(class Game *Game, int StateID)
	: nGameStateID(StateID),
	  game(Game) {}



//Gets the Entity Manager
class EntityManager& IGameState::getEntities() {
	return this->game->getEntityManager();
}



//Gets the World Manager
class MapManager& IGameState::getWorlds() {
	return this->game->getWorldManager();
}



//Gets the Renderer
class RendererManager& IGameState::getRenderer() {
	return this->game->getRenderManager();
}



//Gets the Logger
class GameLogger& IGameState::getLogger() {
	return this->game->getLogger();
}



//Gets the Timer
class GameTimer& IGameState::getTimer() {
	return this->game->getTimer();
}








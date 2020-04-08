//============================================================================
// Name       		: IGameState.cpp
// Author     		: Thomas Hooks
// Last Modified	: 04/06/2020
//============================================================================




#include "IGameState.h"
#include "../Game.h"
#include "../managers/RendererManager.h"
#include "../managers/EntityManager.h"
#include "../managers/MapManager.h"
#include "../managers/AudioManager.h"
#include "../world/TileMap.h"
#include "../utilities/GameLogger.h"
#include "../utilities/GameCamera.h"
#include "../utilities/GameTimer.h"
#include "../utilities/physics/Dimension.h"
#include "../utilities/physics/Position.h"
#include "../utilities/wrappers/SDLWindowWrapper.h"




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



//Gets the Audio Manager
class AudioManager& IGameState::getMixer() {
	return this->game->getMixer();
}



//Gets the Logger
class GameLogger& IGameState::getLogger() {
	return this->game->getLogger();
}



//Gets the Timer
class GameTimer& IGameState::getTimer() {
	return this->game->getTimer();
}








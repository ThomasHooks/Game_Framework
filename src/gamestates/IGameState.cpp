//============================================================================
// Name       		: IGameState.cpp
// Author     		: Thomas Hooks
// Last Modified	: 04/06/2020
//============================================================================




#include "IGameState.h"

#include "../audiomixer/AudioMixer.h"
#include "../entities/EntityManager.h"
#include "../Game.h"
#include "../renderer/Renderer.h"
#include "../world/TileMap.h"
#include "../utilities/GameLogger.h"
#include "../utilities/GameCamera.h"
#include "../utilities/GameTimer.h"
#include "../utilities/physics/Dimension.h"
#include "../utilities/physics/Position.h"
#include "../utilities/wrappers/SDLWindowWrapper.h"
#include "../world/WorldStack.h"




IGameState::IGameState(class Game *Game, int StateID)
	: nGameStateID(StateID),
	  game(Game) {}



//Gets the Entity Manager
class EntityManager& IGameState::getEntities() {
	return this->game->getEntityManager();
}



//Gets the World Manager
class WorldStack& IGameState::getWorlds() {
	return this->game->getWorldStack();
}



//Gets the Renderer
class Renderer& IGameState::getRenderer() {
	return this->game->getRenderManager();
}



//Gets the Audio Manager
class AudioMixer& IGameState::getMixer() {
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








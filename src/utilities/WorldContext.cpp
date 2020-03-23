//============================================================================
// Name       		: WorldContext.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/22/2020
//============================================================================




#include "WorldContext.h"
#include "../managers/EntityManager.h"
#include "../entities/PlayerEntity.h"
#include "../world/TileMap.h"
#include "GameTimer.h"




WorldContext::WorldContext(TileMap *worldIn,
		EntityManager *entites_ptr,
		IEntity *playerIn,
		GameTimer* timerIn)
	: world(worldIn),
	  entities(entites_ptr),
	  player(playerIn),
	  timer(timerIn) {}



WorldContext::~WorldContext() {}



/*
 * @return	The current World
 *
 * Gets the current World
 */
TileMap& WorldContext::getWorld(){
	return *this->world;
}



/*
 * @return	A reference to the Entity Manager
 *
 * Gets the Entity Manager
 */
EntityManager& WorldContext::getEntities(){
	return *this->entities;
}



/*
 * @return	A reference to the Player
 *
 * Gets the Player
 */
IEntity& WorldContext::getPlayer(){
	return *this->player;
}



/*
 * @return	The amount of time since the last tick
 *
 * Gets the amount of time since the last tick
 */
float WorldContext::getDeltaTime(){
	return this->timer->get_deltaTime();
}








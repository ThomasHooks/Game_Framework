//============================================================================
// Name       		: WorldContext.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/19/2020
//============================================================================




#include "WorldContext.h"
#include "../world/GameMap.h"
#include "../managers/EntityManager.h"
#include "../entities/PlayerEntity.h"




WorldContext::WorldContext(GameMap *worldIn,
		EntityManager *entites_ptr,
		PlayerEntity *playerIn,
		float deltaTimeIn)
	: world(worldIn),
	  entities(entites_ptr),
	  player(playerIn),
	  deltaTime(deltaTimeIn) {}



WorldContext::~WorldContext() {}


//============================================================================
// Name       		: WorldContext.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/19/2020
//============================================================================




#include "WorldContext.h"
#include "../managers/EntityManager.h"
#include "../entities/PlayerEntity.h"
#include "../world/TileMap.h"




WorldContext::WorldContext(TileMap *worldIn,
		EntityManager *entites_ptr,
		PlayerEntity *playerIn,
		float deltaTimeIn)
	: world(worldIn),
	  entities(entites_ptr),
	  player(playerIn),
	  deltaTime(deltaTimeIn) {}



WorldContext::~WorldContext() {}


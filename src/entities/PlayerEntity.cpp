//============================================================================
// Name       		: PlayerEntity.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/19/2020
//============================================================================




#include "PlayerEntity.h"
#include "capabilities/HealthCapability.h"
#include "../world/TileMap.h"




PlayerEntity::PlayerEntity() : IEntity() {

	this->setRegistryTag("mario");
	this->setEntityType(EnumEntityType::PLAYER);
	this->setAabb(0.0, 0.0, 11.0, 15.0);
	this->addCapability<HealthCapability>("health", 5, 5);
}



PlayerEntity::~PlayerEntity() {}



/*
 * @param	posIn Coordinates the Entity is to be spawned
 *
 * @param	facingIn The direction the Entity is to be facing
 *
 * This method is called just as an Entity is spawned
 */
void PlayerEntity::onSpwan(){}



//This method is called right before an Entity is despawned
void PlayerEntity::onDespwan(){}



/*
 * @param	deltaTime The amount of time since the last tick
 *
 * This method is called each tick
 */
void PlayerEntity::tick(const TileMap &world, float deltaTime){

	this->updatePos(0.1f, deltaTime);
}



/*
 * @param	other The Entity that has been collided with
 *
 * @param	side The side of the other Entity that has been collided with
 *
 * This method is called when the Entity collides with another Entity
 */
void PlayerEntity::onEntityColision(IEntity &other, EnumSide side){}



/*
 * @param	tile The Tile the Entity collided with
 *
 * @param	side The side of the Tile that the Entity collided with
 *
 * This method is called when the Entity collides with a Tile
 */
void PlayerEntity::onTileColision(ITile &tileIn, EnumSide side){}








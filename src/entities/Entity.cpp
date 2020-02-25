//============================================================================
// Name       		: Entity.cpp
// Author     		: Thomas Hooks
// Last Modified	: 02/25/2020
//============================================================================




#include "Entity.h"




Entity::Entity(std::string tagIn, Position posIn, Dimension dimIn)
	: tag(tagIn),
	  tilePosition(posIn, dimIn),
	  velocity(),
	  acceleration(),
	  health(1),
	  maxHealth(1),
	  behavior(EnumBehavior::PASSIVE) {}



Entity::~Entity() {}



Entity::Entity(const Entity &other)
	: tag(other.tag),
	  tilePosition(other.tilePosition),
	  velocity(other.velocity),
	  acceleration(other.acceleration),
	  health(other.health),
	  maxHealth(other.maxHealth),
	  behavior(other.behavior) {}



Entity::Entity(Entity &&other)
	: tag(other.tag),
	  tilePosition(other.tilePosition),
	  velocity(other.velocity),
	  acceleration(other.acceleration),
	  health(other.health),
	  maxHealth(other.maxHealth),
	  behavior(other.behavior) {

	other.tag = nullptr;
	other.health = 0;
	other.maxHealth = 0;
}



TilePosition& Entity::get_position(){
	return tilePosition;
}



bool Entity::isFriendly(void){
	return this->behavior == EnumBehavior::PASSIVE ? true : false;
}



bool Entity::isNeutral(void){
	return this->behavior == EnumBehavior::NEUTRAL ? true : false;
}



bool Entity::isAggressive(void){
	return this->behavior == EnumBehavior::AGGRESSIVE ? true : false;
}








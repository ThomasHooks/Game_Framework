//============================================================================
// Name       		: IEntity.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/14/2020
//============================================================================




#include "IEntity.hpp"
//#include "states/IEntityState.h"




IEntity::IEntity()
	: tag("null"),
	  active(true),
	  solid(true),
	  pos(),
	  lastPos(),
	  vel(),
	  sprite(),
	  type(EnumEntityType::PASSIVE),
	  facing(EnumSide::RIGHT) {}



IEntity::~IEntity() {}



const std::string& IEntity::getRegistryTag() const {
	return this->tag;
}



bool IEntity::isActive() const {
	return this->active;
}



void IEntity::markInactive() {
	this->active = false;
}



bool IEntity::canCollide() const {
	return this->solid;
}



EnumEntityType IEntity::getType() const {
	return this->type;
}



bool IEntity::isPassive(void)const {
	return this->type == EnumEntityType::PASSIVE ? true : false;
}



bool IEntity::isNeutral(void) const {
	return this->type == EnumEntityType::NEUTRAL ? true : false;
}



bool IEntity::isAggressive(void) const {
	return this->type == EnumEntityType::AGGRESSIVE ? true : false;
}



bool IEntity::isPlayer(void) const {
	return this->type == EnumEntityType::PLAYER ? true : false;
}



const Dimension& IEntity::getSprite() const {
	return this->sprite;
}



EnumEntityType IEntity::directionFacing() const {
	return this->type;
}



const Position& IEntity::getPos() const {
	return this->pos;
}



bool IEntity::isMoving(void) const {
	return this->vel + 0.5 > 0 ? true : false;
}



bool IEntity::hasState(const std::string &stateTag){

	for(auto itr = this->states.begin(); itr != this->states.end(); ++itr){
		if(itr->get()->getTag() == stateTag) return true;
	}
	return false;
}


void IEntity::setRegistryTag(const std::string &tagIn){
	this->tag = tagIn;
}



void IEntity::setSprite(const Dimension &spriteIn){
	this->sprite.width = spriteIn.width;
	this->sprite.height = spriteIn.height;
}



void IEntity::updateVel(const Position &accel, float frict, float deltaTime){

	this->vel.move(this->vel + accel * deltaTime);

	//Add dynamic friction to the Entity to slow it down
	if(frict > 1.0f) frict = 1.0f;
	else if(frict < 0.0f) frict = 0.0f;
	this->vel.move(this->vel - this->vel * deltaTime * frict);
}



void IEntity::updatePos(float deltaTime){

	this->lastPos.move(this->pos - this->lastPos);

	this->pos.move(this->pos + this->vel * deltaTime);
}



void IEntity::teleport(const Position &pos){

}








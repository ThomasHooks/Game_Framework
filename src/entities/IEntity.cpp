//============================================================================
// Name       		: IEntity.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/16/2020
//============================================================================




#include "IEntity.hpp"




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



//Gets the Entity's registration tag
const std::string& IEntity::getRegistryTag() const {
	return this->tag;
}



//Checks if the Entity is active
bool IEntity::isActive() const {
	return this->active;
}



//Marks the Entity to be despawned
void IEntity::markInactive() {
	this->active = false;
}



//Checks if the Entity has collision
bool IEntity::canCollide() const {
	return this->solid;
}



//Gets the Entity's type
EnumEntityType IEntity::getType() const {
	return this->type;
}



//Checks if the Entity is passive
bool IEntity::isPassive(void)const {
	return this->type == EnumEntityType::PASSIVE ? true : false;
}



//Checks if the Entity is neutral
bool IEntity::isNeutral(void) const {
	return this->type == EnumEntityType::NEUTRAL ? true : false;
}



//Checks if the Entity is aggressive
bool IEntity::isAggressive(void) const {
	return this->type == EnumEntityType::AGGRESSIVE ? true : false;
}



//Checks if the Entity is a player
bool IEntity::isPlayer(void) const {
	return this->type == EnumEntityType::PLAYER ? true : false;
}



//Gets the sprite's location in the sprite sheet
const Dimension& IEntity::getSprite() const {
	return this->sprite;
}



//Gets the direction that the Entity is facing
EnumEntityType IEntity::directionFacing() const {
	return this->type;
}



//Gets the Entity's position
const Position& IEntity::getPos() const {
	return this->pos;
}



/*
 * @param	pos The new position of the Entity
 *
 * Moves the Entity to a new position
 */
void IEntity::teleport(const Position &posIn){
	double xPos = posIn.xPos() - this->getPos().xPos();
	double yPos = posIn.yPos() - this->getPos().yPos();
	this->pos.move(xPos, yPos);
}



//Checks if the Entity is moving
bool IEntity::isMoving(void) const {
	return this->vel + 0.5 > 0 ? true : false;
}



/*
 * @param	FacingIn The new direction that the Entity is facing
 *
 * Changes the direction that the Entity is facing
 */
void IEntity::setDirectionFacing(EnumSide facingIn){
	this->facing = facingIn;
}



/*
 * @param	stateTag The state's tag
 *
 * @return	True if the Entity has the state
 *
 * Checks if the Entity has the given state
 */
bool IEntity::hasState(const std::string &stateTag){
	return this->states.count(stateTag) > 0 ? true : false;
}



//Used to set the Entity's registration tag
void IEntity::setRegistryTag(const std::string &tagIn){
	this->tag = tagIn;
}



//Used to update an Entity's sprite
void IEntity::setSprite(const Dimension &spriteIn){
	this->sprite.width = spriteIn.width;
	this->sprite.height = spriteIn.height;
}



/*
 * @param	typeIn The Entity's type
 *
 * Used to set the Entity's type
 */
void IEntity::setEntityType(EnumEntityType typeIn){
	this->type = typeIn;
}



/*
 * @param	accel The acceleration of the Entity
 *
 * @param	frict The friction of the Entity
 *
 * @param	deltaTime The amount of time since the last tick
 *
 * Updates the velocity of the Entity
 */
void IEntity::updateVel(const Position &accel, float frict, float deltaTime){

	this->vel.move(this->vel + accel * deltaTime);

	//Add dynamic friction to the Entity to slow it down
	if(frict > 1.0f) frict = 1.0f;
	else if(frict < 0.0f) frict = 0.0f;
	this->vel.move(this->vel - this->vel * deltaTime * frict);
}



/*
 * @param	deltaTime The amount of time since the last tick
 *
 * Updates the position of the Entity
 */
void IEntity::updatePos(float deltaTime){

	this->lastPos.move(this->pos - this->lastPos);

	this->pos.move(this->pos + this->vel * deltaTime);
}








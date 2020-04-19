//============================================================================
// Name       		: IEntity.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/23/2020
//============================================================================




#include "IEntity.hpp"




IEntity::IEntity()
	: tag("null"),
	  entityID(0),
	  active(true),
	  solid(true),
	  pos(),
	  lastPos(),
	  vel(),
	  hitBox(),
	  sprite(),
	  type(EnumEntityType::PASSIVE),
	  facing(EnumSide::RIGHT) {}



IEntity::~IEntity() {}



/*
 * @param	posIn Coordinates the Entity is to be spawned
 *
 * @param	facingIn The direction the Entity is to be facing
 *
 * This method is called just as an Entity is spawned
 */
void IEntity::spwan(const Position &posIn, EnumSide facingIn, unsigned int entityIDIn){
	this->teleport(posIn);
	//this->hitBox.offset(this->pos);
	this->setDirectionFacing(facingIn);
	this->entityID = entityIDIn;
	this->onSpwan();
}



//Gets the Entity's registration tag
const std::string& IEntity::getRegistryTag() const {
	return this->tag;
}



//Gets the Entity's identification
unsigned int IEntity::getID() const{
	return this->entityID;
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
bool IEntity::isPassive()const {
	return this->type == EnumEntityType::PASSIVE;
}



//Checks if the Entity is neutral
bool IEntity::isNeutral() const {
	return this->type == EnumEntityType::NEUTRAL;
}



//Checks if the Entity is aggressive
bool IEntity::isAggressive() const {
	return this->type == EnumEntityType::AGGRESSIVE;
}



//Checks if the Entity is a player
bool IEntity::isPlayer() const {
	return this->type == EnumEntityType::PLAYER;
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



//Gets the Entity's axis aligned bounding box
const AABB& IEntity::getAabb() const {
	return this->hitBox;
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
	this->hitBox.offset(xPos, yPos);
}



//Checks if the Entity is moving
bool IEntity::isMoving() const {
	return this->vel + 0.5 > 0;
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
bool IEntity::hasCapability(const std::string &stateTag){
	return this->states.count(stateTag) > 0;
}



/*
 * @param	accel The acceleration of the Entity
 *
 * @param	frict The friction of the Entity ranging from 0.0 - 1.0
 *
 * @param	deltaTime The amount of time since the last tick
 *
 * Updates the velocity of the Entity
 */
void IEntity::updateVel(const Position &accel, float frict, float deltaTime){
	
	float deltaFrict = std::abs(frict);
	if(deltaFrict < 0.0f) deltaFrict = 0.0f;
	else if(deltaFrict > 1.0f) deltaFrict = 1.0f;
	this->vel.move(this->vel + accel * deltaTime * deltaFrict);
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
 * @param	x1, y1 The coordinates of the top-left point
 *
 * @param	x2, y2 The coordinates of the bottom-right point
 *
 * Used to set the Entity's axis aligned bounding box
 *
 * The positions given should be relative to the tile
 * and not the Global coordinates.
 * ie. a tile that is 32x32 would be (0.0, 0.0, 32.0, 32.0)
 */
void IEntity::setAabb(double x1, double y1, double x2, double y2){
	this->hitBox.offset(std::abs(x1), std::abs(y1));
	this->hitBox.modify(EnumSide::RIGHT, std::abs(x2));
	this->hitBox.modify(EnumSide::DOWN, std::abs(y2));
}



/*
 * @param	deltaTime The amount of time since the last tick
 *
 * @param	frict The amount of breaking friction ranging from 0.0 - 1.0
 *
 * Updates the position of the Entity
 */
void IEntity::updatePos(float frict, float deltaTime){

	float delta = std::abs(frict);
	if(delta < 0.0f) delta = 0.0f;
	else if(delta > 1.0f) delta = 1.0f;

	this->lastPos.move(this->pos);
	this->pos.move(this->pos + this->vel * deltaTime);

	//Move AABB with this Entity
	this->hitBox.offset(this->pos - this->lastPos);//this->vel * deltaTime
	//Add dynamic friction to the Entity to slow it down
	this->vel.move(this->vel * delta);
}



//Gets the Entity's last position
Position& IEntity::getLastPos(){
	return this->lastPos;
}



//Gets the Entity's velocity
Position& IEntity::getVel(){
	return this->vel;
}








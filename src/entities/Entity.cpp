//============================================================================
// Name       		: Entity.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/02/2020
//============================================================================




#include "Entity.h"

#include <algorithm>

#include <SDL.h>
#include "SDL_image.h"




Entity::Entity()
	: tag("null"),
	  tilePosition(),
	  lastPosition(),
	  velocity(),
	  spriteSize(16, 16),
	  spriteLocation(),
	  livingEntity(false),
	  health(0),
	  maxHealth(0),
	  solid(true),
	  flying(false),
	  onGround(true),
	  hitBox(0.0, 0.0, 0.0, 0.0),
	  behavior(EnumBehavior::PASSIVE) {}



Entity::~Entity() {}



Entity::Entity(const Entity &other)
	: tag(other.tag),
	  tilePosition(other.tilePosition),
	  lastPosition(other.lastPosition),
	  velocity(other.velocity),
	  spriteSize(other.spriteSize),
	  spriteLocation(other.spriteLocation.width, other.spriteLocation.height),
	  livingEntity(other.livingEntity),
	  health(other.health),
	  maxHealth(other.maxHealth),
	  solid(other.solid),
	  flying(other.flying),
	  onGround(other.onGround),
	  hitBox(other.hitBox),
	  behavior(other.behavior) {}



Entity::Entity(Entity &&other)
	: tag(other.tag),
	  tilePosition(other.tilePosition),
	  lastPosition(other.lastPosition),
	  velocity(other.velocity),
	  spriteSize(other.spriteSize),
	  spriteLocation(other.spriteLocation.width, other.spriteLocation.height),
	  livingEntity(other.livingEntity),
	  health(other.health),
	  maxHealth(other.maxHealth),
	  solid(other.solid),
	  flying(other.flying),
	  onGround(other.onGround),
	  hitBox(other.hitBox),
	  behavior(other.behavior) {

	other.tag = nullptr;
	other.health = 0;
	other.maxHealth = 0;
}



void Entity::draw(struct SDL_Renderer *rendererIn,
			  	  struct SDL_Texture *texture,
				  const Position offset){

	//Set the draw color to white
	SDL_SetRenderDrawColor(rendererIn, 255, 255, 255, 255);

	//Select the right sprite from the sprite sheet
	SDL_Rect spriteRect = {this->spriteLocation.width * this->spriteSize.width,
						   this->spriteLocation.height * this->spriteSize.height,
						   this->spriteSize.width,
						   this->spriteSize.height};

	//calculate the entities size and location in the world
	int xPos = this->tilePosition.xPosN() - offset.xPosN() * this->spriteSize.width;
	int yPos = this->tilePosition.yPosN() - offset.yPosN() * this->spriteSize.height;
	SDL_Rect entityRect = {xPos, yPos, this->spriteSize.width, this->spriteSize.height};

	//Draw the Character to the screen
	SDL_RenderCopyEx(rendererIn, texture, &spriteRect, &entityRect, 0, NULL, SDL_FLIP_NONE);

	return;
}



const Dimension& Entity::getSpriteSize(void) const {
	return this->spriteSize;
}



const Dimension& Entity::getAnimation(void) const {
	return this->spriteLocation;
}



const std::string& Entity::getTag(void) const {
	return this->tag;
}



void Entity::teleport(double x, double y){
	/*
	 * @param	x		the X coordinate of the destination
	 *
	 * @param	y		the Y coordinate of the destination
	 *
	 * Teleports the entity from its current location to the given one
	 */




	double xPos = this->getPosition().xPos();
	double yPos = this->getPosition().yPos();
	this->getPosition().move(x - xPos, y - yPos);
	return;
}



void Entity::teleport(const Position &pos){
	/*
	 * @param	pos		the coordinates of the destination
	 *
	 * Teleports the entity from its current location to the given one
	 */




	this->teleport(pos.xPos(), pos.yPos());
	return;
}



void Entity::updateVelocity(const Position &acceleration, float friction, float deltaTime){
	/*
	 * @param	acceleration	The change in velocity of the entity
	 *
	 * @param	friction		The amount of dynamic friction of the entity, range is 0.0 to 1.0
	 *
	 * @param	deltaTime		The amount of time since the last tick
	 */




	this->velocity = this->velocity + acceleration * deltaTime;

	//Add dynamic friction to the entity
	if(friction > 1.0f) friction = 1.0f;
	else if(friction < 0.0f) friction = 0.0f;
	this->velocity = this->velocity - this->velocity * deltaTime * friction;

	return;
}



void Entity::updateVelocity(double xAcc, double yAcc, float friction, float deltaTime){

	this->updateVelocity(Position(xAcc, yAcc), friction, deltaTime);
	return;
}



void Entity::updatePosition(float deltaTime){

	Position pos(this->getPosition().xPos(), this->getPosition().yPos());
	this->lastPosition = pos;

	this->getPosition().move(pos.xPos() + this->velocity.xPos() * deltaTime, pos.yPos() + this->velocity.yPos() * deltaTime);

	return;
}



Position& Entity::getPosition() {
	return this->tilePosition;
}



const Position& Entity::getPreviousPosition(void) const {
	return this->lastPosition;
}



const Position& Entity::getVelocity(void) const {
	return this->velocity;
}



AABB& Entity::getBoundingBox(void) {
	return this->hitBox;
}



bool Entity::isLiving(void) const {
	return this->livingEntity;
}



bool Entity::isAlive(void) const {
	return this->health > 0 ? true : false;
}



void Entity::increaseHealth(int healthIn){
	int delta = this->health += std::abs(healthIn);
	delta > this->maxHealth ? this->health = this->maxHealth : this->health = delta;
	return;
}



void Entity::decreaseHealth(int healthIn){
	int delta = this->health -= std::abs(healthIn);
	delta < 0 ? this->health = 0 : this->health = delta;
	return;
}



int Entity::getHealth(void) const {
	return this->health;
}



void Entity::increaseMaxHealth(int healthIn){
	int delta = std::abs(healthIn);
	this->maxHealth += delta;
	return;
}



void Entity::decreaseMaxHealth(int healthIn){
	int delta = this->maxHealth -= std::abs(healthIn);
	delta < 0 ? this->maxHealth = 0 : this->maxHealth = delta;
	//Update health so that it is not larger than the maximum health
	if(this->health > this->maxHealth) this->health = this->maxHealth;
	return;
}



int Entity::getMaxHealth(void) const {
	return this->maxHealth;
}



bool Entity::isFriendly(void) const {
	return this->behavior == EnumBehavior::PASSIVE ? true : false;
}



bool Entity::isNeutral(void) const {
	return this->behavior == EnumBehavior::NEUTRAL ? true : false;
}



bool Entity::isAggressive(void) const {
	return this->behavior == EnumBehavior::AGGRESSIVE ? true : false;
}



bool Entity::isPlayer(void) const {
	return this->behavior == EnumBehavior::PLAYER ? true : false;
}



bool Entity::isSolid(void) const {
	return solid;
}



bool Entity::isMoving(void) const {
	return this->velocity > 0;
}



bool Entity::isFalling(void) const {
	return !(this->onGround || this->flying);
}



bool Entity::isFlying(void) const {
	return this->flying;
}



void Entity::setFlying(bool stateIn){
	this->flying = stateIn;
	return;
}



void Entity::setOnGround(bool stateIn){
	this->onGround = stateIn;
	return;
}



void Entity::setTag(std::string &tagIn){
	if(this->tag == "null"){
		this->tag = tagIn;
	}

	return;
}








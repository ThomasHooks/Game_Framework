//============================================================================
// Name       		: Entity.cpp
// Author     		: Thomas Hooks
// Last Modified	: 02/29/2020
//============================================================================




#include "Entity.h"

#include <algorithm>

#include <SDL.h>
#include "SDL_image.h"




Entity::Entity(std::string tagIn, Dimension dimensionIn)
	: tag(tagIn),
	  tilePosition(),
	  lastPosition(),
	  velocity(),
	  spriteSize(dimensionIn),
	  spriteLocation(),
	  health(1),
	  maxHealth(1),
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



const std::string& Entity::getTag(void) const {
	return this->tag;
}



Position& Entity::getPosition(){
	return this->tilePosition;
}



void Entity::teleport(double x, double y){
	this->getPosition().move(x, y);
}



void Entity::teleport(const Position &pos){
	this->getPosition().move(pos.xPos(), pos.yPos());
}



void Entity::updateVelocity(const Position &acceleration, float deltaTime){
	this->velocity = this->velocity + acceleration * deltaTime;
}



void Entity::updateVelocity(double xAcc, double yAcc, float deltaTime){

	Position acceleration(xAcc, yAcc);
	this->velocity = this->velocity + acceleration * deltaTime;

	return;
}



void Entity::updatePosition(float deltaTime){

	Position pos(this->getPosition().xPos(), this->getPosition().yPos());
	this->lastPosition = pos;

	this->getPosition().move(pos.xPos() + this->velocity.xPos() * deltaTime, pos.yPos() + this->velocity.yPos() * deltaTime);

	return;
}



AABB& Entity::getBoundingBox(void) {
	return this->hitBox;
}



bool Entity::isAlive(void){
	return this->health > 0 ? true : false;
}



void Entity::increaseHealth(int healthIn){
	int delta = this->health += std::abs(healthIn);
	delta > this->maxHealth ? this->health = this->maxHealth : this->health = delta;
}



void Entity::decreaseHealth(int healthIn){
	int delta = this->health -= std::abs(healthIn);
	delta < 0 ? this->health = 0 : this->health = delta;
}



int Entity::getHealth(void){
	return this->health;
}



void Entity::increaseMaxHealth(int healthIn){
	int delta = std::abs(healthIn);
	this->maxHealth += delta;
}



void Entity::decreaseMaxHealth(int healthIn){
	int delta = this->maxHealth -= std::abs(healthIn);
	delta < 0 ? this->maxHealth = 0 : this->maxHealth = delta;
	//Update health so that it is not larger than the maximum health
	if(this->health > this->maxHealth) this->health = this->maxHealth;
}



int Entity::getMaxHealth(void){
	return this->maxHealth;
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



bool Entity::isSolid(void){
	return solid;
}



bool Entity::isMoving(void){
	return this->velocity > 0;
}



bool Entity::isFalling(void){
	return !(this->onGround || this->flying);
}



bool Entity::isFlying(void){
	return this->flying;
}



void Entity::setFlying(bool stateIn){
	this->flying = stateIn;
}



void Entity::setOnGround(bool stateIn){
	this->onGround = stateIn;
}








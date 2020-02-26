//============================================================================
// Name       		: Entity.cpp
// Author     		: Thomas Hooks
// Last Modified	: 02/25/2020
//============================================================================




#include "Entity.h"

#include <SDL.h>
#include "SDL_image.h"




Entity::Entity(std::string tagIn, Position posIn, Dimension dimIn, EnumBehavior behaviorIn)
	: tag(tagIn),
	  tilePosition(posIn, dimIn),
	  velocity(),
	  acceleration(),
	  health(1),
	  maxHealth(1),
	  solid(true),
	  behavior(behaviorIn) {}



Entity::~Entity() {}



Entity::Entity(const Entity &other)
	: tag(other.tag),
	  tilePosition(other.tilePosition),
	  velocity(other.velocity),
	  acceleration(other.acceleration),
	  health(other.health),
	  maxHealth(other.maxHealth),
	  solid(other.solid),
	  behavior(other.behavior) {}



Entity::Entity(Entity &&other)
	: tag(other.tag),
	  tilePosition(other.tilePosition),
	  velocity(other.velocity),
	  acceleration(other.acceleration),
	  health(other.health),
	  maxHealth(other.maxHealth),
	  solid(other.solid),
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
	SDL_Rect spriteRect = {0, 0, this->tilePosition.get_width(), this->tilePosition.get_height()};

	//calculate the entities size and location in the world
	int xPos = this->tilePosition.get_xPosN() - offset.x * this->tilePosition.get_width();
	int yPos = this->tilePosition.get_yPosN() - offset.y * this->tilePosition.get_height();
	SDL_Rect entityRect = {xPos, yPos, this->tilePosition.get_width(), this->tilePosition.get_height()};

	//Draw the Character to the screen
	SDL_RenderCopyEx(rendererIn, texture, &spriteRect, &entityRect, 0, NULL, SDL_FLIP_NONE);

	return;
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








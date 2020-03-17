//============================================================================
// Name       		: HealthCapability.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/16/2020
//============================================================================




#include "../capabilities/HealthCapability.h"

#include "../IEntity.hpp"




HealthCapability::HealthCapability(int healthIn, int maxHealthIn)
	: health(healthIn),
	  maxHealth(maxHealthIn) {}



HealthCapability::~HealthCapability() {}



//Called to update this state
void HealthCapability::process(class IEntity &context){
	if(!this->isAlive() && !context.isPlayer()) context.markInactive();
}



//Checks if the Entity is alive
bool HealthCapability::isAlive() const {
	return this->health > 0 ? true : false;
}



/*
 * @param	healthIn The amount of health to increase by
 *
 * Increases the health of this Entity by the given amount
 */
void HealthCapability::increaseHealth(int healthIn){
	int delta = this->health += std::abs(healthIn);
	delta > this->maxHealth ? this->health = this->maxHealth : this->health = delta;
}



/*
 * @param	healthIn The amount of health to decrease by
 *
 * Decreases the health of this Entity by the given amount
 */
void HealthCapability::decreaseHealth(int healthIn){
	int delta = this->health -= std::abs(healthIn);
	delta < 0 ? this->health = 0 : this->health = delta;
}



//Gets this Entity's amount of health
int HealthCapability::getHealth() const {
	return this->health;
}



/*
 * @param	healthIn The amount of maximum health to increase by
 *
 * Increases the maximum health of this Entity by the given amount
 */
void HealthCapability::increaseMaxHealth(int healthIn){
	int delta = std::abs(healthIn);
	this->maxHealth += delta;
}



/*
 * @param	healthIn The amount of maximum health to decrease by
 *
 * Decreases the maximum health of this Entity by the given amount
 */
void HealthCapability::decreaseMaxHealth(int healthIn){
	int delta = this->maxHealth -= std::abs(healthIn);
	delta < 0 ? this->maxHealth = 0 : this->maxHealth = delta;
	//Update health so that it is not larger than the maximum health
	if(this->health > this->maxHealth) this->health = this->maxHealth;
}



//Gets the maximum health of this Entity
int HealthCapability::getMaxHealth() const {
	return this->maxHealth;
}








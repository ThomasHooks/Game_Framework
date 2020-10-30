//============================================================================
// Name       		: HealthCapability.h
// Author     		: Thomas Hooks
// Last Modified	: 03/16/2020
//============================================================================




#ifndef CAPABILITIES_HEALTHCAPABILITY_H_
#define CAPABILITIES_HEALTHCAPABILITY_H_


#include "IEntityCapability.h"


class HealthCapability : public IEntityCapability {

public:

	HealthCapability(int healthIn, int maxHealthIn);



	~HealthCapability();



	//Called to update this state
	void process(class IEntity &context) override;



	//Checks if the Entity is alive
	bool isAlive() const;



	/*
	 * @param	healthIn The amount of health to increase by
	 *
	 * Increases the health of this Entity by the given amount
	 */
	void increaseHealth(int healthIn);



	/*
	 * @param	healthIn The amount of health to decrease by
	 *
	 * Decreases the health of this Entity by the given amount
	 */
	void decreaseHealth(int healthIn);



	//Gets this Entity's amount of health
	int getHealth() const;



	/*
	 * @param	healthIn The amount of maximum health to increase by
	 *
	 * Increases the maximum health of this Entity by the given amount
	 */
	void increaseMaxHealth(int healthIn);



	/*
	 * @param	healthIn The amount of maximum health to decrease by
	 *
	 * Decreases the maximum health of this Entity by the given amount
	 */
	void decreaseMaxHealth(int healthIn);



	//Gets the maximum health of this Entity
	int getMaxHealth() const;



private:

	int health;
	int maxHealth;
};


#endif /* CAPABILITIES_HEALTHCAPABILITY_H_ */




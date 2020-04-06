//============================================================================
// Name       		: Entity.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/14/2020
//============================================================================




#ifndef ENTITY_H_
#define ENTITY_H_


#include <string>

#include "../utilities/physics/AABB.h"
#include "../utilities/physics/Dimension.h"
#include "../utilities/physics/Position.h"
#include "EnumEntityType.h"


class [[deprecated("Use src/entities/IEntity instead")]]Entity {

public:

	Entity();

	virtual ~Entity();

	Entity(const Entity &other);

	Entity(Entity &&other);

	virtual void tick(float deltaTime) = 0;

	void draw(struct SDL_Renderer *rendererIn,
			  struct SDL_Texture *texture,
			  const Position offset);

	const Dimension& getSpriteSize(void) const;
	const Dimension& getAnimation(void) const;
	const std::string& getTag(void) const;

	void teleport(double x, double y);
	void teleport(const Position &pos);
	void updateVelocity(const Position &acceleration, float friction, float deltaTime);
	void updateVelocity(double xAcc, double yAcc, float friction, float deltaTime);
	void updatePosition(float deltaTime);

	Position& getPosition(void);
	const Position& getPreviousPosition(void) const;
	const Position& getVelocity(void) const;

	AABB& getBoundingBox(void);

	bool isLiving(void) const;
	bool isAlive(void) const;

	void increaseHealth(int healthIn);
	void decreaseHealth(int healthIn);
	int getHealth(void) const;

	void increaseMaxHealth(int healthIn);
	void decreaseMaxHealth(int healthIn);
	int getMaxHealth(void) const;

	bool isFriendly(void)const;
	bool isNeutral(void) const;
	bool isAggressive(void) const;
	bool isPlayer(void) const;

	bool isSolid(void) const;

	bool isMoving(void) const;

	bool isFalling(void) const;
	bool isFlying(void) const;
	void setFlying(bool stateIn);
	void setOnGround(bool stateIn);

protected:

	void setTag(std::string &tagIn);

	Position tilePosition;
	Position lastPosition;
	Position velocity;

	Dimension spriteSize;
	Dimension spriteLocation;

	bool livingEntity;

	int health;
	int maxHealth;

	bool solid;

	bool flying;
	bool onGround;

	AABB hitBox;

	EnumEntityType behavior;

private:

	std::string tag;
};


#endif /* ENTITY_H_ */




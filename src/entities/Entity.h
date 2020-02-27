//============================================================================
// Name       		: Entity.cpp
// Author     		: Thomas Hooks
// Last Modified	: 02/27/2020
//============================================================================




#ifndef ENTITY_H_
#define ENTITY_H_


#include <string>

#include "../utilities/TilePosition.h"
#include "EnumBehavior.h"
#include "../utilities/AABB.h"


class Entity {

public:

	Entity(std::string tagIn,
		   Position posIn,
		   Dimension dimIn);

	virtual ~Entity();

	Entity(const Entity &other);

	Entity(Entity &&other);

	virtual void tick(float deltaTime) = 0;

	void draw(struct SDL_Renderer *rendererIn,
			  struct SDL_Texture *texture,
			  const Position offset);

	std::string get_tag(void) const;

	TilePosition& get_position(void);
	void teleport(double x, double y);
	void teleport(const Position &pos);
	void updateVelocity(const Position &acceleration, float deltaTime);
	void updateVelocity(double xAcc, double yAcc, float deltaTime);
	void updatePosition(float deltaTime);

	AABB& get_BoundingBox(void);

	bool isAlive(void);

	void increaseHealth(int healthIn);
	void decreaseHealth(int healthIn);
	int get_health(void);

	void increaseMaxHealth(int healthIn);
	void decreaseMaxHealth(int healthIn);
	int get_maxHealth(void);

	bool isFriendly(void);
	bool isNeutral(void);
	bool isAggressive(void);

	bool isSolid(void);

	bool isMoving(void);

	bool isFalling(void);
	bool isFlying(void);
	void setOnGround(bool state);

protected:

	std::string tag;

	TilePosition tilePosition;
	Position lastPosition;
	Position velocity;

	Dimension spriteLocation;

	int health;
	int maxHealth;

	bool solid;

	bool flying;
	bool onGround;

	AABB hitBox;

	EnumBehavior behavior;
};


#endif /* ENTITY_H_ */




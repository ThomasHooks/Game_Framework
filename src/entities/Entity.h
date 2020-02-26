//============================================================================
// Name       		: Entity.cpp
// Author     		: Thomas Hooks
// Last Modified	: 02/25/2020
//============================================================================




#ifndef ENTITY_H_
#define ENTITY_H_


#include <string>

#include "../utilities/TilePosition.h"
#include "EnumBehavior.h"


class Entity {

public:

	Entity(std::string tagIn,
		   Position posIn,
		   Dimension dimIn,
		   EnumBehavior behaviorIn);

	virtual ~Entity();

	Entity(const Entity &other);

	Entity(Entity &&other);

	virtual void tick(float deltaTime) = 0;

	void draw(struct SDL_Renderer *rendererIn,
			  struct SDL_Texture *texture,
			  const Position offset);

	std::string get_tag(void) const {return tag;}

	TilePosition& get_position(void);

	bool isFriendly(void);
	bool isNeutral(void);
	bool isAggressive(void);

	bool isSolid(void) {return solid;}

protected:

	std::string tag;

	TilePosition tilePosition;

	Position velocity;
	Position acceleration;

	int health;
	int maxHealth;

	bool solid;

	EnumBehavior behavior;
};


#endif /* ENTITY_H_ */




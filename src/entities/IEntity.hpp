//============================================================================
// Name       		: IEntity.h
// Author     		: Thomas Hooks
// Last Modified	: 03/16/2020
//============================================================================




#ifndef IENTITY_HPP_
#define IENTITY_HPP_


#include <string>
#include <memory>
#include <vector>
#include <map>

#include "../utilities/EnumSide.h"
#include "../utilities/Position.h"
#include "../utilities/Dimension.h"
#include "capabilities/IEntityCapability.h"
#include "EnumEntityType.h"




class IEntity {

public:

	IEntity();



	virtual ~IEntity();



	/*
	 * @param	posIn Coordinates the Entity is to be spawned
	 *
	 * @param	facingIn The direction the Entity is to be facing
	 *
	 * This method is called just as an Entity is spawned
	 */
	virtual void onSpwan(const Position &posIn, EnumSide facingIn) = 0;



	//This method is called right before an Entity is despawned
	virtual void onDespwan() = 0;



	/*
	 * @param	deltaTime The amount of time since the last tick
	 *
	 * This method is called each tick
	 */
	virtual void tick(float deltaTime) = 0;



	/*
	 * @param	other The Entity that has been collided with
	 *
	 * @param	side The side of the other Entity that has been collided with
	 *
	 * This method is called when the Entity collides with another Entity
	 */
	virtual void onEntityColision(IEntity &other, EnumSide side) = 0;



	/*
	 * @param	tile The Tile the Entity collided with
	 *
	 * @param	side The side of the Tile that the Entity collided with
	 *
	 * This method is called when the Entity collides with a Tile
	 */
	virtual void onTileColision(class ITile &tile, EnumSide side) = 0;



	//Gets the Entity's registration tag
	const std::string& getRegistryTag() const;



	//Checks if the Entity is active
	bool isActive() const;



	//Marks the Entity to be despawned
	void markInactive();



	//Checks if the Entity has collision
	bool canCollide() const;



	//Gets the Entity's type
	EnumEntityType getType() const;



	//Checks if the Entity is passive
	bool isPassive(void)const;



	//Checks if the Entity is neutral
	bool isNeutral(void) const;



	//Checks if the Entity is aggressive
	bool isAggressive(void) const;



	//Checks if the Entity is a player
	bool isPlayer(void) const;



	//Gets the sprite's location in the sprite sheet
	const Dimension& getSprite() const;



	//Gets the direction that the Entity is facing
	EnumEntityType directionFacing() const;



	//Gets the Entity's position
	const Position& getPos() const;



	/*
	 * @param	pos The new position of the Entity
	 *
	 * Moves the Entity to a new position
	 */
	void teleport(const Position &pos);



	//Checks if the Entity is moving
	bool isMoving(void) const;



	/*
	 * @param	FacingIn The new direction that the Entity is facing
	 *
	 * Changes the direction that the Entity is facing
	 */
	void setDirectionFacing(EnumSide facingIn);



	/*
	 * @param	stateTag The state's tag
	 *
	 * @return	True if the Entity has the state
	 *
	 * Checks if the Entity has the given state
	 */
	bool hasState(const std::string &stateTag);



	/*
	 * @nullable
	 *
	 * @param	stateTag The tag of the state to get
	 *
	 * @return	A pointer to the Entity's state given by tag
	 *
	 * Gets the given Entity's state
	 */
	template<class T>
	T* getState(const std::string &stateTag){
		return this->states.find(stateTag) != this->states.end() ? this->states[stateTag].get() : nullptr;
	}



	/*
	 * @param	tag The states ID tag
	 *
	 * @param	mArgs The states arguments
	 *
	 * @return	A pointer to the Entity the state is being added to
	 *
	 * Adds a new state to the given Entity
	 */
	template<class T, typename... TArgs>
	IEntity& addState(std::string tag, TArgs... mArgs){

		this->states.insert({tag, std::make_unique<T>((mArgs)...)});

		return *this;
	}



protected:

	//Used to set the Entity's registration tag
	void setRegistryTag(const std::string &tagIn);



	//Used to update an Entity's sprite
	void setSprite(const Dimension &spriteIn);



	/*
	 * @param	typeIn The Entity's type
	 *
	 * Used to set the Entity's type
	 */
	void setEntityType(EnumEntityType typeIn);



	/*
	 * @param	accel The acceleration of the Entity
	 *
	 * @param	frict The friction of the Entity
	 *
	 * @param	deltaTime The amount of time since the last tick
	 *
	 * Updates the velocity of the Entity
	 */
	void updateVel(const Position &accel, float frict, float deltaTime);



	/*
	 * @param	deltaTime The amount of time since the last tick
	 *
	 * Updates the position of the Entity
	 */
	void updatePos(float deltaTime);



private:

	std::string tag;

	bool active;

	bool solid;

	Position pos;
	Position lastPos;
	Position vel;

	Dimension sprite;

	EnumEntityType type;

	EnumSide facing;

	std::map<std::string, std::unique_ptr<IEntityCapability>> states;
};


#endif /* IENTITY_HPP_ */




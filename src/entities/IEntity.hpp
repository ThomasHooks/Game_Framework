//============================================================================
// Name       		: IEntity.h
// Author     		: Thomas Hooks
// Last Modified	: 03/14/2020
//============================================================================




#ifndef IENTITY_HPP_
#define IENTITY_HPP_


#include <string>
#include <memory>
#include <vector>

#include "../utilities/EnumSide.h"
#include "../utilities/Position.h"
#include "../utilities/Dimension.h"
#include "EnumEntityType.h"
#include "states/IEntityState.h"




class IEntity {

public:

	IEntity();



	virtual ~IEntity();



	//This method is called just after an Entity is spawned
	virtual void onSpwan() = 0;



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

		for(auto itr = this->states.begin(); itr != this->states.end(); ++itr){
			if(itr->get()->getTag() == stateTag) return std::static_pointer_cast<T>(itr->get());
		}
		return nullptr;
	}



protected:

	//Used to set the Entity's registration tag
	void setRegistryTag(const std::string &tagIn);



	//Used to update an Entity's sprite
	void setSprite(const Dimension &spriteIn);



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



	/*
	 * @param	mArgs The states arguments
	 *
	 * @return	A pointer to the Entity the state is being added to
	 *
	 * Adds a new state to the given Entity
	 */
	template<class T, typename... TArgs>
	IEntity* addState(TArgs... mArgs){

		this->states.emplace_back(std::make_unique<T>((mArgs)...));

		return this;
	}


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

	std::vector<std::unique_ptr<IEntityState>> states;
};


#endif /* IENTITY_HPP_ */




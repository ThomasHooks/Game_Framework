#ifndef IENTITY_HPP_
#define IENTITY_HPP_


#include <string>
#include <memory>
#include <vector>
#include <map>

#include "utilities/physics/AABB.h"
#include "utilities/math/Pos2.hpp"
#include "utilities/math/Pos3.hpp"
#include "utilities/physics/EnumSide.h"
#include "utilities/physics/TilePos.h"
#include "capabilities/IEntityCapability.h"
#include "EnumEntityType.h"




class IEntity 
{
public:

	IEntity();



	virtual ~IEntity();



	/// <summary>
	/// This method is called just as an Entity is spawned
	/// </summary>
	/// <param name="posIn">Coordinates the Entity is to be spawned</param>
	/// <param name="facingIn">The direction the Entity is to be facing</param>
	/// <param name="entityIDIn">This Entity's ID tag</param>
	void spwan(const TilePos& posIn, EnumSide facingIn, unsigned int entityIDIn);



	/*
	 * @param	posIn Coordinates the Entity is to be spawned
	 *
	 * @param	facingIn The direction the Entity is to be facing
	 *
	 * This method is called just as an Entity is spawned
	 */
	virtual void onSpwan() = 0;



	//This method is called right before an Entity is despawned
	virtual void onDespwan() = 0;



	/*
	 * @param	deltaTime The amount of time since the last tick
	 *
	 * This method is called each tick
	 */
	virtual void tick(const class TileMap& world, float deltaTime) = 0;



	/*
	 * @param	other The Entity that has been collided with
	 *
	 * @param	side The side of the other Entity that has been collided with
	 *
	 * This method is called when the Entity collides with another Entity
	 */
	virtual void onEntityColision(IEntity& other, EnumSide side) = 0;



	/*
	 * @param	tile The Tile the Entity collided with
	 *
	 * @param	side The side of the Tile that the Entity collided with
	 *
	 * This method is called when the Entity collides with a Tile
	 */
	virtual void onTileColision(class ITile& tileIn, EnumSide side) = 0;



	//Gets the Entity's registration tag
	const std::string& getRegistryTag() const;



	//Gets the Entity's identification
	unsigned int getID() const;



	//Checks if the Entity is active
	bool isActive() const;



	//Marks the Entity to be despawned
	void markInactive();



	//Checks if the Entity has collision
	bool canCollide() const;



	//Gets the Entity's type
	EnumEntityType getType() const;



	//Checks if the Entity is passive
	bool isPassive()const;



	//Checks if the Entity is neutral
	bool isNeutral() const;



	//Checks if the Entity is aggressive
	bool isAggressive() const;



	//Checks if the Entity is a player
	bool isPlayer() const;



	//Gets the sprite's location in the sprite sheet
	const Pos2N& getSprite() const { return m_sprite; }



	//Gets the direction that the Entity is facing
	EnumEntityType directionFacing() const;



	//Gets the Entity's position
	const TilePos& getPos() const { return m_pos; }



	//Gets the Entity's axis aligned bounding box
	const AABB& getAabb() const;



	/*
	 * @param	pos The new position of the Entity
	 *
	 * Moves the Entity to a new position
	 */
	void teleport(const TilePos& pos);



	//Checks if the Entity is moving
	bool isMoving() const;



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
	bool hasCapability(const std::string &stateTag);



	/*
	 * @param	accel The acceleration of the Entity
	 *
	 * @param	frict The friction of the Entity ranging from 0.0 - 1.0
	 *
	 * @param	deltaTime The amount of time since the last tick
	 *
	 * Updates the velocity of the Entity
	 */
	void updateVel(const Pos2D& accel, float frict, float deltaTime);



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
	T* getCapability(const std::string &stateTag)
	{
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
	IEntity& addCapability(std::string tag, TArgs... mArgs)
	{
		this->states.insert({tag, std::make_unique<T>((mArgs)...)});
		return *this;
	}



protected:

	//Used to set the Entity's registration tag
	void setRegistryTag(const std::string &tagIn);



	//Used to update an Entity's sprite
	void setSprite(const Pos2N& spriteIn);



	/*
	 * @param	typeIn The Entity's type
	 *
	 * Used to set the Entity's type
	 */
	void setEntityType(EnumEntityType typeIn);



	/*
	 * @param	x1, y1 The coordinates of the top-left point
	 *
	 * @param	x2, y2 The coordinates of the bottom-right point
	 *
	 * Used to set the Entity's axis aligned bounding box
	 *
	 * The positions given should be relative to the tile
	 * and not the Global coordinates.
	 * ie. a tile that is 32x32 would be (0.0, 0.0, 32.0, 32.0)
	 */
	void setAabb(double x1, double y1, double x2, double y2);



	/*
	 * @param	deltaTime The amount of time since the last tick
	 *
	 * @param	frict The amount of breaking friction ranging from 0.0 - 1.0
	 *
	 * Updates the position of the Entity
	 */
	void updatePos(float frict, float deltaTime);



	//Gets the Entity's last position
	TilePos& getLastPos() { return m_lastPos; }



	//Gets the Entity's velocity
	Pos2D& getVel() { return m_vel; }



private:

	std::string tag;

	unsigned int entityID;

	bool active;

	bool solid;

	TilePos m_pos;

	TilePos m_lastPos;

	Pos2D m_vel;

	AABB hitBox;

	Pos2N m_sprite;

	EnumEntityType type;

	EnumSide facing;

	std::map<std::string, std::unique_ptr<IEntityCapability>> states;
};


#endif /* IENTITY_HPP_ */




#ifndef PLAYERENTITY_H_
#define PLAYERENTITY_H_


#include "IEntity.hpp"




class PlayerEntity : public IEntity 
{
public:

	PlayerEntity();



	~PlayerEntity();



	/*
	 * @param	posIn Coordinates the Entity is to be spawned
	 *
	 * @param	facingIn The direction the Entity is to be facing
	 *
	 * This method is called just as an Entity is spawned
	 */
	void onSpwan() override;



	//This method is called right before an Entity is despawned
	void onDespwan() override;



	/*
	 * @param	deltaTime The amount of time since the last tick
	 *
	 * This method is called each tick
	 */
	void tick(const class TileMap &world, float deltaTime) override;



	/*
	 * @param	other The Entity that has been collided with
	 *
	 * @param	side The side of the other Entity that has been collided with
	 *
	 * This method is called when the Entity collides with another Entity
	 */
	void onEntityColision(IEntity &other, EnumSide side) override;



	/*
	 * @param	tile The Tile the Entity collided with
	 *
	 * @param	side The side of the Tile that the Entity collided with
	 *
	 * This method is called when the Entity collides with a Tile
	 */
	void onTileColision(class ITile &tile, EnumSide side) override;
};


#endif /* PLAYERENTITY_H_ */




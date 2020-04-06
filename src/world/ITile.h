//============================================================================
// Name       		: ITile.h
// Author     		: Thomas Hooks
// Last Modified	: 03/21/2020
//============================================================================




#ifndef ITILE_H_
#define ITILE_H_


#include "../utilities/physics/AABB.h"
#include "../utilities/physics/Dimension.h"
#include "../utilities/physics/Position.h"


class ITile {

public:

	ITile(double x,
			double y,
			double w,
			double h,
			const Dimension &spriteIn,
			EnumSide direction,
			bool opaqueIn,
			bool solidIn);



	~ITile();



	//Gets this Tile's current position in Global-Space
	const Position& getPos() const;



	//Gets this Tile's axis aligned bounding box
	const AABB& getAabb() const;



	//Gets this Tile's current sprite
	const Dimension& getSprite() const;



	//Checks if this Tile has collision
	bool canCollide() const;



	/*
	 * @param	stateIn If the Tile has collision
	 *
	 * Sets this Tile collision state
	 */
	void setCollide(bool stateIn);



	//Checks if this Tile can be rendered
	bool isOpaque() const;



	/*
	 * @param	stateIn If the Tile can be seen
	 *
	 * Sets if this Tile can be seen
	 */
	void setOpaque(bool stateIn);



	/*
	 * @param	direction The side of the Tile to test for passability
	 *
	 * @return	True if the given direction is passable
	 *
	 * Checks if the given side of the Tile is passable
	 */
	bool isPassable(EnumSide direction) const;



	/*
	 * @return	True if the Tile is impassable
	 *
	 * Checks if this Tile is impassable
	 */
	bool isImpassable() const;



private:

	Position pos;

	AABB boundingBox;

	bool opaque;

	bool solid;

	EnumSide pass;

	Dimension sprite;
};


#endif /* ITILE_H_ */




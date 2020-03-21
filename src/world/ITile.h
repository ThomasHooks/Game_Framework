//============================================================================
// Name       		: ITile.h
// Author     		: Thomas Hooks
// Last Modified	: 03/20/2020
//============================================================================




#ifndef ITILE_H_
#define ITILE_H_


#include "../utilities/Position.h"
#include "../utilities/Dimension.h"
#include "../utilities/AABB.h"


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



	//Gets this Tile's current position
	const Position& getPos() const;



	//Gets this Tile's axis aligned bounding box
	const AABB& getAabb() const;



	//Gets this Tile's current sprite
	const Dimension& getSprite() const;



	//Checks if this Tile has collision
	bool canCollide() const;



	/*
	 * @param	state If the Tile has collision
	 *
	 * Sets this Tile collision state
	 */
	void setCollide(bool state);



	//Checks if this Tile can be rendered
	bool isOpaque() const;



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




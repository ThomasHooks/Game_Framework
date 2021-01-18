#ifndef ITILE_H_
#define ITILE_H_




#include "utilities/physics/AxisAlignedBB.h"
#include "utilities/math/Pos2.hpp"
#include "utilities/physics/TilePos.h"




class ITile 
{
public:

	ITile(double x, double y, double w, double h, const Pos2N& spriteIn, EnumSide direction, bool opaqueIn, bool solidIn);



	//Gets this Tile's current position in Global-Space
	const TilePos& getPos() const { return m_pos; }



	//Gets this Tile's axis aligned bounding box
	const AxisAlignedBB& getAabb() const { return m_boundingBox; }



	//Gets this Tile's current sprite
	const Pos2N& getSprite() const { return m_sprite; }



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

	TilePos m_pos;

	AxisAlignedBB m_boundingBox;

	bool m_isOpaque;

	bool m_isSolid;

	EnumSide m_passable;

	Pos2N m_sprite;
};


#endif




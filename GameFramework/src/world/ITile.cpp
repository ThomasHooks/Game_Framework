#include "ITile.h"




ITile::ITile(double x, double y, double w, double h, const Pos2N& spriteIn, EnumSide direction, bool opaqueIn, bool solidIn)
	: m_pos(x, y), m_boundingBox(x, y, x + w, y + h), m_isOpaque(opaqueIn), m_isSolid(solidIn), m_passable(direction), m_sprite(spriteIn.u, spriteIn.v) 
{}



bool ITile::canCollide() const 
{
	return m_isSolid;
}



/*
 * @param	state If the Tile has collision
 *
 * Sets this Tile collision state
 */
void ITile::setCollide(bool stateIn) 
{
	m_isSolid = stateIn;
}



//Checks if this Tile can be rendered
bool ITile::isOpaque() const 
{
	return m_isOpaque;
}



/*
 * @param	stateIn If the Tile can be seen
 *
 * Sets if this Tile can be seen
 */
void ITile::setOpaque(bool stateIn)
{
	m_isOpaque = stateIn;
}



/*
 * @param	direction The side of the Tile to test for passability
 *
 * @return	True if the given direction is passable
 *
 * Checks if the given side of the Tile is passable
 */
bool ITile::isPassable(EnumSide direction) const 
{
	return m_passable == direction;
}



/*
 * @return	True if the Tile is impassable
 *
 * Checks if this Tile is impassable
 */
bool ITile::isImpassable() const
{
	return m_passable == EnumSide::NONE;
}








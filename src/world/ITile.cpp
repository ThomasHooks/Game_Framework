//============================================================================
// Name       		: ITile.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/20/2020
//============================================================================




#include "ITile.h"




ITile::ITile(double x, double y, double w, double h, const Dimension &spriteIn, EnumSide direction, bool opaqueIn, bool solidIn)
	: pos(x, y),
	  boundingBox(x, y, x + w, y + h),
	  opaque(opaqueIn),
	  solid(solidIn),
	  pass(direction),
	  sprite(spriteIn.width, spriteIn.height) {}



ITile::~ITile() {}



//Gets this Tile's current position
const Position& ITile::getPos() const {
	return this->pos;
}



//Gets this Tile's axis aligned bounding box
const AABB& ITile::getAabb() const {
	return this->boundingBox;
}



//Gets this Tile's current sprite
const Dimension& ITile::getSprite() const {
	return this->sprite;
}



//Checks if this Tile has collision
bool ITile::canCollide() const {
	return this->solid;
}



/*
 * @param	state If the Tile has collision
 *
 * Sets this Tile collision state
 */
void ITile::setCollide(bool state) {
	this->solid = state;
}



//Checks if this Tile can be rendered
bool ITile::isOpaque() const {
	return this->opaque;
}



/*
 * @param	direction The side of the Tile to test for passability
 *
 * @return	True if the given direction is passable
 *
 * Checks if the given side of the Tile is passable
 */
bool ITile::isPassable(EnumSide direction) const {
	return this->pass == direction;
}



/*
 * @return	True if the Tile is impassable
 *
 * Checks if this Tile is impassable
 */
bool ITile::isImpassable() const{
	return this->pass == EnumSide::NONE ? true : false;
}








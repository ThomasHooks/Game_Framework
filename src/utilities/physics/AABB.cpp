//============================================================================
// Name       		: AABB.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/19/2020
//============================================================================




#include "AABB.h"

#include <algorithm>





AABB::AABB()
	: pos1(),
	  pos2() {}



AABB::AABB(double x1, double y1, double x2, double y2)
	: pos1(x1, y1),
	  pos2(x2, y2) {}



AABB::~AABB() {}



//Gets the Axis Aligned Bounding Box's width
double AABB::width() const {
	return std::abs(this->pos2.xPos() - this->pos1.xPos());
}



//Gets the integer value of the Axis Aligned Bounding Box's width
int AABB::widthN() const {
	return static_cast<int>(this->width() + 0.5);
}



//Gets the Axis Aligned Bounding Box's height
double AABB::height() const {
	return std::abs(this->pos2.yPos() - this->pos1.yPos());
}



//Gets the integer value of the Axis Aligned Bounding Box's height
int AABB::heightN() const {
	return static_cast<int>(this->height() + 0.5);
}



/*
 * @return The coordinates of the AABB's center
 *
 * Gets the center position of the Axis Aligned Bounding Box
 */
Position AABB::getCenter() const {

	double width = this->width();
	double height = this->height();
	return Position(this->pos1.xPos() + width/2.0, this->pos1.yPos()/2.0);
}



/*
 * @return The coordinates of the AABB's top-left corner
 *
 * Gets the top-left corner of the Axis Aligned Bounding Box
 */
Position AABB::getPos() const {
	return Position(this->pos1.xPos(), this->pos1.yPos());
}



/*
 * @param	amount The amount to increase the AABB by
 *
 * Grows the Axis Aligned Bounding Box by the given amount
 */
void AABB::grow(double amount){

	double delta = std::abs(amount);

	this->pos1.move_xPos(-delta);
	this->pos2.move_xPos(delta);

	this->pos1.move_yPos(-delta);
	this->pos2.move_yPos(delta);
}



/*
 * @param	amount The amount to decrease the AABB by
 *
 * Shrinks the Axis Aligned Bounding Box by the given amount
 */

void AABB::shrink(double amount){

	double delta = std::abs(amount);
	Position center = this->getCenter();

	//This is done so that the corners of the AABB do not flip
	this->width() < delta ? this->pos1.move_xPos(center.xPos()) : this->pos1.move_xPos(delta);
	this->width() < delta ? this->pos2.move_xPos(center.xPos()) : this->pos2.move_xPos(-delta);

	this->height() < delta ? this->pos1.move_yPos(center.yPos()) : this->pos1.move_yPos(delta);
	this->height() < delta ? this->pos2.move_yPos(center.yPos()) : this->pos2.move_yPos(-delta);
}



/*
 * @param	direction Which direction to modify the AABB in
 *
 * @param	amount The amount to modify the AABB by
 *
 * Changes the Axis Aligned Bounding Box in the given direction by the given amount
 */
void AABB::modify(EnumSide direction, double amount){

	double delta = std::abs(amount);
	switch(direction){

	case EnumSide::UP:
		this->pos1.move_yPos(-delta);
		break;

	case EnumSide::RIGHT:
		this->pos2.move_xPos(delta);
		break;

	case EnumSide::DOWN:
		this->pos2.move_yPos(delta);
		break;

	case EnumSide::LEFT:
		this->pos1.move_xPos(-delta);
		break;

	default:
		break;
	}
}



/*
 * @param	x The X coordinate to move the AABB by
 *
 * @param	y The Y coordinate to move the AABB by
 *
 * Moves the Axis Aligned Bounding Box by the given amount
 */
void AABB::offset(double x, double y){

	this->pos1.move_xPos(x);
	this->pos1.move_yPos(y);

	this->pos2.move_xPos(x);
	this->pos2.move_yPos(y);
}



/*
 * @param	posIn The coordinates to move the AABB by
 *
 * Moves the Axis Aligned Bounding Box by the given amount
 */
void AABB::offset(const Position &posIn){
	this->offset(posIn.xPos(), posIn.yPos());
}



/*
 * @param	direction Which direction the AABB is to be moved in
 *
 * @param	amount The distance the AABB is to be moved by
 *
 * Moves the Axis Aligned Bounding Box in the given direction by the given amount
 */
void AABB::nudge(EnumSide direction, double amount){

	double delta = std::abs(amount);
	switch(direction){

	case EnumSide::UP:
		this->pos1.move_yPos(-delta);
		this->pos2.move_yPos(-delta);
		break;

	case EnumSide::RIGHT:
		this->pos1.move_xPos(delta);
		this->pos2.move_xPos(delta);
		break;

	case EnumSide::DOWN:
		this->pos1.move_yPos(delta);
		this->pos2.move_yPos(delta);
		break;

	case EnumSide::LEFT:
		this->pos1.move_xPos(-delta);
		this->pos2.move_xPos(-delta);
		break;
	}
}



/*
 * @return	True if the Axis Aligned Bounding Box is a point
 *
 * Checks if the Axis Aligned Bounding Box is a point
 */
bool AABB::isPoint() const {
	return this->pos1 == this->pos2 ? true : false;
}








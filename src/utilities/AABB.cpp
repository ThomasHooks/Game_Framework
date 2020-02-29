//============================================================================
// Name       		: AABB.cpp
// Author     		: Thomas Hooks
// Last Modified	: 02/27/2020
//============================================================================




#include <algorithm>

#include "AABB.h"




AABB::AABB()
	: p1(),
	  p2() {}



AABB::AABB(double x1, double y1, double x2, double y2)
	: p1(std::min(x1, x2), std::min(y1, y2)),
	  p2(std::max(x1, x2), std::max(y1, y2)) {}



AABB::AABB(const Position &topLeft, const Position &bottomRight)
	: p1(topLeft.xPos(), topLeft.yPos()),
	  p2(bottomRight.xPos(), bottomRight.yPos()) {}



AABB::~AABB() {}



double AABB::width(void){
	return std::abs(this->p2.xPos() - this->p1.xPos());
}



int AABB::widthN(void){
	return static_cast<int>(this->width());
}



double AABB::height(void){
	return std::abs(this->p2.yPos() - this->p1.yPos());
}



int AABB::heightN(void){
	return static_cast<int>(this->height());
}



Position AABB::getCenter(void){
	/*
	 * @return	The relative coordinates of the AABB's center
	 *
	 * The returned Position is not the Global coordinates of the AABB's center
	 */




	return Position((std::max(this->p2, this->p1) - std::min(this->p2, this->p1))/2);
}



Position AABB::getTopLeftPoint(const Position& posIn) const {
	/*
	 * @param	posIn	The Global position of the Entity/Tile
	 *
	 * @return	The top-left position of the AABB in the Global coordinates
	 */




	return Position(this->p1 + posIn);
}



Position AABB::getBottomRightPoint(const Position& posIn) const {
	/*
	 * @param	posIn	The Global position of the Entity/Tile
	 *
	 * @return	The bottom-right position of the AABB in the Global coordinates
	 */




	return Position(this->p2 + posIn);
}



void AABB::grow(double amount){
	/*
	 * @brief	Grows the Axis Aligned Bounding Box by the given amount
	 *
	 * @param	amount	the amount to increase the AABB by
	 */




	double delta = std::abs(amount);

	this->p1.move_xPos(-delta);
	this->p1.move_xPos(delta);

	this->p1.move_yPos(-delta);
	this->p1.move_yPos(delta);

	return;
}



void AABB::shrink(double amount){
	/*
	 * @brief	Shrinks the Axis Aligned Bounding Box by the given amount
	 *
	 * @param	amount	the amount to decrease the AABB by
	 */




	double delta = std::abs(amount);
	Position center = this->getCenter();

	//This is done so that the corners of the AABB do not flip
	this->width() < delta ? this->p1.move_xPos(center.xPos()) : this->p1.move_xPos(delta);
	this->width() < delta ? this->p2.move_xPos(center.xPos()) : this->p2.move_xPos(-delta);

	this->height() < delta ? this->p1.move_yPos(center.yPos()) : this->p1.move_yPos(delta);
	this->height() < delta ? this->p2.move_yPos(center.yPos()) : this->p2.move_yPos(-delta);

	return;
}



void AABB::modify(EnumSide direction, double amount){
	/*
	 * @brief	Changes the Axis Aligned Bounding Box in the given direction by the given amount
	 *
	 * @param	direction	Which direction to modify the AABB in
	 *
	 * @param	amount		The amount to modify the AABB by
	 */




	double delta = std::abs(amount);
	switch(direction){

	case EnumSide::UP:
		this->p1.move_yPos(-delta);
		break;

	case EnumSide::RIGHT:
		this->p2.move_xPos(delta);
		break;

	case EnumSide::DOWN:
		this->p2.move_yPos(delta);
		break;

	case EnumSide::LEFT:
		this->p1.move_xPos(-delta);
		break;
	}
}



void AABB::offset(double x, double y){
	/*
	 * @brief	Moves the Axis Aligned Bounding Box by the given amount
	 *
	 * @param	x	The X coordinate to move the AABB by
	 *
	 * @param	y	The Y coordinate to move the AABB by
	 */




	this->p1.move_xPos(x);
	this->p1.move_yPos(y);

	this->p2.move_xPos(x);
	this->p2.move_yPos(y);

	return;
}



void AABB::nudge(EnumSide direction, double amount){
	/*
	 * @brief	Moves the Axis Aligned Bounding Box in the given direction by the given amount
	 *
	 * @param	direction	Which direction the AABB is to be moved in
	 *
	 * @param	amount		The distance the AABB is to be moved by
	 */




	double delta = std::abs(amount);
	switch(direction){

	case EnumSide::UP:
		this->p1.move_yPos(-delta);
		this->p2.move_yPos(-delta);
		break;

	case EnumSide::RIGHT:
		this->p1.move_xPos(delta);
		this->p2.move_xPos(delta);
		break;

	case EnumSide::DOWN:
		this->p1.move_yPos(delta);
		this->p2.move_yPos(delta);
		break;

	case EnumSide::LEFT:
		this->p1.move_xPos(-delta);
		this->p2.move_xPos(-delta);
		break;
	}

	return;
}



bool AABB::isPoint(void){
	return this->p1 == this->p2 ? true : false;
}








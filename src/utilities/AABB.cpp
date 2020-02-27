//============================================================================
// Name       		: AABB.cpp
// Author     		: Thomas Hooks
// Last Modified	: 02/27/2020
//============================================================================




#include <algorithm>

#include "AABB.h"




AABB::AABB() : p1(), p2() {}



AABB::AABB(double x1, double y1, double x2, double y2)
	: p1(std::min(x1, x2), std::min(y1, y2)),
	  p2(std::max(x1, x2), std::max(y1, y2)) {}



AABB::AABB(const Position &topLeft, const Position &bottomRight)
	: p1(topLeft.x, topLeft.y),
	  p2(bottomRight.x, bottomRight.y) {}



AABB::~AABB() {}



double AABB::get_width(void){
	return std::abs(this->p2.x - this->p1.x);
}



int AABB::get_widthN(void){
	return static_cast<int>(this->get_width());
}



double AABB::get_height(void){
	return std::abs(this->p2.y - this->p1.y);
}



int AABB::get_heightN(void){
	return static_cast<int>(this->get_height());
}



Position AABB::get_center(void){
	return Position((this->p2.x - this->p1.x)/2, (this->p2.y - this->p1.y)/2);
}



void AABB::grow(double amount){
	/*
	 * @brief	Grows the Axis Aligned Bounding Box by the given amount
	 *
	 * @param	amount	the amount to increase the AABB by
	 */




	double delta = std::abs(amount);

	this->p1.x -= delta;
	this->p2.x += delta;

	this->p1.y -= delta;
	this->p2.y += delta;

	return;
}



void AABB::shrink(double amount){
	/*
	 * @brief	Shrinks the Axis Aligned Bounding Box by the given amount
	 *
	 * @param	amount	the amount to decrease the AABB by
	 */




	double delta = std::abs(amount);
	Position center = this->get_center();

	//This is done so that the corners of the AABB do not flip
	this->get_width() < delta ? this->p1.x = center.x : this->p1.x += delta;
	this->get_width() < delta ? this->p2.x = center.x : this->p2.x -= delta;

	this->get_height() < delta ? this->p1.y = center.y : this->p1.y += delta;
	this->get_height() < delta ? this->p2.y = center.y : this->p2.y -= delta;

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
		this->p1.y -= delta;
		break;

	case EnumSide::RIGHT:
		this->p2.x += delta;
		break;

	case EnumSide::DOWN:
		this->p2.y += delta;
		break;

	case EnumSide::LEFT:
		this->p1.x -= delta;
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




	this->p1.x += x;
	this->p1.y += y;
	this->p2.x += x;
	this->p2.y += y;

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
		this->p1.y -= delta;
		this->p2.y -= delta;
		break;

	case EnumSide::RIGHT:
		this->p1.x += delta;
		this->p2.x += delta;
		break;

	case EnumSide::DOWN:
		this->p1.y += delta;
		this->p2.y += delta;
		break;

	case EnumSide::LEFT:
		this->p1.x -= delta;
		this->p2.x -= delta;
		break;
	}

	return;
}



bool AABB::isPoint(void){
	return this->p1 == this->p2 ? true : false;
}








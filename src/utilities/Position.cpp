//============================================================================
// Name       		: Position.cpp
// Author     		: Thomas Hooks
// Last Modified	: 02/29/2020
//============================================================================




#include "Position.h"




Position::Position()
	: x(0.0),
	  y(0.0) {}



Position::Position(double x, double y)
	: x(x),
	  y(y) {}



Position::~Position() {}



float Position::xPosF(void) const {

	return static_cast<float>(this->x);
}



float Position::yPosF(void) const {

	return static_cast<float>(this->y);
}



int Position::xPosN(void) const {

	return static_cast<int>(this->x + 0.5);
}



int Position::yPosN(void) const {

	return static_cast<int>(this->y + 0.5);
}



void Position::move_xPos(double amout){
	this->x += amout;
}



void Position::move_yPos(double amout){
	this->y += amout;
}



void Position::move(double x, double y) {

	this->x = x;
	this->y = y;

	return;
}



void Position::move(const Position &pos){

	this->x = pos.x;
	this->y = pos.y;

	return;
}



void Position::offsetBy(EnumSide direction, double distance){
	//

	switch(direction){
	case EnumSide::NONE:
		break;

	case EnumSide::UP:
		this->y -= distance;
		break;

	case EnumSide::RIGHT:
		this->x += distance;
		break;

	case EnumSide::DOWN:
		this->y += distance;
		break;

	case EnumSide::LEFT:
		this->x -= distance;
		break;
	}
}



bool Position::isPoint(void) const {
	return this->xPosN() == this->yPosN() ? true : false;
}



bool Position::operator==(const Position& other) const {
	return (this->x == other.x) && (this->y == other.y) ? true : false;
}



bool Position::operator>(const Position& other) const {
	return (this->x > other.x) && (this->y > other.y);
}



bool Position::operator>=(const Position& other) const{
	return (this->x >= other.x) && (this->y >= other.y);
}



bool Position::operator<(const Position& other) const {
	return (this->x < other.x) && (this->y < other.y);
}



bool Position::operator<=(const Position& other) const {
	return (this->x <= other.x) && (this->y <= other.y);
}



bool Position::operator>(int scalar) const {
	return (this->x > scalar) && (this->y > scalar);
}



bool Position::operator>=(int scalar) const{
	return (this->x >= scalar) && (this->y >= scalar);
}



bool Position::operator<(int scalar) const {
	return (this->x < scalar) && (this->y < scalar);
}



bool Position::operator<=(int scalar) const {
	return (this->x <= scalar) && (this->y <= scalar);
}



Position Position::operator+(const Position& other) const {
	return Position(this->x + other.x, this->y + other .y);
}



Position Position::operator+(double scalar) const {
	return Position(this->x + scalar, this->y + scalar);
}



Position Position::operator-(const Position& other) const {
	return Position(this->x - other.x, this->y - other .y);
}



Position Position::operator-(double scalar) const {
	return Position(this->x - scalar, this->y - scalar);
}



Position Position::operator*(double scalar) const {
	return Position(this->x * scalar, this->y * scalar);
}



Position Position::operator/(double scalar) const {
	return Position(this->x/scalar, this->y/scalar);
}








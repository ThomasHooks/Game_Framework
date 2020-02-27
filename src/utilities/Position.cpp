//============================================================================
// Name       		: Position.cpp
// Author     		: Thomas Hooks
// Last Modified	: 02/27/2020
//============================================================================




#include "Position.h"




Position::Position()
	: x(0.0), y(0.0) {}



Position::Position(double x, double y)
	: x(x), y(y) {}



Position::~Position() {}



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








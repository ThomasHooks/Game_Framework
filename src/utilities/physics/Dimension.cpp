//============================================================================
// Name       		: Dimension.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/09/2020
//============================================================================




#include "Dimension.h"




Dimension::Dimension()
	: width(0),
	  height(0) {}



Dimension::Dimension(int width, int height)
	: width(width),
	  height(height) {}



Dimension::~Dimension() {}



bool Dimension::operator==(const Dimension& other) const {
	return (this->width == other.width) && (this->height == other.height) ? true : false;
}



bool Dimension::operator>(const Dimension& other) const {
	return (this->width > other.width) && (this->height > other.height);
}



bool Dimension::operator>=(const Dimension& other) const{
	return (this->width >= other.width) && (this->height >= other.height);
}



bool Dimension::operator<(const Dimension& other) const {
	return (this->width < other.width) && (this->height < other.height);
}



bool Dimension::operator<=(const Dimension& other) const {
	return (this->width <= other.width) && (this->height <= other.height);
}



bool Dimension::operator>(int scalar) const {
	return (this->width > scalar) && (this->height > scalar);
}



bool Dimension::operator>=(int scalar) const{
	return (this->width >= scalar) && (this->height >= scalar);
}



bool Dimension::operator<(int scalar) const {
	return (this->width < scalar) && (this->height < scalar);
}



bool Dimension::operator<=(int scalar) const {
	return (this->width <= scalar) && (this->height <= scalar);
}



Dimension Dimension::operator+(const Dimension& other) const {
	return Dimension(this->width + other.width, this->height + other .height);
}



Dimension Dimension::operator-(const Dimension& other) const {
	return Dimension(this->width - other.width, this->height - other .height);
}



Dimension Dimension::operator+(int scalar) const {
	return Dimension(this->width + scalar, this->height + scalar);
}



Dimension Dimension::operator-(int scalar) const {
	return Dimension(this->width - scalar, this->height - scalar);
}



Dimension Dimension::operator*(int scalar) const {
	return Dimension(this->width * scalar, this->height * scalar);
}



Dimension Dimension::operator/(int scalar) const {
	return Dimension(this->width/scalar, this->height/scalar);
}








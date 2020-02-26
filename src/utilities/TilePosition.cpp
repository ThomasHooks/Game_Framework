//============================================================================
// Name       		: TilePosition.cpp
// Author     		: Thomas Hooks
// Last Modified	: 02/24/2020
//============================================================================




#include "TilePosition.h"




TilePosition::TilePosition()
	: position(),
	  dimension() {}



TilePosition::TilePosition(double x, double y)
	: position(x, y),
	  dimension() {}



TilePosition::TilePosition(Position positionIn)
	: position(positionIn.x, positionIn.y),
	  dimension() {}



TilePosition::TilePosition(double x, double y, int width, int height)
	: position(x, y),
	  dimension(width, height) {}



TilePosition::TilePosition(Position positionIn, Dimension dimensionIn)
	: position(positionIn.x, positionIn.y),
	  dimension(dimensionIn.width, dimensionIn.height) {}



TilePosition::~TilePosition() {}



TilePosition::TilePosition(const TilePosition &other)
	: position(other.position.x, other.position.y),
	  dimension(other.dimension.width, other.dimension.height) {}



TilePosition::TilePosition(TilePosition &&other)
	: position(other.position.x, other.position.y),
	  dimension(other.dimension.width, other.dimension.height) {

	other.position.x = 0.0;
	other.position.y = 0.0;
	other.dimension.width = 0;
	other.dimension.height = 0;
}



float TilePosition::get_xPosF(void){

	return static_cast<float>(this->position.x);
}



float TilePosition::get_yPosF(void){

	return static_cast<float>(this->position.y);
}



int TilePosition::get_xPosN(void){

	return static_cast<int>(this->position.x + 0.5);
}



int TilePosition::get_yPosN(void){

	return static_cast<int>(this->position.y + 0.5);
}



void TilePosition::set_position(double x, double y) {
	//

	this->position.x = x;
	this->position.y = y;

	return;
}



void TilePosition::set_position(const Position &pos){
	//

	this->position.x = pos.x;
	this->position.y = pos.y;

	return;
}



void TilePosition::set_dimensions(int width, int height){
	//

	if(width >= 0) this->dimension.width = width;
	else this->dimension.width = 0;

	if(width >= 0) this->dimension.height = height;
	else this->dimension.height = 0;

	return;
}



void TilePosition::set_dimensions(const Dimension &dim){
	//

	this->dimension.width = dim.width;
	this->dimension.height = dim.height;

	return;
}



void TilePosition::offsetBy(Side direction, double distance){
	//

	switch(direction){
	case Side::NONE:
		break;

	case Side::UP:
		this->position.y -= distance;
		break;

	case Side::RIGHT:
		this->position.x += distance;
		break;

	case Side::DOWN:
		this->position.y += distance;
		break;

	case Side::LEFT:
		this->position.x -= distance;
		break;
	}
}



bool TilePosition::isPoint(void){

	if(this->get_width() == 0 && this->get_height() == 0) return true;
	else return false;
}



Position TilePosition::getCenter(void){

	return Position(this->position.x - this->dimension.width/2, this->position.y + this->dimension.height/2);
}








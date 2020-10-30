//============================================================================
// Name       		: Direction.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/22/2020
//============================================================================




#include "Direction.h"




/*
 * @param	dir The direction to get the opposite of
 *
 * @return	The opposite direction otherwise NONE
 */
EnumSide Direction::getOpposite(EnumSide dir){
	switch(dir){

	case EnumSide::UP:
		return EnumSide::DOWN;

	case EnumSide::RIGHT:
		return EnumSide::LEFT;

	case EnumSide::DOWN:
		return EnumSide::UP;

	case EnumSide::LEFT:
		return EnumSide::RIGHT;

	default:
		return EnumSide::NONE;
	}
}



/*
 * @param	dir The direction to rotate clockwise
 *
 * @return	The clockwise rotated direction otherwise NONE
 */
EnumSide Direction::rotateCW(EnumSide dir){
	switch(dir){

	case EnumSide::UP:
		return EnumSide::RIGHT;

	case EnumSide::RIGHT:
		return EnumSide::DOWN;

	case EnumSide::DOWN:
		return EnumSide::LEFT;

	case EnumSide::LEFT:
		return EnumSide::UP;

	default:
		return EnumSide::NONE;
	}
}



/*
 * @param	dir The direction to rotate counter clockwise
 *
 * @return	The counter clockwise rotated direction otherwise NONE
 */
EnumSide Direction::rotateCCW(EnumSide dir){
	switch(dir){

	case EnumSide::UP:
		return EnumSide::LEFT;

	case EnumSide::RIGHT:
		return EnumSide::UP;

	case EnumSide::DOWN:
		return EnumSide::RIGHT;

	case EnumSide::LEFT:
		return EnumSide::DOWN;

	default:
		return EnumSide::NONE;
	}
}

//============================================================================
// Name       		: Direction.h
// Author     		: Thomas Hooks
// Last Modified	: 03/22/2020
//============================================================================




#ifndef DIRECTION_H_
#define DIRECTION_H_


#include "EnumSide.h"


namespace Direction {

/*
 * @param	dir The direction to get the opposite of
 *
 * @return	The opposite direction otherwise NONE
 */
EnumSide getOpposite(EnumSide dir);



/*
 * @param	dir The direction to rotate clockwise
 *
 * @return	The clockwise rotated direction otherwise NONE
 */
EnumSide rotateCW(EnumSide dir);



/*
 * @param	dir The direction to rotate counter clockwise
 *
 * @return	The counter clockwise rotated direction otherwise NONE
 */
EnumSide rotateCCW(EnumSide dir);
}


#endif /* DIRECTION_H_ */




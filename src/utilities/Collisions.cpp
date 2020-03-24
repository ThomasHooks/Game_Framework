//============================================================================
// Name       		: Collisions.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/17/2020
//============================================================================




#include "Collisions.h"

#include <math.h>
#include <algorithm>
#include <iostream>




/*
 * @param	xRect, yRect Top left corner of the rectangle
 *
 * @param	wRect Width of the rectangle
 *
 * @param	hRect Height of the rectangle
 *
 * @param	xPt, yPt Center of the point
 *
 * @return	True if the point is inside of the rectangle
 *
 * checks if a point is inside of a rectangle
 */
bool Collision::RectVsPt(double xRect, double yRect, double wRect, double hRect, double xPt, double yPt){

	//right edge, left edge, top edge, bottom edge
	if(xRect + wRect >= xPt && xRect <= xPt && yRect + hRect >= yPt && yRect <= yPt) return true;

	else return false;
}



/*
 * @param	posRect The coordinates of the rectangle
 *
 * @param	dimRect The dimension of the rectangle
 *
 * @param	posPt The coordinates of the point
 *
 * @return	True if the point is inside of the rectangle
 *
 * Checks if a point is inside of a rectangle
 */
bool Collision::RectVsPt(const Position &posRect, const Dimension &dimRect, const Position &posPt){
	return RectVsPt(posRect.xPos(), posRect.yPos(), dimRect.width, dimRect.height, posPt.xPos(), posPt.yPos());
}



/*
 * @param	rect The axis aligned bounding box of the rectangle
 *
 * @param	posPt The coordinates of the point
 *
 * @return	True if the point is inside of the rectangle
 *
 * Checks if a point is inside of a rectangle
 */
bool Collision::RectVsPt(const AABB &rect, const Position &posPt){
	return RectVsPt(rect.getPos().xPos(), rect.getPos().yPos(), rect.width(), rect.height(), posPt.xPos(), posPt.yPos());
}



/*
 * @param	x1,y1	top left corner of rectangle 1
 *
 * @param	w1		width of rectangle 1
 *
 * @param	h1		height of rectangle 1
 *
 * @param	x2,y2	top left corner of rectangle 2
 *
 * @param	w2		width of rectangle 2
 *
 * @param	h2		height of rectangle 2
 *
 * @return	True if the rectangles are overlapping/colliding
 *
 * Checks if two rectangle are overlapping/colliding
 */
bool Collision::RectVsRect(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2){

	//right edge, left edge, top edge, bottom edge
	if(x1 + w1 >= x2 && x1 <= x2 + w2 && y1 + h1 >= y2 && y1 <= y2 + h2) return true;

	else return false;
}



/*
 * @param	pos1 Coordinates of the first rectangle
 *
 * @param	dim1 Size of the first rectangle
 *
 * @param	pos2 Coordinates of the second rectangle
 *
 * @param	dim2 Size of the second rectangle
 *
 * @return	True if the rectangles are overlapping/colliding
 *
 * Checks if 2 rectangles are overlapping/colliding
 */
bool Collision::RectVsRect(const Position &pos1, const Dimension &dim1, const Position &pos2, const Dimension &dim2){
	return RectVsRect(pos1.xPos(), pos1.yPos(), dim1.width, dim1.height, pos2.xPos(), pos2.yPos(), dim2.width, dim2.height);
}



/*
 * @param	rect1 The axis aligned bounding box of the first rectangle
 *
 * @param	rect2 The axis aligned bounding box of the second rectangle
 *
 * @return	True if the rectangles are overlapping/colliding
 *
 * Checks if 2 rectangles are overlapping/colliding
 */
bool Collision::RectVsRect(const AABB &rect1, const AABB &rect2){
	return RectVsRect(rect1.getPos().xPos(), rect1.getPos().yPos(), rect1.width(), rect1.height(),
			rect2.getPos().xPos(), rect2.getPos().yPos(), rect2.width(), rect2.height());
}



/*
 * @param	x1,y1	top left corner of rectangle 1
 *
 * @param	w1		width of rectangle 1
 *
 * @param	h1		height of rectangle 1
 *
 * @param	x2,y2	top left corner of rectangle 2
 *
 * @param	w2		width of rectangle 2
 *
 * @param	h2		height of rectangle 2
 *
 * @return	Which side of two rectangles is colliding
 *
 * Checks which side of rectangle 1 is colliding with rectangle 2
 */
EnumSide Collision::RectEdge(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2){

	if(RectVsRect(x1, y1, w1, h1, x2, y2, w2, h2)) {
		//first calculate each rectangle's center
		Position rect1Center(x1 + w1/2.0, y1 + h1/2.0);
		Position rect2Center(x2 + w2/2.0, y2 + h2/2.0);
		Position distance(rect1Center.xPos() - rect2Center.xPos(), rect1Center.yPos() - rect2Center.yPos());

		//Now check which components of rectangle 2 is further from rectangle 1's center
		if(std::abs(distance.xPosN()) > std::abs(distance.yPosN())) {
			//Because the x component of rectangle 2 is closer to rectangle 1's center
			//Check if rectangle 2 is to the right or left of rectangle 1's center
			return rect2Center.xPosN() <= rect1Center.xPosN() ? EnumSide::LEFT : EnumSide::RIGHT;
		}
		//Because the y component of rectangle 2 is further from rectangle 1's center
		else {
			//Check if rectangle 2 is above or below rectangle 1's center
			//Note values will become negative when going above rectangle 1's center
			return rect2Center.yPosN() <= rect1Center.yPosN() ? EnumSide::UP : EnumSide::DOWN;
		}
	}
	//Because neither overlap
	else return EnumSide::NONE;
}



/*
 * @param	rect1 The axis aligned bounding box of the first rectangle
 *
 * @param	rect2 The axis aligned bounding box of the second rectangle
 *
 * @return	Which side of two rectangles is colliding
 *
 * Checks which side of rectangle 1 is colliding with rectangle 2
 */
EnumSide Collision::RectEdge(const AABB &rect1, const AABB &rect2){
	return RectEdge(rect1.getPos().xPos(), rect1.getPos().yPos(), rect1.width(), rect1.height(),
			rect2.getPos().xPos(), rect2.getPos().yPos(), rect2.width(), rect2.height());
}







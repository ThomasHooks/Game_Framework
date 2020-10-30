//============================================================================
// Name       		: Collisions.h
// Author     		: Thomas Hooks
// Last Modified	: 03/17/2020
//============================================================================




#ifndef COLLISIONS_H_
#define COLLCOLLISIONS_H_


#include "EnumSide.h"
#include "Dimension.h"
#include "Position.h"
#include "AABB.h"


namespace Collision {

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
bool RectVsPt(double xRect,
		double yRect,
		double wRect,
		double hRect,
		double xPt,
		double yPt);



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
bool RectVsPt(const Position &posRect,
		const Dimension &dimRect,
		const Position &posPt);



/*
 * @param	rect The axis aligned bounding box of the rectangle
 *
 * @param	posPt The coordinates of the point
 *
 * @return	True if the point is inside of the rectangle
 *
 * Checks if a point is inside of a rectangle
 */
bool RectVsPt(const AABB &rect,
		const Position &posPt);



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
bool RectVsRect(double x1,
		double y1,
		double w1,
		double h1,
		double x2,
		double y2,
		double w2,
		double h2);



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
bool RectVsRect(const Position &pos1,
		const Dimension &dim1,
		const Position &pos2,
		const Dimension &dim2);



/*
 * @param	rect1 The axis aligned bounding box of the first rectangle
 *
 * @param	rect2 The axis aligned bounding box of the second rectangle
 *
 * @return	True if the rectangles are overlapping/colliding
 *
 * Checks if 2 rectangles are overlapping/colliding
 */
bool RectVsRect(const AABB &rect1, const AABB &rect2);



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
EnumSide RectEdge(double x1,
		double y1,
		double w1,
		double h1,
		double x2,
		double y2,
		double w2,
		double h2);



/*
 * @param	rect1 The axis aligned bounding box of the first rectangle
 *
 * @param	rect2 The axis aligned bounding box of the second rectangle
 *
 * @return	Which side of two rectangles is colliding
 *
 * Checks which side of rectangle 1 is colliding with rectangle 2
 */
EnumSide RectEdge(const AABB &rect1, const AABB &rect2);
}


#endif /* COLLISIONS_H_  */





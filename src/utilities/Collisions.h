//============================================================================
// Name       		: Collisions.h
// Author     		: Thomas Hooks
// Last Modified	: 03/12/2020
//============================================================================




#ifndef COLLISIONS_H_
#define COLLCOLLISIONS_H_


#include "EnumSide.h"
#include "Dimension.h"
#include "Position.h"
#include "AABB.h"


namespace Collision {

bool RectVsPt(double xRect,
		double yRect,
		double wRect,
		double hRect,
		double xPt,
		double yPt);

bool RectVsPt(const Position &posRect,
		const Dimension &dimRect,
		const Position &posPt);

bool RectVsRect(double x1,
		double y1,
		double w1,
		double h1,
		double x2,
		double y2,
		double w2,
		double h2);

bool RectVsRect(const Position &pos1,
		const Dimension &dim1,
		const Position &pos2,
		const Dimension &dim2);

bool RectVsRect(const AABB &rect1, const AABB &rect2);

EnumSide RectEdge(double x1,
		double y1,
		double w1,
		double h1,
		double x2,
		double y2,
		double w2,
		double h2);

EnumSide RectEdge(const AABB &rect1, const AABB &rect2);
}


#endif /* COLLISIONS_H_  */





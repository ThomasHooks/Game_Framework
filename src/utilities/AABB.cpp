//============================================================================
// Name       		: AABB.cpp
// Author     		: Thomas Hooks
// Last Modified	: 02/25/2020
//============================================================================




#include "AABB.h"

#include "../utilities/Position.h"




AABB::AABB() : p1(), p2() {}



AABB::AABB(double x1, double y1, double x2, double y2) : p1(x1, y1), p2(x2, y2) {}



AABB::AABB(struct Position p1In, struct Position p2In) : p1(p1In), p2(p2In) {}



AABB::~AABB() {}








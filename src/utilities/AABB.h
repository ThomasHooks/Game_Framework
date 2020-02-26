//============================================================================
// Name       		: AABB.h
// Author     		: Thomas Hooks
// Last Modified	: 02/25/2020
//============================================================================




#ifndef AABB_H_
#define AABB_H_


#include "../utilities/Position.h"


class AABB {

public:

	AABB();
	AABB(double x1, double y1, double x2, double y2);
	AABB(Position p1In, Position p2In);

	~AABB();

	Position p1;
	Position p2;
};


#endif /* AABB_H_ */




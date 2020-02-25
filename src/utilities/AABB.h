//============================================================================
// Name       		: AABB.h
// Author     		: Thomas Hooks
// Last Modified	: 02/25/2020
//============================================================================




#ifndef AABB_H_
#define AABB_H_




class AABB {

public:

	AABB();
	AABB(double x1, double y1, double x2, double y2);
	AABB(struct Position p1In, struct Position p2In);

	~AABB();

	struct Position p1;
	struct Position p2;
};


#endif /* AABB_H_ */




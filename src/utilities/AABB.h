//============================================================================
// Name       		: AABB.h
// Author     		: Thomas Hooks
// Last Modified	: 02/27/2020
//============================================================================




#ifndef AABB_H_
#define AABB_H_


#include "Position.h"
#include  "EnumSide.h"


class AABB {

public:

	AABB();
	AABB(double x1, double y1, double x2, double y2);
	AABB(const Position &topLeft, const Position &bottomRight);

	~AABB();

	double width(void);
	int widthN(void);
	double height(void);
	int heightN(void);

	Position getCenter(void);

	Position getTopLeftPoint(const Position& posIn) const;
	Position getBottomRightPoint(const Position& posIn) const;

	void grow(double amount);
	void shrink(double amount);
	void modify(EnumSide direction, double amount);

	void offset(double x, double y);
	void nudge(EnumSide direction, double amount);

	bool isPoint(void);

private:

	Position p1;	//Top-left corner
	Position p2;	//Bottom-right corner
};


#endif /* AABB_H_ */




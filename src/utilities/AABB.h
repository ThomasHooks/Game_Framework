//============================================================================
// Name       		: AABB.h
// Author     		: Thomas Hooks
// Last Modified	: 03/11/2020
//============================================================================




#ifndef AABB_H_
#define AABB_H_


#include "Position.h"
#include  "EnumSide.h"


class AABB {

public:

	AABB();
	AABB(double x1, double y1, double width, double height);

	~AABB();

	double width() const;
	int widthN() const;
	double height(void) const;
	int heightN() const;

	Position getCenter() const;

	Position getPos() const;

	void grow(double amount);
	void shrink(double amount);
	void modify(EnumSide direction, double amount);

	void offset(double x, double y);
	void offset(const Position &posIn);
	void nudge(EnumSide direction, double amount);

	bool isPoint() const;

private:

	Position pos1;
	Position pos2;
};


#endif /* AABB_H_ */




//============================================================================
// Name       		: AABB.h
// Author     		: Thomas Hooks
// Last Modified	: 03/19/2020
//============================================================================




#ifndef AABB_H_
#define AABB_H_


#include "EnumSide.h"
#include "Position.h"


class AABB {

public:

	AABB();


	/*
	 * @param	x1, y1 The coordinates of the top-left point
	 *
	 * @param	x2, y2 The coordinates of the bottom-right point
	 */
	AABB(double x1, double y1, double x2, double y2);



	~AABB();



	//Gets the Axis Aligned Bounding Box's width
	double width() const;



	//Gets the integer value of the Axis Aligned Bounding Box's width
	int widthN() const;



	//Gets the Axis Aligned Bounding Box's height
	double height(void) const;



	//Gets the integer value of the Axis Aligned Bounding Box's height
	int heightN() const;



	/*
	 * @return The coordinates of the AABB's center
	 *
	 * Gets the center position of the Axis Aligned Bounding Box
	 */
	Position getCenter() const;



	/*
	 * @return The coordinates of the AABB's top-left corner
	 *
	 * Gets the top-left corner of the Axis Aligned Bounding Box
	 */
	Position getPos() const;



	/*
	 * @param	amount The amount to increase the AABB by
	 *
	 * Grows the Axis Aligned Bounding Box by the given amount
	 */
	void grow(double amount);



	/*
	 * @param	amount The amount to decrease the AABB by
	 *
	 * Shrinks the Axis Aligned Bounding Box by the given amount
	 */

	void shrink(double amount);



	/*
	 * @param	direction Which direction to modify the AABB in
	 *
	 * @param	amount The amount to modify the AABB by
	 *
	 * Changes the Axis Aligned Bounding Box in the given direction by the given amount
	 */
	void modify(EnumSide direction, double amount);



	/*
	 * @param	x The X coordinate to move the AABB by
	 *
	 * @param	y The Y coordinate to move the AABB by
	 *
	 * Moves the Axis Aligned Bounding Box by the given amount
	 */
	void offset(double x, double y);



	/*
	 * @param	posIn The coordinates to move the AABB by
	 *
	 * Moves the Axis Aligned Bounding Box by the given amount
	 */
	void offset(const Position &posIn);



	/*
	 * @param	direction Which direction the AABB is to be moved in
	 *
	 * @param	amount The distance the AABB is to be moved by
	 *
	 * Moves the Axis Aligned Bounding Box in the given direction by the given amount
	 */
	void nudge(EnumSide direction, double amount);



	bool isPoint() const;



private:

	Position pos1;
	Position pos2;
};


#endif /* AABB_H_ */




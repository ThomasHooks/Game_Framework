#ifndef AXISALIGNEDBB_H_
#define AXISALIGNEDBB_H_


#include "utilities/physics/EnumSide.h"
#include "utilities/math/Pos2.hpp"
#include "utilities/math/Pos3.hpp"




class AxisAlignedBB 
{
public:

	AxisAlignedBB();



	AxisAlignedBB(double x1, double y1, double x2, double y2);



	//Gets the Axis Aligned Bounding Box's width
	double width() const;



	//Gets the integer value of the Axis Aligned Bounding Box's width
	int widthN() const;



	//Gets the Axis Aligned Bounding Box's height
	double height() const;



	//Gets the integer value of the Axis Aligned Bounding Box's height
	int heightN() const;



	/*
	 * @return The coordinates of the AABB's center
	 *
	 * Gets the center position of the Axis Aligned Bounding Box
	 */
	Pos2D getCenter() const;



	/*
	 * @return The coordinates of the AABB's top-left corner
	 *
	 * Gets the top-left corner of the Axis Aligned Bounding Box
	 */
	const Pos2D& getPos() const;



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
	void offset(const Pos3D& posIn);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="posIn"></param>
	void move(const Pos2D& posIn);



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

	Pos2D m_pos1;

	Pos2D m_pos2;
};


#endif




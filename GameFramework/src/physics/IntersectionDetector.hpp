#ifndef IntersectionDetector_HPP_
#define IntersectionDetector_HPP_


#include "physics/Line2D.hpp"




class IntersectionDetector 
{
public:

	/// <summary>
	/// 
	/// </summary>
	/// <param name="point"></param>
	/// <param name="line"></param>
	/// <param name="epsilon"></param>
	/// <returns></returns>
	static bool isPointOnLine(const Pos2D& point, const Line2D& line, double epsilon);



	static bool isPointOnLine(const Pos2D& point, const Line2D& line);



	/// <summary>
	/// Checks if the specified point is inside of a rectangle
	/// </summary>
	/// <param name="point">Specifies the coordinates of the point</param>
	/// <param name="aabb">Specifies the Axis-Aligned Bounding Box</param>
	/// <returns></returns>
	static bool isPointInAABB(const Pos2D& point, const class AxisAlignedBB& aabb);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="aabb1"></param>
	/// <param name="aabb2"></param>
	/// <returns></returns>
	static bool aabbVsAABB(const class AxisAlignedBB& aabb1, const class AxisAlignedBB& aabb2);
}; 


#endif /* IntersectionDetector_HPP_ */




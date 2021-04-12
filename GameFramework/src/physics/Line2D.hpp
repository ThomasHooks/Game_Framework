#ifndef Line2D_HPP_
#define Line2D_HPP_


#include <limits>
#include <algorithm>

#include "utilities/math/Pos2.hpp"




struct Line2D 
{
	Pos2D start;



	Pos2D end;



	Line2D(const Pos2D& startIn, const Pos2D& endIn)
		: start(startIn), end(endIn) 
	{}



	Line2D(double x1, double y1, double x2, double y2)
		: start(x1, y1), end(x2, y2)
	{}



	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool isVertical() const
	{
		return std::abs(end.x - start.x) <= 0.000001 * std::max(1.0, std::max(std::abs(end.x), std::abs(start.x)));
	}



	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool isHorizontal() const
	{
		return std::abs(end.y - start.y) <= 0.000001 * std::max(1.0, std::max(std::abs(end.y), std::abs(start.y)));
	}



	/// <summary>
	/// Calculates the slope of this line
	/// </summary>
	/// <returns>The slope of this line unless the line is vertical and which case it will return std::numeric_limits::infinity</returns>
	double slope() const
	{
		if (isVertical())
			return std::numeric_limits<double>::infinity();
		else
			return (end.y - start.y) / (end.x - start.x);
	}



	/// <summary>
	/// Calculates the y-intercept of this line
	/// </summary>
	/// <returns>The y-intercept of this line</returns>
	double yIntercept() const
	{
		return start.y - slope() * start.x;
	}
}; 


#endif /* Line2D_HPP_ */




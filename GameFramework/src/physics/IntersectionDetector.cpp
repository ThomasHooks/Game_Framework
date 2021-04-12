#include <limits>
#include <algorithm>

#include "IntersectionDetector.hpp"
#include "utilities/physics/AxisAlignedBB.h"




bool IntersectionDetector::isPointOnLine(const Pos2D& point, const Line2D& line, double epsilon)
{
	if (line.slope() == std::numeric_limits<double>::infinity())
		return std::abs(point.x - line.end.x) <= epsilon * std::max(1.0, std::max(std::abs(point.x), std::abs(line.end.x)));
	else
	{
		double y2 = line.slope() * point.x + line.yIntercept();
		return std::abs(point.y - y2) <= epsilon * std::max(1.0, std::max(std::abs(point.y), std::abs(y2)));
	}
}



bool IntersectionDetector::isPointOnLine(const Pos2D& point, const Line2D& line)
{
	return isPointOnLine(point, line, 0.000001);
}



bool IntersectionDetector::isPointInAABB(const Pos2D& point, const AxisAlignedBB& aabb)
{
	Pos2D aabbPos = aabb.getPos();
	Pos2D aabbSize(aabb.width(), aabb.height());
	return aabbPos.x + aabbSize.w >= point.x && aabbPos.x <= point.x && aabbPos.y + aabbSize.h >= point.y && aabbPos.y <= point.y;;
}



bool IntersectionDetector::aabbVsAABB(const AxisAlignedBB& aabb1, const AxisAlignedBB& aabb2)
{
	Pos2D pos1 = aabb1.getPos();
	Pos2D size1(aabb1.width(), aabb1.height());
	Pos2D pos2 = aabb2.getPos();
	Pos2D size2(aabb2.width(), aabb2.height());
	return pos1.x + size1.w >= pos2.x && pos1.x <= pos2.x + size2.w && pos1.y + size1.h >= pos2.y && pos1.y <= pos2.y + size2.h;
}




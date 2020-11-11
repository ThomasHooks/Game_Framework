#ifndef COLLISIONS_H_
#define COLLCOLLISIONS_H_

#include "utilities/physics/EnumSide.h"
#include "utilities/math/Pos2.hpp"
#include "utilities/physics/TilePos.h"
#include "utilities/physics/AABB.h"




namespace Collision 
{

/// <summary>
/// Checks if a point is inside of a rectangle
/// </summary>
/// <param name="xRect">Top left X coordinate of the rectangle</param>
/// <param name="yRect">Top left Y coordinate of the rectangle</param>
/// <param name="wRect">Width of the rectangle</param>
/// <param name="hRect">Height of the rectangle</param>
/// <param name="xPt">X coordinate of the point</param>
/// <param name="yPt">Y coordinate of the point</param>
/// <returns>True if the point is inside of the rectangle</returns>
bool RectVsPt(double xRect, double yRect, double wRect, double hRect, double xPt, double yPt);



/// <summary>
/// Checks if a point is inside of a rectangle
/// </summary>
/// <param name="posRect">The coordinates of the rectangle</param>
/// <param name="dimRect">The dimension of the rectangle</param>
/// <param name="posPt">The coordinates of the point</param>
/// <returns>True if the point is inside of the rectangle</returns>
bool RectVsPt(const Pos2D& posRect, const Pos2N& dimRect, const Pos2D& posPt);



/// <summary>
/// Checks if a point is inside of a rectangle
/// </summary>
/// <param name="rect">The axis aligned bounding box of the rectangle</param>
/// <param name="posPt">The coordinates of the point</param>
/// <returns>True if the point is inside of the rectangle</returns>
bool RectVsPt(const AABB& rect, const Pos2D& posPt);



/// <summary>
/// Checks if a point is inside of a rectangle
/// </summary>
/// <param name="rect">The axis aligned bounding box of the rectangle</param>
/// <param name="posPt">The coordinates of the point</param>
/// <returns>True if the point is inside of the rectangle</returns>
bool RectVsPt(const AABB& rect, const TilePos& posPt);



/// <summary>
/// Checks if two rectangle are overlapping/colliding
/// </summary>
/// <param name="x1">Top left X coordinate of the first rectangle</param>
/// <param name="y1">Top left Y coordinate of the first rectangle</param>
/// <param name="w1">Width of the first rectangle</param>
/// <param name="h1">Height of the first rectangle</param>
/// <param name="x2">Top left X coordinate of the second rectangle</param>
/// <param name="y2">Top left Y coordinate of the second rectangle</param>
/// <param name="w2">Width of the second rectangle</param>
/// <param name="h2">Height of the second rectangle</param>
/// <returns>True if the rectangles are overlapping/colliding</returns>
bool RectVsRect(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2);



/// <summary>
/// Checks if 2 rectangles are overlapping/colliding
/// </summary>
/// <param name="pos1">Coordinates of the first rectangle</param>
/// <param name="dim1">Size of the first rectangle</param>
/// <param name="pos2">Coordinates of the second rectangle</param>
/// <param name="dim2">Size of the second rectangle</param>
/// <returns>True if the rectangles are overlapping/colliding</returns>
bool RectVsRect(const Pos2D& pos1, const Pos2N& dim1, const Pos2D& pos2, const Pos2N& dim2);



/// <summary>
/// Checks if 2 rectangles are overlapping/colliding
/// </summary>
/// <param name="rect1">The axis aligned bounding box of the first rectangle</param>
/// <param name="rect2">The axis aligned bounding box of the second rectangle</param>
/// <returns>True if the rectangles are overlapping/colliding</returns>
bool RectVsRect(const AABB &rect1, const AABB &rect2);



/// <summary>
/// Checks which side of rectangle 1 is colliding with rectangle 2
/// </summary>
/// <param name="x1">Top left X coordinate of the first rectangle</param>
/// <param name="y1">Top left Y coordinate of the first rectangle</param>
/// <param name="w1">Width of the first rectangle</param>
/// <param name="h1">Height of the first rectangle</param>
/// <param name="x2">Top left X coordinate of the second rectangle</param>
/// <param name="y2">Top left Y coordinate of the second rectangle</param>
/// <param name="w2">Width of the second rectangle</param>
/// <param name="h2">Height of the second rectangle</param>
/// <returns>Which side of two rectangles is colliding</returns>
EnumSide RectEdge(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2);



/// <summary>
/// Checks which side of rectangle 1 is colliding with rectangle 2
/// </summary>
/// <param name="rect1">The axis aligned bounding box of the first rectangle</param>
/// <param name="rect2">The axis aligned bounding box of the second rectangle</param>
/// <returns>Which side of two rectangles is colliding</returns>
EnumSide RectEdge(const AABB &rect1, const AABB &rect2);
}


#endif




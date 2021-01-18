#include <math.h>
#include <algorithm>
#include <iostream>

#include "Collisions.h"




bool Collision::RectVsPt(double xRect, double yRect, double wRect, double hRect, double xPt, double yPt)
{
	//right edge, left edge, top edge, bottom edge
	if(xRect + wRect >= xPt && xRect <= xPt && yRect + hRect >= yPt && yRect <= yPt) return true;

	else return false;
}



bool Collision::RectVsPt(const Pos2D& posRect, const Pos2N &dimRect, const Pos2D& posPt)
{
	return RectVsPt(posRect.x, posRect.y, dimRect.x, dimRect.y, posPt.x, posPt.y);
}



bool Collision::RectVsPt(const AxisAlignedBB& rect, const Pos2D& posPt){
	return RectVsPt(rect.getPos().x, rect.getPos().y, rect.width(), rect.height(), posPt.x, posPt.y);
}



bool Collision::RectVsPt(const AxisAlignedBB& rect, const TilePos& posPt)
{
	return RectVsPt(rect.getPos().x, rect.getPos().y, rect.width(), rect.height(), posPt.x(), posPt.y());
}



bool Collision::RectVsRect(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2)
{
	//right edge, left edge, top edge, bottom edge
	if(x1 + w1 >= x2 && x1 <= x2 + w2 && y1 + h1 >= y2 && y1 <= y2 + h2) return true;

	else return false;
}



bool Collision::RectVsRect(const Pos2D& pos1, const Pos2N& dim1, const Pos2D& pos2, const Pos2N& dim2)
{
	return RectVsRect(pos1.x, pos1.y, dim1.x, dim1.y, pos2.x, pos2.y, dim2.x, dim2.y);
}



bool Collision::RectVsRect(const AxisAlignedBB &rect1, const AxisAlignedBB &rect2)
{
	return RectVsRect(rect1.getPos().x, rect1.getPos().y, rect1.width(), rect1.height(),
			rect2.getPos().x, rect2.getPos().y, rect2.width(), rect2.height());
}



EnumSide Collision::RectEdge(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2)
{
	if (RectVsRect(x1, y1, w1, h1, x2, y2, w2, h2)) 
	{
		//first calculate each rectangle's center
		Pos2D rect1Center(x1 + w1/2.0, y1 + h1/2.0);
		Pos2D rect2Center(x2 + w2/2.0, y2 + h2/2.0);
		Pos2D distance(rect1Center.x - rect2Center.x, rect1Center.y - rect2Center.y);

		//Now check which components of rectangle 2 is further from rectangle 1's center
		if (std::abs(static_cast<int>(distance.x + 0.5)) > std::abs(static_cast<int>(distance.y + 0.5)))
		{
			//Because the x component of rectangle 2 is closer to rectangle 1's center
			//Check if rectangle 2 is to the right or left of rectangle 1's center
			return rect2Center.x <= rect1Center.x ? EnumSide::LEFT : EnumSide::RIGHT;
		}
		//Because the y component of rectangle 2 is further from rectangle 1's center
		else 
		{
			//Check if rectangle 2 is above or below rectangle 1's center
			//Note values will become negative when going above rectangle 1's center
			return rect2Center.y <= rect1Center.y ? EnumSide::UP : EnumSide::DOWN;
		}
	}
	//Because neither overlap
	else 
		return EnumSide::NONE;
}



EnumSide Collision::RectEdge(const AxisAlignedBB &rect1, const AxisAlignedBB &rect2)
{
	return RectEdge(rect1.getPos().x, rect1.getPos().y, rect1.width(), rect1.height(), rect2.getPos().x, rect2.getPos().y, rect2.width(), rect2.height());
}







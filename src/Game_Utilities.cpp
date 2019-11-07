//============================================================================
// Name       		: Game_Utilities.cpp
// Author     		: Thomas Hooks
// Version    		: 1
// Last Modified	: 11/2/2019
// Description		:
//============================================================================




#include "Game_Utilities.h"
#include <math.h>




//----------------------------------------------------------------------------
//							Position2D Constructors

Position2D::Position2D(){

	//position
	f_x = 0.0f;
	f_y = 0.0f;

	//velocity
	f_dx = 0.0f;
	f_dy = 0.0f;

	//acceleration
	f_2dx = 0.0f;
	f_2dy = 0.0f;

	return;
}


Position2D::Position2D(float x, float y){

	//position
	f_x = x;
	f_y = y;

	//velocity
	f_dx = 0.0f;
	f_dy = 0.0f;

	//acceleration
	f_2dx = 0.0f;
	f_2dy = 0.0f;

	return;
}


Position2D::Position2D(float x, float y, float dx, float dy){

	//position
	f_x = x;
	f_y = y;

	//velocity
	f_dx = dx;
	f_dy = dy;

	//acceleration
	f_2dx = 0.0f;
	f_2dy = 0.0f;

	return;
}


Position2D::Position2D(float x, float y,
		float dx, float dy, float d2x, float d2y){

	//position
	f_x = x;
	f_y = y;

	//velocity
	f_dx = dx;
	f_dy = dy;

	//acceleration
	f_2dx = d2x;
	f_2dy = d2y;

	return;
}


//----------------------------------------------------------------------------
//							Dimension2D Constructors

Dimension2D::Dimension2D(){

	//dimension
	n_width = 0;
	n_height = 0;

	return;
}


Dimension2D::Dimension2D(int width, int height){

	//dimension
	n_width = width;
	n_height = height;

	return;
}


//----------------------------------------------------------------------------
//						Rectangle Vs Point

bool CollisionPointRect(float rect_x, float rect_y, int rect_w, int rect_h,
		float pnt_x, float pnt_y){
	/*
	 * *brief*	This function will return true if the the rectangles overlap
	 *
	 * param	rect_x, rect_y		top left corner of the rectangle
	 * param	rect_w				width of the rectangle
	 * param	rect_h				height of the rectangle
	 *
	 * param	pnt_x, pnt_y		center of the point
	 *
	 * 			This function checks if a point is inside of a rectangle.
	 *			If the point is inside the rectangle it will return true,
	 *			if not it will return false
	 **/




	if(rect_x + (float)rect_w >= pnt_x &&			//right edge
			rect_x <= pnt_x &&						//left edge
			rect_y + (float)rect_h >= pnt_y &&		//top edge
			rect_y <= pnt_y){						//bottom edge

		return true;
	}

	return false;
}


bool CollisionPointRect(const Position2D &rect_p, const Dimension2D &rect_d,
		const Position2D &pnt){
	/*
	 * *brief*	This function will return true if the the point is inside of
	 * 			the rectangle
	 *
	 * param	rect_p	a struct that contains the rectangle's position
	 * param	rect_d	a struct that contains the rectangle's dimension
	 *
	 * param	pnt		a struct that contains the position of the point
	 *
	 * 			This function checks if a point is inside of a rectangle.
	 *			If the point is inside the rectangle it will return true,
	 *			if not it will return false
	 **/




	if(rect_p.f_x + (float)rect_d.n_width >= pnt.f_x &&			//right edge
			rect_p.f_x <= pnt.f_x &&							//left edge
			rect_p.f_y + (float)rect_d.n_height >= pnt.f_y &&	//top edge
			rect_p.f_y <= pnt.f_y){							//bottom edge

		return true;
	}

	return false;
}


//----------------------------------------------------------------------------
//					   Rectangle Vs Rectangle

bool CollisionRectRect(float x1, float y1, int w1, int h1,
		float x2, float y2, int w2, int h2){
	/*
	 * *brief*	This function will return true if the the rectangles overlap
	 *
	 * param	x1,y1	top left corner of rectangle 1
	 * param	w1		width of rectangle 1
	 * param	h1		height of rectangle 1
	 *
	 * param	x2,y2	top left corner of rectangle 2
	 * param	w2		width of rectangle 2
	 * param	h2		height of rectangle 2
	 *
	 * 			This function checks if to rectangle are overlapping or colliding.
	 *			If they are it will return true, if not it will return false
	 **/




	if(x1 + (float)w1 >= x2 && 			//rect1's right edge is pat rect2's left
			x1 <= x2 + (float)w2 &&		//rect1's left edge is past rect2's right
			y1 + (float)h1 >= y2 &&		//rect1's top edge is past rect2's bottom
			y1 <= y2 + (float)h2){		//rect1's bottom edge is past rect2's top

		return true;
	}

	return false;
}


bool CollisionRectRect(const Position2D &rect1_p, const Dimension2D &rect1_d,
		const Position2D &rect2_p, const Dimension2D &rect2_d){
	/*
	 * *brief*	This function will return true if the the rectangles overlap
	 *
	 * param	rect1_p		a struct that contains the first rectangle's position
	 * param	rect1_d		a struct that contains the first rectangle's dimension
	 *
	 * param	rect2_p		a struct that contains the second rectangle's position
	 * param	rect2_d		a struct that contains the second rectangle's dimension
	 *
	 * 			This function checks if to rectangle are overlapping or colliding.
	 *			If they are it will return true, if not it will return false
	 **/




	if(rect1_p.f_x + (float)rect1_d.n_width >= rect2_p.f_x &&			//right edge
			rect1_p.f_x <= rect2_p.f_x + (float)rect2_d.n_width &&		//left edge
			rect1_p.f_y + (float)rect1_d.n_height >= rect2_p.f_y &&		//top edge
			rect1_p.f_y <= rect2_p.f_y + (float)rect2_d.n_height){		//bottom edge

		return true;
	}

	return false;
}


//----------------------------------------------------------------------------
//					Which Edge of Rectangle Vs Rectangle

Side EdgeRectRect(const Position2D &rect1_p, const Dimension2D &rect1_d,
		const Position2D &rect2_p, const Dimension2D &rect2_d){
	/*
	 * *brief*	This function will return which side the rectangles collied,
	 * 			if the the rectangles overlap
	 *
	 * param	rect1_p		a struct that contains the first rectangle's position
	 * param	rect1_d		a struct that contains the first rectangle's dimension
	 *
	 * param	rect2_p		a struct that contains the second rectangle's position
	 * param	rect2_d		a struct that contains the second rectangle's dimension
	 *
	 * retrn	Side	None = 0, Top = 1, Right = 2, Bottom = 3, Left = 4
	 *
	 * 			This function checks if two rectangle are overlapping or
	 * 			colliding. If they are it will return which side of
	 * 			rectangle 1 is colliding with rectangle 2. If they are not
	 * 			overlapping it will return "None" or 0.
	 **/




	//Check if the rectangles overlap
	if(CollisionRectRect(rect1_p, rect1_d, rect2_p, rect2_d)){
		//If they do overlap:
		//first calculate each rectangle's center
		const float rect1_center_x = rect1_p.f_x + (float)rect1_d.n_width/2;
		const float rect1_center_y = rect1_p.f_y + (float)rect1_d.n_height/2;

		const float rect2_center_x = rect2_p.f_x + (float)rect2_d.n_width/2;
		const float rect2_center_y = rect2_p.f_y + (float)rect2_d.n_height/2;

		//Next calculate the distance between each rectangle's center
		//And make the distance relative to rectangle 1's center
		const float f_x_distance = sqrt((rect1_center_x * rect1_center_x) +
				(rect2_center_x * rect2_center_x)) - rect1_center_x;

		const float f_y_distance = sqrt((rect1_center_y * rect1_center_y) +
				(rect2_center_y * rect2_center_y)) - rect1_center_y;

		//Rectangle 1's center
		const float center = 0.0f;

		//Now check which components of rectangle 2 is closer to rectangle 1's center
		if(abs(f_x_distance) < abs(f_y_distance)){
			//Because the x component of rectangle 2 is closer to rectangle 1's center
			//Check if rectangle 2 is to the right or left of rectangle 1's center
			if(f_x_distance < center) return Side::Left;

			else return Side::Right;
		}

		else{
			//Because the y component of rectangle 2 is closer to rectangle 1's center
			//Check if rectangle 2 is above or below rectangle 1's center
			//*Note* values become negative when going above rectangle 1's center
			if(f_y_distance < center) return Side::Top;

			else return Side::Bottom;
		}
	}

	//Because neither rectangles overlap
	return Side::None;
}


//----------------------------------------------------------------------------









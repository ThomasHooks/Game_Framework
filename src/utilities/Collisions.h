//============================================================================
// Name       		: Collisions.h
// Author     		: Thomas Hooks
// Last Modified	: 02/23/2020
//============================================================================




#ifndef COLLISIONS_H_
#define COLLCOLLISIONS_H_


#include "EnumSide.h"


struct Dimension2D {
	/*
	 *	This structure encapsulates the dimension of a 2D entity
	 * 	by storing its width and height
	 */

	int n_width, n_height;		//dimension


	//Constructors
	Dimension2D();
	Dimension2D(int width, int height);
};


//----------------------------------------------------------------------------


struct Position2D {
	/*
	 *	This structure encapsulates the position of a 2D entity
	 * 	by storing its position, velocity, and acceleration
	 */

	float f_x, f_y;				//position

	float f_dx, f_dy;			//velocity

	float f_2dx, f_2dy;			//acceleration


	//Constructors
	Position2D();
	Position2D(float x, float y);
	Position2D(float x, float y,
			float dx, float dy);
	Position2D(float x, float y,
			float dx, float dy, float d2x, float d2y);

};


bool CollisionPointRect(float rect_x,
						float rect_y,
						int rect_w,
						int rect_h,
						float pnt_x,
						float pnt_y);

bool CollisionPointRect(const Position2D &rect_p,
						const Dimension2D &rect_d,
						const Position2D &pnt);


bool CollisionRectRect(float x1,
					   float y1,
					   int w1,
					   int h1,
					   float x2,
					   float y2,
					   int w2,
					   int h2);

bool CollisionRectRect(const Position2D &rect1_p,
					   const Dimension2D &rect1_d,
					   const Position2D &rect2_p,
					   const Dimension2D &rect2_d);


Side EdgeRectRect(float x1,
				  float y1,
				  int w1,
				  int h1,
				  float x2,
				  float y2,
				  int w2,
				  int h2);

Side EdgeRectRect(const Position2D &rect1_p,
				  const Dimension2D &rect1_d,
				  const Position2D &rect2_p,
				  const Dimension2D &rect2_d);


#endif /* COLLISIONS_H_  */





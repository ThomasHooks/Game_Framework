//============================================================================
// Name       		: Position.h
// Author     		: Thomas Hooks
// Last Modified	: 02/22/2020
//============================================================================




#ifndef SRC_POSITION_H_
#define SRC_POSITION_H_



//TODO add operator over loads for Dimension2D and Position2D
//This structure encapsulates the 2D position of an entity

struct Position {

	double x, y;

	Position();
	Position(double x, double y);

	~Position();
};




#endif /* SRC_POSITION_H_ */




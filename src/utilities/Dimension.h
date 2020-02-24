//============================================================================
// Name       		: Dimension.h
// Author     		: Thomas Hooks
// Last Modified	: 02/22/2020
//============================================================================




#ifndef SRC_DIMENSION_H_
#define SRC_DIMENSION_H_



//This structure encapsulates the dimension of a 2D entity by storing its width and height
//TODO add operator over loads for Dimension
struct Dimension {

	int width, height;

	Dimension();
	Dimension(int width, int height);

	~Dimension();
};


#endif /* SRC_DIMENSION_H_ */




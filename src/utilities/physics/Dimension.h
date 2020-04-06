//============================================================================
// Name       		: Dimension.h
// Author     		: Thomas Hooks
// Last Modified	: 03/09/2020
//============================================================================




#ifndef SRC_DIMENSION_H_
#define SRC_DIMENSION_H_



//This structure encapsulates the dimension of a 2D entity
//TODO add operator over loads for Dimension
struct Dimension {

	int width, height;

	Dimension();
	Dimension(int width, int height);

	~Dimension();

	bool operator==(const Dimension& other) const;
	bool operator>(const Dimension& other) const;
	bool operator>=(const Dimension& other) const;
	bool operator<(const Dimension& other) const;
	bool operator<=(const Dimension& other) const;

	bool operator>(int scalar) const;
	bool operator>=(int scalar) const;
	bool operator<(int scalar) const;
	bool operator<=(int scalar) const;

	Dimension operator+(const Dimension& other) const;
	Dimension operator-(const Dimension& other) const;

	Dimension operator+(int scalar) const;
	Dimension operator-(int scalar) const;
	Dimension operator*(int scalar) const;
	Dimension operator/(int scalar) const;
};


#endif /* SRC_DIMENSION_H_ */




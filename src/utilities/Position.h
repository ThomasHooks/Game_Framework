//============================================================================
// Name       		: Position.h
// Author     		: Thomas Hooks
// Last Modified	: 02/27/2020
//============================================================================




#ifndef SRC_POSITION_H_
#define SRC_POSITION_H_



//TODO add more operator overloads for Position
//This structure encapsulates the position of an entity/tile

struct Position {

	double x, y;

	Position();
	Position(double x, double y);

	~Position();

	bool operator==(const Position& other) const;
	bool operator>(const Position& other) const;
	bool operator>=(const Position& other) const;
	bool operator<(const Position& other) const;
	bool operator<=(const Position& other) const;
	bool operator>(int scalar) const;
	bool operator>=(int scalar) const;
	bool operator<(int scalar) const;
	bool operator<=(int scalar) const;

	Position operator+(const Position& other) const;
	Position operator+(double scalar) const;
	Position operator-(const Position& other) const;
	Position operator-(double scalar) const;
	Position operator*(double scalar) const;
};


#endif /* SRC_POSITION_H_ */




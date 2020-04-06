//============================================================================
// Name       		: Position.h
// Author     		: Thomas Hooks
// Last Modified	: 02/29/2020
//============================================================================




#ifndef SRC_POSITION_H_
#define SRC_POSITION_H_




#include "EnumSide.h"



//TODO add more operator overloads for Position
class Position {

public:

	Position();
	Position(double x, double y);

	~Position();

	double xPos(void) const {return x;}
	double yPos(void) const {return y;}

	float xPosF(void) const;
	float yPosF(void) const;

	int xPosN(void) const;
	int yPosN(void) const;

	void move_xPos(double amout);
	void move_yPos(double amout);
	void move(double x, double y);
	void move(const Position &pos);

	void offsetBy(EnumSide direction, double distance);

	bool isPoint(void) const;

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
	Position operator/(double scalar) const;

private:

	double x, y;
};


#endif /* SRC_POSITION_H_ */




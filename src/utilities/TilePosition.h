//============================================================================
// Name       		: TilePosition.h
// Author     		: Thomas Hooks
// Last Modified	: 02/23/2020
//============================================================================




#ifndef SRC_TILEPOSITION_H_
#define SRC_TILEPOSITION_H_




#include "Dimension.h"
#include "EnumSide.h"
#include "Position.h"




class TilePosition {

public:

	TilePosition();
	TilePosition(double x, double y);
	TilePosition(Position positionIn);
	TilePosition(double x, double y, int width, int height);
	TilePosition(Position positionIn, Dimension dimensionIn);


	~TilePosition();

	TilePosition(const TilePosition &other);

	TilePosition(TilePosition &&other);


	double get_xPos(void) const {return this->position.x;}
	double get_yPos(void) const {return this->position.y;}

	float get_xPosF(void);
	float get_yPosF(void);

	int get_xPosN(void);
	int get_yPosN(void);

	void set_position(double x, double y);
	void set_position(const Position &pos);


	int get_width(void) const {return this->dimension.width;}
	int get_height(void) const {return this->dimension.height;}

	void set_dimensions(int width, int height);
	void set_dimensions(const Dimension &dim);

	void offsetBy(Side direction, double distance);

	bool isPoint(void);

private:

	Position position;

	Dimension dimension;
};





#endif /* SRC_TILEPOSITION_H_ */




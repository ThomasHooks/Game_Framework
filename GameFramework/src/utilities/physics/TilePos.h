#ifndef TilePos_H_
#define TilePos_H_


#include "utilities/math/Pos3.hpp"
#include "utilities/math/Pos2.hpp"
#include "utilities/physics/EnumSide.h"




class TilePos 
{
public:

	TilePos();



	TilePos(double xIn, double yIn, double zIn = 0.0);



	TilePos(const Pos3D& posIn);



	TilePos(const Pos2D& posIn);



	TilePos(const Pos2N& posIn);



	TilePos(const TilePos& other);



	/// <summary>
	/// Gets this tile position's x coordinate
	/// </summary>
	/// <returns></returns>
	double x() const { return m_pos.x; }



	/// <summary>
	/// Gets this tile position's x coordinate
	/// </summary>
	/// <returns></returns>
	int xN() const;



	/// <summary>
	/// Gets this tile position's y coordinate
	/// </summary>
	/// <returns></returns>
	double y() const { return m_pos.y; }



	/// <summary>
	/// Gets this tile position's x coordinate
	/// </summary>
	/// <returns></returns>
	int yN() const;



	/// <summary>
	/// Gets this tile position's z coordinate
	/// </summary>
	/// <returns></returns>
	double z() const { return m_pos.z; }



	/// <summary>
	/// Gets this tile position's x coordinate
	/// </summary>
	/// <returns></returns>
	int zN() const;



	/// <summary>
	/// Changes this tile position to the specified coordinates
	/// </summary>
	/// <param name="xIn">This tile position's x coordinate</param>
	/// <param name="yIn">This tile position's y coordinate</param>
	/// <param name="zIn">This tile position's z coordinate</param>
	void set(double xIn, double yIn, double zIn);



	/// <summary>
	/// Changes this tile position to the specified coordinates
	/// </summary>
	/// <param name="xIn">This tile position's x coordinate</param>
	/// <param name="yIn">This tile position's y coordinate</param>
	void set(double xIn, double yIn);



	/// <summary>
	/// Changes this tile position to the specified coordinates
	/// </summary>
	/// <param name="posIn">Specifies the new coordinates</param>
	void set(const Pos3D& posIn);



	/// <summary>
	/// Changes this tile's position to the specified coordinates
	/// </summary>
	/// <param name="posIn">Specifies the new coordinates</param>
	void set(const Pos2D& posIn);



	/// <summary>
	/// Changes this tile's position to the specified coordinates
	/// </summary>
	/// <param name="posIn">Specifies the new coordinates</param>
	void set(const Pos2N& posIn);



	/// <summary>
	/// Offset this tile's position by the specified amount
	/// </summary>
	/// <param name="xIn">This tile position's x coordinate</param>
	/// <param name="yIn">This tile position's y coordinate</param>
	/// <param name="zIn">This tile position's z coordinate</param>
	void move(double xIn, double yIn, double zIn);



	/// <summary>
	/// Offset this tile's position by the specified amount
	/// </summary>
	/// <param name="xIn">This tile position's x coordinate</param>
	/// <param name="yIn">This tile position's y coordinate</param>
	void move(double xIn, double yIn);



	/// <summary>
	/// Offset this tile's position by the specified amount
	/// </summary>
	/// <param name="posIn">Specifies the amount to offset by</param>
	void move(const Pos3D& posIn);



	/// <summary>
	/// Offset this tile's position by the specified amount
	/// </summary>
	/// <param name="posIn">Specifies the amount to offset by</param>
	void move(const Pos2D& posIn);



	/// <summary>
	/// Offset this tile's position by the specified amount
	/// </summary>
	/// <param name="posIn">Specifies the amount to offset by</param>
	void move(const Pos2N& posIn);



	/// <summary>
	/// Offset this tile's position by the specified amount and direction
	/// </summary>
	/// <param name="directionIn">Specifies the direction of the offset</param>
	/// <param name="distanceIn">Specifies the amount to offset by</param>
	void move(EnumSide directionIn, double distanceIn);



	TilePos operator+(const TilePos& other) const;



	TilePos& operator+=(const TilePos& other);



	TilePos operator-(const TilePos& other) const;



	TilePos& operator-=(const TilePos& other);



	bool operator==(const TilePos& other) const;



	bool operator>(const TilePos& other) const;



	bool operator>=(const TilePos& other) const;



	bool operator<(const TilePos& other) const;



	bool operator<=(const TilePos& other) const;



private:

	Pos3D m_pos;
}; 


#endif /* TilePos_H_ */




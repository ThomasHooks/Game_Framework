#include <cstdlib>

#include "TilePos.h"




TilePos::TilePos() 
	: m_pos(0.0, 0.0, 0.0)
{}



TilePos::TilePos(double xIn, double yIn, double zIn)
	: m_pos(xIn, yIn, zIn)
{}



TilePos::TilePos(const Pos3D & posIn)
	: m_pos(posIn.x, posIn.y, posIn.z)
{}



TilePos::TilePos(const Pos2D& posIn)
	: m_pos(posIn.x, posIn.y, 0.0)
{}



TilePos::TilePos(const Pos2N & posIn)
	: m_pos(posIn.x, posIn.y, 0.0)
{}



TilePos::TilePos(const TilePos& other)
{
	if (this != &other)
	{
		m_pos.x = other.m_pos.x;
		m_pos.y = other.m_pos.y;
		m_pos.z = other.m_pos.z;
	}
}



int TilePos::xN() const
{
	return static_cast<int>(m_pos.x + 0.5);
}



int TilePos::yN() const
{
	return static_cast<int>(m_pos.y + 0.5);
}



int TilePos::zN() const
{
	return static_cast<int>(m_pos.z + 0.5);
}



void TilePos::set(double xIn, double yIn, double zIn)
{
	m_pos.x = xIn;
	m_pos.y = yIn;
	m_pos.z = zIn;
}



void TilePos::set(double xIn, double yIn)
{
	m_pos.x = xIn;
	m_pos.y = yIn;
}



void TilePos::set(const Pos3D& posIn)
{
	m_pos.x = posIn.x;
	m_pos.y = posIn.y;
	m_pos.z = posIn.z;
}



void TilePos::set(const Pos2D& posIn)
{
	m_pos.x = posIn.x;
	m_pos.y = posIn.y;
}



void TilePos::set(const Pos2N& posIn)
{
	m_pos.x = posIn.x;
	m_pos.y = posIn.y;
}



void TilePos::move(double xIn, double yIn, double zIn)
{
	m_pos.x += xIn;
	m_pos.y += yIn;
	m_pos.z += zIn;
}



void TilePos::move(double xIn, double yIn)
{
	m_pos.x += xIn;
	m_pos.y += yIn;
}



void TilePos::move(const Pos3D& posIn)
{
	m_pos.x += posIn.x;
	m_pos.y += posIn.y;
	m_pos.z += posIn.z;
}



void TilePos::move(const Pos2D& posIn)
{
	m_pos.x += posIn.x;
	m_pos.y += posIn.y;
}



void TilePos::move(const Pos2N& posIn)
{
	m_pos.x += posIn.x;
	m_pos.y += posIn.y;
}



void TilePos::move(EnumSide directionIn, double distanceIn)
{
	switch (directionIn)
	{
	case EnumSide::NONE:
		break;

	case EnumSide::UP:
		m_pos.y -= std::abs(distanceIn);
		break;

	case EnumSide::RIGHT:
		m_pos.x += std::abs(distanceIn);
		break;

	case EnumSide::DOWN:
		m_pos.y += std::abs(distanceIn);
		break;

	case EnumSide::LEFT:
		m_pos.x -= std::abs(distanceIn);
		break;
	}
}



TilePos TilePos::operator+(const TilePos& other) const
{
	return TilePos(m_pos.x + other.m_pos.x, m_pos.y + other.m_pos.y, m_pos.z + other.m_pos.z);
}



TilePos& TilePos::operator+=(const TilePos& other)
{
	m_pos.x += other.m_pos.x;
	m_pos.y += other.m_pos.y;
	m_pos.z += other.m_pos.z;
	return *this;
}



TilePos TilePos::operator-(const TilePos& other) const
{
	return TilePos(m_pos.x - other.m_pos.x, m_pos.y - other.m_pos.y, m_pos.z - other.m_pos.z);
}



TilePos& TilePos::operator-=(const TilePos& other)
{
	m_pos.x -= other.m_pos.x;
	m_pos.y -= other.m_pos.y;
	m_pos.z -= other.m_pos.z;
	return *this;
}



bool TilePos::operator==(const TilePos& other) const
{
	return m_pos.x == other.m_pos.x && m_pos.y == other.m_pos.y && m_pos.z == other.m_pos.z;
}



bool TilePos::operator>(const TilePos& other) const
{
	return m_pos.x > other.m_pos.x && m_pos.y > other.m_pos.y && m_pos.z > other.m_pos.z;
}



bool TilePos::operator>=(const TilePos& other) const
{
	return m_pos.x >= other.m_pos.x && m_pos.y >= other.m_pos.y && m_pos.z >= other.m_pos.z;
}



bool TilePos::operator<(const TilePos& other) const
{
	return m_pos.x < other.m_pos.x && m_pos.y < other.m_pos.y && m_pos.z < other.m_pos.z;
}



bool TilePos::operator<=(const TilePos& other) const
{
	return m_pos.x <= other.m_pos.x && m_pos.y <= other.m_pos.y && m_pos.z <= other.m_pos.z;
}








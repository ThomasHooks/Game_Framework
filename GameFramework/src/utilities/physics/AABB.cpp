#include <algorithm>

#include "AABB.h"





AABB::AABB()
	: m_pos1(0.0, 0.0), m_pos2(0.0, 0.0)
{}



AABB::AABB(double x1, double y1, double x2, double y2)
	: m_pos1(x1, y1), m_pos2(x2, y2) 
{}



double AABB::width() const 
{
	return std::abs(m_pos2.x - m_pos1.x);
}



int AABB::widthN() const 
{
	return static_cast<int>(this->width() + 0.5);
}



double AABB::height() const 
{
	return std::abs(m_pos2.y - m_pos1.y);
}



int AABB::heightN() const 
{
	return static_cast<int>(this->height() + 0.5);
}



Pos2D AABB::getCenter() const
{
	double width = this->width();
	double height = this->height();
	return Pos2D(m_pos1.x + width/2.0, m_pos1.y + height/2.0);
}



const Pos2D& AABB::getPos() const
{
	return m_pos1;
}



void AABB::grow(double amount)
{
	double delta = std::abs(amount);
	m_pos1 += -delta;
	m_pos2 += delta;
}



void AABB::shrink(double amount)
{
	double delta = std::abs(amount);
	Pos2D center = this->getCenter();
	//This is done so that the corners of the AABB do not flip
	this->width() < delta ? m_pos1.x += center.x : m_pos1.x += delta;
	this->width() < delta ? m_pos2.x += center.x : m_pos2.x += -delta;
	this->width() < delta ? m_pos1.y += center.y : m_pos1.y += delta;
	this->width() < delta ? m_pos2.y += center.y : m_pos2.y += -delta;
}



void AABB::modify(EnumSide direction, double amount)
{
	double delta = std::abs(amount);
	switch (direction)
	{
	case EnumSide::UP:
		m_pos1.y += -delta;
		break;

	case EnumSide::RIGHT:
		m_pos2.x += delta;
		break;

	case EnumSide::DOWN:
		m_pos2.y += delta;
		break;

	case EnumSide::LEFT:
		m_pos1.x += -delta;
		break;

	default:
		break;
	}
}



void AABB::offset(double x, double y)
{
	m_pos1.x += x;
	m_pos2.x += x;
	m_pos1.y += y;
	m_pos2.y += y;
}



void AABB::offset(const Pos3D& posIn)
{
	this->offset(posIn.x, posIn.y);
}



void AABB::nudge(EnumSide direction, double amount)
{
	double delta = std::abs(amount);
	switch (direction)
	{
	case EnumSide::UP:
		m_pos1.y += -delta;
		m_pos2.y += -delta;
		break;

	case EnumSide::RIGHT:
		m_pos1.x += delta;
		m_pos2.x += delta;
		break;

	case EnumSide::DOWN:
		m_pos1.y += delta;
		m_pos2.y += delta;
		break;

	case EnumSide::LEFT:
		m_pos1.x += -delta;
		m_pos2.x += -delta;
		break;
	}
}



bool AABB::isPoint() const 
{
	return m_pos1 == m_pos2;
}








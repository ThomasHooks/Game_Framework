#include <cstdlib>

#include "SpriteLocation.hpp"




SpriteLocation::SpriteLocation(const std::string& tagIn, const Pos2N& indexIn)
	: m_index(indexIn), m_tag(tagIn)
{}



void SpriteLocation::setIndex(const Pos2N& indexIn)
{
	if (m_index != indexIn)
	{
		m_index.u = std::abs(indexIn.u);
		m_index.v = std::abs(indexIn.v);
	}
}








#include <cstdlib>

#include "renderer/texture/SpriteLocation.hpp"




SpriteLocation::SpriteLocation(const std::string& tagIn, const Pos2N& posIn)
	: m_index(posIn), m_tag(tagIn)
{}



SpriteLocation::SpriteLocation(const std::string & tagIn, int uIn, int vIn)
	: m_index(uIn, vIn), m_tag(tagIn)
{}



void SpriteLocation::setIndex(const Pos2N& indexIn)
{
	if (m_index != indexIn)
	{
		indexIn.u < 0 ? m_index.u = 0 : m_index.u = indexIn.u;
		indexIn.v < 0 ? m_index.v = 0 : m_index.v = indexIn.v;
	}
}








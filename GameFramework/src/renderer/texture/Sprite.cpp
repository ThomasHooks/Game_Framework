#include <cstdlib>

#include "renderer/texture/Sprite.hpp"




Sprite::Sprite(const std::string& tagIn, const Pos2N& sizeIn)
	: size(sizeIn), index(), fliped(Flip::NONE), m_tag(tagIn)
{
}



Sprite::Sprite(const std::string & tagIn, const Pos2N & sizeIn, const Pos2N & indexIn)
	: size(sizeIn), index(indexIn), fliped(Flip::NONE), m_tag(tagIn)
{
}



const std::string& Sprite::tag() const
{
	return m_tag;
}








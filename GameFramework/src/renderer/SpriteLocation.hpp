#ifndef SpriteLocation_HPP_
#define SpriteLocation_HPP_

#include <string>

#include "utilities/math/Pos2.hpp"




class SpriteLocation 
{
public:

	SpriteLocation(const std::string& tagIn, const Pos2N& indexIn);



	const Pos2N& getIndex() const { return m_index; }



	const std::string& getTag() const { return m_tag; }



	void setIndex(const Pos2N& indexIn);



private:

	std::string m_tag;

	Pos2N m_index;
}; 


#endif




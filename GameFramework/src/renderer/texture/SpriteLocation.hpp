#ifndef SpriteLocation_HPP_
#define SpriteLocation_HPP_

#include <string>

#include "utilities/math/Pos2.hpp"




class SpriteLocation 
{
public:

	/// <summary>
	/// 
	/// </summary>
	/// <param name="tagIn"></param>
	/// <param name="posIn"></param>
	SpriteLocation(const std::string& tagIn, const Pos2N& posIn);



	SpriteLocation(const std::string& tagIn, int uIn, int vIn);



	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	const Pos2N& getIndex() const { return m_index; }



	/// <summary>
	/// 
	/// </summary>
	/// <param name="indexIn"></param>
	void setIndex(const Pos2N& indexIn);



	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	const std::string& tag() const { return m_tag; }



private:

	std::string m_tag;

	Pos2N m_index;
}; 


#endif




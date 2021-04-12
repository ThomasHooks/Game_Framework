#ifndef Sprite_HPP_
#define Sprite_HPP_

#include <string>

#include "utilities/math/Pos2.hpp"




class Sprite 
{
public:

	enum struct Flip : unsigned char
	{
		NONE = 0,
		HORIZONTAL,
		VERTICAL
	};



	/// <summary>
	/// 
	/// </summary>
	/// <param name="tagIn"></param>
	/// <param name="sizeIn"></param>
	Sprite(const std::string& tagIn, const Pos2N& sizeIn);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="tagIn"></param>
	/// <param name="sizeIn"></param>
	/// <param name="indexIn"></param>
	Sprite(const std::string& tagIn, const Pos2N& sizeIn, const Pos2N& indexIn);



	/// <summary>
	/// Gets this sprite's sprite sheet identifier 
	/// </summary>
	/// <returns></returns>
	const std::string& tag() const;



	Pos2N size;



	/// <summary>
	/// Specifies the sprite's location inside of the sprite sheet
	/// </summary>
	Pos2N index;



	float scale = 1.0f;



	Flip fliped;



private:

	std::string m_tag;
}; 


#endif




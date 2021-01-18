#ifndef Capabilities_HPP_
#define Capabilities_HPP_


#include <string>

#include "entities/capabilities/ICapability.hpp"
#include "utilities/math/Pos2.hpp"
#include "utilities/physics/AxisAlignedBB.h"
#include "utilities/physics/EnumSide.h"
#include "renderer/texture/SpriteLocation.hpp"




/// <summary>
/// This Capability gives an Entity the ability to have a 2-dimensional position
/// <para>
/// Note: this Capability is required for all Entities, and if removed will cause undefined behavior
/// </para>
/// </summary>
class PositionCapability : public ICapability<PositionCapability>
{
public:

	/// <summary>
	/// The 2-dimensional position for this Entity
	/// </summary>
	Pos2D pos;



	PositionCapability(double xIn, double yIn)
		: ICapability(), pos(xIn, yIn)
	{}



	operator Pos2D() { return pos; }



	operator const Pos2D() const { return pos; }
};



/// <summary>
/// This Capability gives an Entity the ability to have a text unique identifier
/// <para>
/// Note: this Capability is required for all Entities, and if removed will cause undefined behavior
/// </para>
/// </summary>
class TagCapability : public ICapability<TagCapability>
{
public:

	TagCapability(const std::string& tagIn)
		: ICapability(), m_tag(tagIn)
	{}



	/// <summary>
	/// Gets this Entity's text unique identifier
	/// </summary>
	/// <returns></returns>
	const std::string& tag() const { return m_tag; }



private:

	std::string m_tag;
};



/// <summary>
/// This Capability gives an Entity the ability to movie in 2-dimensional space
/// </summary>
/// <param name="dxIn">Specifies the initial "X" component of this Entity's velocity vector</param>
/// <param name="dyIn">Specifies the initial "Y" component of this Entity's velocity vector</param>
class KinematicCapability : public ICapability<KinematicCapability>
{
public:

	/// <summary>
	/// This Entity's current velocity
	/// </summary>
	Pos2D velocity;



	KinematicCapability()
		: ICapability(), velocity()
	{}



	KinematicCapability(double dxIn, double dyIn)
		: ICapability(), velocity(dxIn, dyIn)
	{}



	KinematicCapability(Pos2D& velocityIn)
		: ICapability(), velocity(velocityIn)
	{}
};



/// <summary>
/// This Capability gives an Entity the ability to face towards a direction in 2-dimensional space
/// </summary>
/// <param name="facingIn">Specifies what direction the Entity should be pointing towards initially</param>
class FacingCapability : public ICapability<FacingCapability>
{
public:

	/// <summary>
	/// The direction in 2-dimensional space that this Entity is pointing towards
	/// </summary>
	EnumSide facing;



	FacingCapability(EnumSide facingIn)
		: ICapability(), facing(facingIn)
	{}
};



/// <summary>
/// This Capability gives an Entity the ability to have Axis-Aligned Bounding Box collisions
/// <para>
/// The coordinates given should be relative to this Entity position, which is located in the top-left corner
/// </para>
/// <para>
/// For example, if an Entity is occupying a 32x32px space it would be (0.0, 0.0, 32.0, 32.0)
/// </para>
/// </summary>
/// <param name="x1">Specifies the "X" coordinates of the top-left point</param>
/// <param name="y1">Specifies the "Y" coordinates of the top-left point</param>
/// <param name="x2">Specifies the "X" coordinates of the bottom-right point</param>
/// <param name="y2">Specifies the "Y" coordinates of the bottom-right point</param>
class ColliderCapability : public ICapability<ColliderCapability>
{
public:

	ColliderCapability(double x1, double y1, double x2, double y2)
		: ICapability(), aabb(x1, y1, x2, y2)
	{}



	/// <summary>
	/// The Axis-Aligned Bounding Box for this Entity
	/// </summary>
	AxisAlignedBB aabb;
};



/// <summary>
/// This Capability gives an Entity the ability to be rendered as a 2-dimensional sprite
/// </summary>
/// <param name="tagIn">Specifies the texture atlas/sprite sheet's name</param>
/// <param name="uIn">Specifies the "X" coordinate of the sprite's top-left corner</param>
/// <param name="vIn">Specifies the "Y" coordinate of the sprite's top-left corner</param>
/// <param name="wIn">Specifies the width of the sprite</param>
/// <param name="hIn">Specifies the height of the sprite</param>
class RenderableCapability : ICapability<RenderableCapability> 
{
public:

	/// <summary>
	/// Specifies the dimensions of this Entity's sprite
	/// </summary>
	Pos2N size;



	/// <summary>
	/// Specifies both the texture atlas this Entity uses, and the texture's coordinates within the atlas
	/// </summary>
	SpriteLocation sprite;



	RenderableCapability(SpriteLocation& spriteIn, Pos2N& sizeIn)
		: ICapability(), size(sizeIn), sprite(spriteIn) 
	{}



	RenderableCapability(const std::string& tagIn, int uIn, int vIn, int wIn, int hIn)
		: ICapability(), size(wIn, hIn), sprite(tagIn, uIn, vIn)
	{}
};


#endif /* Capabilities_HPP_ */




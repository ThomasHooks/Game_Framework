#ifndef Capabilities_HPP_
#define Capabilities_HPP_


#include <string>

#include "entities/capabilities/ICapability.hpp"
#include "utilities/math/Pos2.hpp"
#include "utilities/physics/AxisAlignedBB.h"
#include "utilities/physics/EnumSide.h"
#include "renderer/texture/Sprite.hpp"




/// <summary>
/// This Capability gives an Entity the ability to have a 2-dimensional position
/// <para>
/// Note: this Capability is required for all Entities, and if removed will cause undefined behavior
/// </para>
/// </summary>
class PositionCapability : public ICapability<PositionCapability>
{
public:

	PositionCapability(double xIn, double yIn)
		: ICapability(), pos(xIn, yIn)
	{}



	Pos2D pos;



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

	KinematicCapability()
		: ICapability(), velocity()
	{}



	KinematicCapability(double dxIn, double dyIn)
		: ICapability(), velocity(dxIn, dyIn)
	{}



	KinematicCapability(Pos2D& velocityIn)
		: ICapability(), velocity(velocityIn)
	{}



	/// <summary>
	/// This Entity's current velocity
	/// </summary>
	Pos2D velocity;
};



/// <summary>
/// This Capability gives an Entity the ability to face towards a direction in 2-dimensional space
/// </summary>
/// <param name="facingIn">Specifies what direction the Entity should be pointing towards initially</param>
class FacingCapability : public ICapability<FacingCapability>
{
public:

	FacingCapability(EnumSide facingIn)
		: ICapability(), facing(facingIn)
	{}



	/// <summary>
	/// The direction in 2-dimensional space that this Entity is pointing towards
	/// </summary>
	EnumSide facing;
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
/// This Capability gives an Entity the ability of a rigid-body, i.e. the ability to both movie in 2-dimensional space and collide with other rigid-bodies.
/// <para>
/// The coordinates of the Axis-Aligned Bounding Box should be relative to this Entity position, which is located in the top-left corner 
/// For example, if an Entity is occupying a 32x32px space it would be (0.0, 0.0, 32.0, 32.0).
/// </para>
/// <para>
/// When creating a rigid-body the mass should be specified in its non-inverse amount, and if the Entity has infinite mass use 0.0f 
/// </para>
/// </summary>
/// <param name="velocityIn">Specifies the initial velocity vector of this Entity</param>
/// <param name="aabbIn">Specifies the Axis-Aligned Bounding Box of this Entity</param>
/// <param name="frictionIn">Specifies the initial friction of this Entity</param>
/// <param name="massIn">Specifies the initial mass of this Entity</param>
class RigidbodyCapability : ICapability<RigidbodyCapability>
{
public:

	RigidbodyCapability(const AxisAlignedBB& aabbIn, float massIn, float frictionIn = 1.0f)
		: acceleration(), velocity(), aabb(aabbIn), friction(frictionIn), inverseMass(0.0f)
	{
		if (massIn != 0.0f)
			inverseMass = 1.0f / massIn;
	}



	RigidbodyCapability(const Pos2D& velocityIn, const AxisAlignedBB& aabbIn, float massIn, float frictionIn = 1.0f)
		: acceleration(), velocity(velocityIn), aabb(aabbIn), friction(frictionIn), inverseMass(0.0f)
	{
		if (massIn != 0.0f)
			inverseMass = 1.0f / massIn;
	}



	Pos2D acceleration;



	Pos2D velocity;



	/// <summary>
	/// The Axis-Aligned Bounding Box for this Entity
	/// </summary>
	AxisAlignedBB aabb;



	float friction;



	float inverseMass;
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

	RenderableCapability(Sprite& spriteIn, Pos2N& sizeIn)
		: ICapability(), size(sizeIn), sprite(spriteIn)
	{}



	/// <summary>
	/// Specifies the dimensions of this Entity's sprite
	/// </summary>
	Pos2N size;



	/// <summary>
	/// Specifies both the texture atlas this Entity uses, and the texture's coordinates within the atlas
	/// </summary>
	Sprite sprite;
};



class TickableCapability : ICapability<TickableCapability>
{
public:

	TickableCapability()
		: ICapability()
	{}
};


#endif /* Capabilities_HPP_ */




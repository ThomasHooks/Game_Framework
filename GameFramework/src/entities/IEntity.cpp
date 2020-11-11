#include "IEntity.hpp"




IEntity::IEntity()
	: tag("null"), entityID(0), active(true), solid(true), m_pos(), m_lastPos(), m_vel(), hitBox(), m_sprite(), type(EnumEntityType::PASSIVE), facing(EnumSide::RIGHT)
{}



IEntity::~IEntity() 
{}



void IEntity::spwan(const TilePos& posIn, EnumSide facingIn, unsigned int entityIDIn)
{
	this->teleport(posIn);
	this->setDirectionFacing(facingIn);
	this->entityID = entityIDIn;
	this->onSpwan();
}



const std::string& IEntity::getRegistryTag() const 
{
	return this->tag;
}



unsigned int IEntity::getID() const
{
	return this->entityID;
}



bool IEntity::isActive() const 
{
	return this->active;
}



void IEntity::markInactive() 
{
	this->active = false;
}



bool IEntity::canCollide() const 
{
	return this->solid;
}



EnumEntityType IEntity::getType() const 
{
	return this->type;
}



bool IEntity::isPassive()const 
{
	return this->type == EnumEntityType::PASSIVE;
}



bool IEntity::isNeutral() const 
{
	return this->type == EnumEntityType::NEUTRAL;
}



bool IEntity::isAggressive() const 
{
	return this->type == EnumEntityType::AGGRESSIVE;
}



bool IEntity::isPlayer() const 
{
	return this->type == EnumEntityType::PLAYER;
}



EnumEntityType IEntity::directionFacing() const 
{
	return this->type;
}



const AABB& IEntity::getAabb() const 
{
	return this->hitBox;
}



void IEntity::teleport(const TilePos& posIn)
{
	double xPos = posIn.x() - this->getPos().x();
	double yPos = posIn.y() - this->getPos().y();
	m_pos.set(xPos, yPos);
	this->hitBox.offset(xPos, yPos);
}



bool IEntity::isMoving() const 
{
	return m_vel + 0.5 > 0;
}



void IEntity::setDirectionFacing(EnumSide facingIn)
{
	this->facing = facingIn;
}



bool IEntity::hasCapability(const std::string &stateTag)
{
	return this->states.count(stateTag) > 0;
}



void IEntity::updateVel(const Pos2D& accel, float frict, float deltaTime)
{
	float deltaFrict = std::abs(frict);
	if (deltaFrict < 0.0f) 
		deltaFrict = 0.0f;
	else if (deltaFrict > 1.0f) 
		deltaFrict = 1.0f;
	m_vel += (accel * deltaTime * deltaFrict);
}



void IEntity::setRegistryTag(const std::string &tagIn)
{
	this->tag = tagIn;
}



void IEntity::setSprite(const Pos2N& spriteIn)
{
	m_sprite.x = spriteIn.x;
	m_sprite.y = spriteIn.y;
}



void IEntity::setEntityType(EnumEntityType typeIn)
{
	this->type = typeIn;
}



void IEntity::setAabb(double x1, double y1, double x2, double y2)
{
	this->hitBox.offset(std::abs(x1), std::abs(y1));
	this->hitBox.modify(EnumSide::RIGHT, std::abs(x2));
	this->hitBox.modify(EnumSide::DOWN, std::abs(y2));
}



void IEntity::updatePos(float frict, float deltaTime)
{
	float delta = std::abs(frict);
	if (delta < 0.0f) 
		delta = 0.0f;
	else if (delta > 1.0f) 
		delta = 1.0f;

	m_lastPos = m_pos;
	m_pos.move(m_vel * deltaTime);

	//Move AABB with this Entity
	this->hitBox.offset(m_pos.x() - m_lastPos.x(), m_pos.y() - m_lastPos.y());
	//Add dynamic friction to the Entity to slow it down
	m_vel *= delta;
}








#ifndef Entity_HPP_
#define Entity_HPP_


#include <memory>

#include <entt/entt.hpp>

#include "utilities/Assertions.h"
#include "entities/capabilities/Capabilities.hpp"




class Entity
{
public:

	Entity(std::shared_ptr<entt::registry>& registryIn, entt::entity idIn)
		: m_id(idIn), m_registry(registryIn)
	{}



	Entity(const Entity& other)
	{
		m_id = other.m_id;
		m_registry = other.m_registry;
	}



	Entity(Entity&& other) noexcept
	{
		m_id = other.m_id;
		other.m_id = entt::null;
		m_registry = other.m_registry;
	}



	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns></returns>
	template<typename Capability>
	bool has() const
	{
		auto reg = m_registry.lock();
		GAME_ASSERT(reg != nullptr);
		return reg->has<Capability>(m_id);
	}



	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns></returns>
	template<typename Capability>
	Capability& get()
	{
		GAME_ASSERT(has<Capability>());
		return m_registry.lock()->get<Capability>(m_id);
	}



	template<typename Capability>
	const Capability& get() const
	{
		GAME_ASSERT(!has<Capability>());
		return m_registry.lock()->get<Capability>(m_id);
	}



	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="...Args"></typeparam>
	/// <param name="...args"></param>
	/// <returns></returns>
	template<typename Capability, typename... Args>
	Entity& add(Args&&... args)
	{
		GAME_ASSERT(!has<Capability>());
		m_registry.lock()->emplace<Capability>(m_id, std::forward<Args>(args)...);
		return *this;
	}



	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns></returns>
	template<typename Capability>
	Entity& remove()
	{
		GAME_ASSERT(!has<Capability>());
		m_registry.lock()->remove<Capability>(m_id);
		return *this;
	}



	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	inline Pos2D& pos()
	{
		return get<PositionCapability>().pos;
	}



	inline const Pos2D& pos() const
	{
		return get<PositionCapability>().pos;
	}



	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	inline const std::string& tag() const
	{
		return get<TagCapability>().tag();
	}



	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	entt::entity guid() const { return m_id; }


	
	/// <summary>
	/// 
	/// </summary>
	/// <param name="vec"></param>
	/// <param name="frict"></param>
	/// <param name="deltaTime"></param>
	inline void movePos(const Pos2D& vec, float frict, float deltaTime)
	{
		if (has<KinematicCapability>())
		{
			float deltaFrict = std::abs(frict);
			if (deltaFrict < 0.0f)
				deltaFrict = 0.0f;
			else if (deltaFrict > 1.0f)
				deltaFrict = 1.0f;

			KinematicCapability& kinCap = get<KinematicCapability>();
			kinCap.velocity += vec * deltaFrict * deltaTime;
		}
	}



	/// <summary>
	/// 
	/// </summary>
	/// <param name="frict"></param>
	/// <param name="deltaTime"></param>
	inline void updatePos(float frict, float deltaTime)
	{
		if (has<KinematicCapability>())
		{
			float deltaFrict = std::abs(frict);
			if (deltaFrict < 0.0f)
				deltaFrict = 0.0f;
			else if (deltaFrict > 1.0f)
				deltaFrict = 1.0f;

			Pos2D& vec = get<KinematicCapability>().velocity;
			Pos2D& pos = this->pos();
			Pos2D deltaPos = vec * deltaTime;
			pos += deltaPos;
			vec *= deltaFrict;

			if (has<ColliderCapability>())
			{
				AxisAlignedBB& aabb = get<ColliderCapability>().aabb;
				aabb.offset(deltaPos.x, deltaPos.y);
			}
		}
	}



private:

	entt::entity m_id;

	std::weak_ptr<entt::registry> m_registry;
};


#endif /* Entity_HPP_ */




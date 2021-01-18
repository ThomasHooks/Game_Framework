#ifndef EntityJournal_HPP_
#define EntityJournal_HPP_


#include <memory>
#include <functional>
#include <string>
#include <vector>
#include <unordered_map>

#include <entt/entt.hpp>

#include "utilities/Loggers.hpp"
#include "entities/Entity.hpp"




class EntityJournal
{
	using Callback = std::function<void(Entity&)>;

public:

	EntityJournal();



	~EntityJournal();



	/// <summary>
	/// 
	/// </summary>
	/// <param name="tag"></param>
	/// <param name="pos"></param>
	/// <returns></returns>
	Entity spawn(std::string tag, const struct Pos2D& pos);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	Entity spawn(const struct Pos2D& pos);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="entity"></param>
	void despawn(Entity& entity);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="entity"></param>
	void despawn(entt::entity entity);



	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="entity"></param>
	/// <returns></returns>
	template<typename... Capability>
	auto get(entt::entity entity)
	{
		return m_entityRegistry->try_get<Capability...>(entity);
	}



	template<typename... Capability>
	auto get(entt::entity entity) const
	{
		return m_entityRegistry->try_get<Capability...>(entity);
	}



	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="Capability"></typeparam>
	/// <param name="entity"></param>
	template<typename Capability>
	void remove(entt::entity entity)
	{
		m_entityRegistry->remove_if_exists<Capability>(entity);
	}



	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="...Capability"></typeparam>
	/// <typeparam name="...Exclude"></typeparam>
	/// <param name=""></param>
	/// <returns></returns>
	template<typename... Capability, typename... Exclude>
	entt::basic_view<entt::entity, entt::exclude_t<Exclude...>, Capability...> view(entt::exclude_t<Exclude...> = {})
	{
		return m_entityRegistry->view<Capability...>(entt::exclude_t<Exclude...>);
	}



	template<typename... Capability, typename... Exclude>
	entt::basic_view<entt::entity, entt::exclude_t<Exclude...>, Capability...> view(entt::exclude_t<Exclude...> = {}) const
	{
		return m_entityRegistry->view<Capability...>(entt::exclude_t<Exclude...>);
	}



	/// <summary>
	/// 
	/// </summary>
	/// <param name="area"></param>
	/// <returns></returns>
	std::vector<Entity> getEntities(const class AxisAlignedBB& area);



	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	size_t count() const;



	/// <summary>
	/// 
	/// </summary>
	/// <param name="tagIn"></param>
	/// <param name="callbackIn"></param>
	void registerSpawner(const std::string& tagIn, Callback callbackIn);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="tagIn"></param>
	/// <param name="callbackIn"></param>
	void registerOnSpawn(const std::string& tagIn, Callback callbackIn);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="tagIn"></param>
	/// <param name="callbackIn"></param>
	void registerOnDespawn(const std::string& tagIn, Callback callbackIn);



private:

	std::shared_ptr<spdlog::logger> m_logger;

	std::shared_ptr<entt::registry> m_entityRegistry;

	std::unordered_map<std::string, Callback> m_entityFactoryRegistry;

	std::unordered_map<std::string, Callback> m_onSpawnRegistry;

	std::unordered_map<std::string, Callback> m_onDespawnRegistry;
};


#endif /* EntityJournal_HPP_ */




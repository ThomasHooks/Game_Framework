#include "EntityJournal.hpp"
#include "utilities/physics/Collisions.h"




EntityJournal::EntityJournal()
{
	m_entityRegistry = std::make_shared<entt::registry>();
	m_logger = Loggers::getLog();
	m_logger->info("Entity Journal has been initialized");
}



EntityJournal::~EntityJournal()
{
	m_logger->info("Entity Journal stopped");
}



Entity EntityJournal::spawn(std::string tag, const Pos2D& pos)
{
	Entity entity(m_entityRegistry, m_entityRegistry->create());
	m_entityRegistry->emplace<PositionCapability>(entity.guid(), pos.x, pos.y);
	m_entityRegistry->emplace<TagCapability>(entity.guid(), tag);

	if (m_entityFactoryRegistry.find(tag) != m_entityFactoryRegistry.end())
		m_entityFactoryRegistry[tag](entity);

	if (m_onSpawnRegistry.find(tag) != m_onSpawnRegistry.end())
		m_onSpawnRegistry[tag](entity);

	return entity;
}



Entity EntityJournal::spawn(const Pos2D& pos)
{
	Entity entity(m_entityRegistry, m_entityRegistry->create());
	m_entityRegistry->emplace<PositionCapability>(entity.guid(), pos.x, pos.y);
	m_entityRegistry->emplace<TagCapability>(entity.guid(), "unknown");
	return entity;
}



void EntityJournal::despawn(Entity& entity)
{
	if (m_onDespawnRegistry.find(entity.tag()) != m_onDespawnRegistry.end())
		m_onDespawnRegistry[entity.tag()](entity);

	m_entityRegistry->destroy(entity.guid());
}



void EntityJournal::despawn(entt::entity entity)
{
	Entity temp(m_entityRegistry, entity);
	if (m_onDespawnRegistry.find(temp.tag()) != m_onDespawnRegistry.end())
		m_onDespawnRegistry[temp.tag()](temp);

	m_entityRegistry->destroy(entity);
}



std::vector<Entity> EntityJournal::getEntities(const AxisAlignedBB& area)
{
	std::vector<Entity> entities;
	auto views = m_entityRegistry->view<PositionCapability>();
	for (auto entity : views)
	{
		PositionCapability& pos = views.get<PositionCapability>(entity);
		if (Collision::RectVsPt(area, pos))
			entities.emplace_back(m_entityRegistry, entity);
	}
	return entities;
}



size_t EntityJournal::count() const
{
	return m_entityRegistry->alive();
}



void EntityJournal::registerSpawner(const std::string& tagIn, Callback callbackIn)
{
	m_entityFactoryRegistry.insert({ tagIn, callbackIn });
}



void EntityJournal::registerOnSpawn(const std::string& tagIn, Callback callbackIn)
{
	m_onSpawnRegistry.insert({ tagIn, callbackIn });
}



void EntityJournal::registerOnDespawn(const std::string& tagIn, Callback callbackIn)
{
	m_onDespawnRegistry.insert({ tagIn, callbackIn });
}




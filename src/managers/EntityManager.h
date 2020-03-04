//============================================================================
// Name       		: EntityManager.h
// Author     		: Thomas Hooks
// Last Modified	: 03/03/2020
//============================================================================




#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_




#include <vector>
#include <map>
#include <memory>
#include <string>

#include "Builder.h"




class EntityManager {

public:

	EntityManager(class GameLogger *log_ptr);

	~EntityManager();

	EntityManager(const EntityManager &other) = delete;

	EntityManager(EntityManager &&other) = delete;

	void registerEntity(std::string tag, BuilderBase<class Entity>* builder);

	int spawn(std::string tag, const class Position &pos);
	bool despawn(int id);

	void drawAll(void);

	class Entity* getEntity(int id);
	int numberOfEntities(void);

private:

	class GameLogger *logger;

	std::map<int, std::unique_ptr<class Entity>> entityMap;
	int highestEntityID;

	std::map<std::string, std::unique_ptr<BuilderBase<class Entity>>> entityRegistry;
};


#endif /* ENTITYMANAGER_H_ */




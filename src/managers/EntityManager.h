//============================================================================
// Name       		: EntityManager.h
// Author     		: Thomas Hooks
// Last Modified	: 02/29/2020
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

	EntityManager();
	EntityManager(class GameLogger *log_ptr);

	~EntityManager();

	EntityManager(const EntityManager &other) = delete;

	EntityManager(EntityManager &&other) = delete;

	void init(class GameLogger *log_ptr);

	void registerEntity(std::string tag, BuilderBase<class Entity>* builder);

	//class Entity& get_entity(int index);

	int spawn(std::string tag, class Position pos);
	bool despawn(int index);

private:

	bool hasBeenInit;

	class GameLogger *logger;

	std::vector<std::unique_ptr<class Entity>> entityArray;

	std::map<std::string, std::unique_ptr<BuilderBase<class Entity>>> entityRegistry;
};


#endif /* ENTITYMANAGER_H_ */




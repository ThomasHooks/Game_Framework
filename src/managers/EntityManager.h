//============================================================================
// Name       		: EntityManager.h
// Author     		: Thomas Hooks
// Last Modified	: 02/24/2020
//============================================================================




#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_




class EntityManager {

public:
	EntityManager();
	~EntityManager();
	EntityManager(const EntityManager &other);
	EntityManager(EntityManager &&other);
};


#endif /* ENTITYMANAGER_H_ */




//============================================================================
// Name       		: WorldContext.h
// Author     		: Thomas Hooks
// Last Modified	: 03/19/2020
//============================================================================




#ifndef WORLDCONTEXT_H_
#define WORLDCONTEXT_H_




class WorldContext {

public:

	WorldContext(class TileMap *worldIn,
			class EntityManager *entites_ptr,
			class PlayerEntity *playerIn,
			float deltaTimeIn);



	~WorldContext();



	class TileMap& getWorld();



	class EntityManager& getEntities();



	class PlayerEntity* getPlayer();



	float getDeltaTime();



protected:

	class TileMap *world;

	class EntityManager *entities;

	class PlayerEntity *player;

	float deltaTime;
};


#endif /* WORLDCONTEXT_H_ */




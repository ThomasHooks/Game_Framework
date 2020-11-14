//============================================================================
// Name       		: WorldContext.h
// Author     		: Thomas Hooks
// Last Modified	: 03/22/2020
//============================================================================




#ifndef WORLDCONTEXT_H_
#define WORLDCONTEXT_H_




class WorldContext {

public:

	WorldContext(class TileMap *worldIn,
			class EntityManager *entites_ptr,
			class IEntity *playerIn,
			class Timer* timer);



	~WorldContext();



	/*
	 * @return	The current World
	 *
	 * Gets the current World
	 */
	class TileMap& getWorld();



	/*
	 * @return	A reference to the Entity Manager
	 *
	 * Gets the Entity Manager
	 */
	class EntityManager& getEntities();



	/*
	 * @return	A reference to the Player
	 *
	 * Gets the Player
	 */
	class IEntity& getPlayer();



protected:

	class TileMap *world;

	class EntityManager *entities;

	class IEntity *player;

	class Timer* timer;
};


#endif /* WORLDCONTEXT_H_ */




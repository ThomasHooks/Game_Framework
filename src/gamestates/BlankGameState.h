//============================================================================
// Name       		: BlankGameState.h
// Author     		: Thomas Hooks
// Last Modified	: 04/04/2020
//============================================================================




#ifndef SRC_BLANKGAMESTATE_H_
#define SRC_BLANKGAMESTATE_H_


#include <memory>
#include <vector>

#include "IGameState.h"


class BlankGameState : public IGameState {

public:

	BlankGameState(class Game *Game, int StateID);



	~BlankGameState();



	BlankGameState(const BlankGameState &other) = delete;



	BlankGameState(BlankGameState &&other) = delete;



	void onInputEvent() override;



	/*
	 * @param	camera Reference to the Game's Camera
	 *
	 * @param	worldIn The current World
	 *
	 * @param	deltaTime Amount of time that has elapsed since the last tick
	 *
	 * Causes the current Game State to update
	 */
	void tick(const class GameCamera &camera, class TileMap &worldIn, float deltaTime) override;



	/*
	 * @param	camera Reference to the Game's Camera
	 *
	 * Renders the current GameState
	 */
	void render(const class GameCamera &camera) override;



	void ChangeState(int StateFlag, class Game *Game) override;



protected:

	//----All of this should be removed later----
		class IEntity* player;
	//----All of this should be removed later----
};


#endif /* SRC_BLANKGAMESTATE_H_ */




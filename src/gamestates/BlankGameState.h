//============================================================================
// Name       		: BlankGameState.h
// Author     		: Thomas Hooks
// Last Modified	: 03/21/2020
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

	void GetUserInput() override;

	void tick(const class Position &cameraPos) override;

	void ChangeState(int StateFlag, class Game *Game) override;

	//----This need to be put in the base class----
	//void EntityMapCollisionRect(int EntityIndex, int MapIndex);
	//----This need to be put in the base class----


protected:

	void customDraw(const class Position &cameraPos,
			const class Dimension &windowSize) override;

	//----All of this should be removed later----
	std::vector<std::unique_ptr<class Game_Dynamic>> vEntity;
	class IEntity* player;
	//----All of this should be removed later----
};


#endif /* SRC_BLANKGAMESTATE_H_ */




//============================================================================
// Name       		: BlankGameState.h
// Author     		: Thomas Hooks
// Last Modified	: 03/24/2020
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



	void tick(const class Position &cameraPos) override;



	void ChangeState(int StateFlag, class Game *Game) override;



protected:

	void customDraw(const class Position &cameraPos,
			const class Dimension &windowSize) override;

	//----All of this should be removed later----
		class IEntity* player;
	//----All of this should be removed later----
};


#endif /* SRC_BLANKGAMESTATE_H_ */




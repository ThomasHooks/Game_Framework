//============================================================================
// Name       		: BlankGameState.h
// Author     		: Thomas Hooks
// Last Modified	: 02/22/2020
//============================================================================




#ifndef SRC_BLANKGAMESTATE_H_
#define SRC_BLANKGAMESTATE_H_




#include "GameState.h"

#include <memory>
#include <vector>


class BlankGameState : public GameState {

public:

	BlankGameState(class Game *Game, int StateID);

	~BlankGameState();

	BlankGameState(const BlankGameState &other) = delete;

	BlankGameState(BlankGameState &&other) = delete;

	void GetUserInput() override;

	void Process() override;

	void ChangeState(int StateFlag, class Game *Game) override;

	//----This need to be put in the base class----
	void EntityMapCollisionRect(int EntityIndex, int MapIndex);
	//----This need to be put in the base class----


protected:

	void customDraw(float offsetX, float offsetY, int visibleTilesHor, int visibleTilesVer) override;

	//----All of this should be removed later----
	std::vector<std::unique_ptr<class Game_Dynamic>> vEntity;
	std::vector<class Game_Map> vMap;
	//----All of this should be removed later----
};


#endif /* SRC_BLANKGAMESTATE_H_ */




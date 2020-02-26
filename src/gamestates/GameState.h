//============================================================================
// Name       		: GameState.h
// Author     		: Thomas Hooks
// Last Modified	: 02/22/2020
//============================================================================




#ifndef GAME_STATE_H_
#define GAME_STATE_H_




class GameState {

public:

	virtual ~GameState(){}

	GameState(class Game *Game, int StateID){game = Game; nGameStateID = StateID;}

	virtual void GetUserInput() = 0;

	virtual void Process() = 0;

	void Draw();

	virtual void ChangeState(int StateFlag, class Game *Game) = 0;

	int nGameStateID;

protected:

	virtual void customDraw(float offsetX, float offsetY, int visibleTilesHor, int visibleTilesVer) = 0;

	class Game *game;

};




#endif /* GAME_STATE_H_ */



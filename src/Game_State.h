//============================================================================
// Name       		: Game_State.h
// Author     		: Thomas Hooks
// Version    		: 1
// Last Modified	: 11/2/2019
// Description		:
//============================================================================




#ifndef GAME_STATE_H_
#define GAME_STATE_H_




#include <memory>
#include <vector>
#include "Game_Dynamic.h"




class Game_State{
public:
	virtual ~Game_State(){}
	Game_State(class Game *Game, int StateID){cGEngine = Game; nGameStateID = StateID;}

	virtual void GetUserInput() = 0;
	virtual void Process() = 0;
	virtual void Draw() = 0;
	virtual void ChangeState(int StateFlag, class Game *Game) = 0;

	int nGameStateID;

protected:
	class Game *cGEngine;

};


//============================================================================
/*
 * Game_State(cGameEngine *cGameEngine){cGEngine = cGameEngine;}
 *
 * cGSBlack(cGameEngine *cGameEngine) : Game_State(cGameEngine){}
 *
 * */


class cGSBlack : public Game_State{
public:
	cGSBlack(class Game *Game, int StateID);
	~cGSBlack(){}

	void GetUserInput() override;
	void Process() override;
	void Draw() override;
	void ChangeState(int StateFlag, Game *Game) override;

	//----This need to be put in the base class----
	float fCameraX, fCameraY;		//Location of camera's top left corner

	void EntityMapCollisionRect(int EntityIndex, int MapIndex);
	//----This need to be put in the base class----

protected:
	//----These need to be put in the base class----
	std::vector<std::unique_ptr<class Game_Dynamic>> vEntity;		//Vector of all entities
	std::vector<class Game_Map> vMap;								//Vector of all maps
	//----These need to be put in the base class----
};


#endif /* GAME_STATE_H_ */

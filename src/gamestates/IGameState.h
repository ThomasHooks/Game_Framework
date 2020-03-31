//============================================================================
// Name       		: IGameState.h
// Author     		: Thomas Hooks
// Last Modified	: 03/26/2020
//============================================================================




#ifndef GAME_STATE_H_
#define GAME_STATE_H_




class IGameState {

public:

	virtual ~IGameState(){}



	IGameState(class Game *Game, int StateID);



	virtual void onInputEvent() = 0;



	virtual void tick(const class Position &cameraPos) = 0;



	/*
	 * @param	camera The coordinates of the camera
	 *
	 * Renders the current GameState
	 */
	void render(const class Position &cameraPos);



	virtual void ChangeState(int StateFlag, class Game *Game) = 0;



	int nGameStateID;

protected:

	virtual void customDraw(const class Position &camera,
			const class Dimension &windowSize) = 0;



	//Gets the Entity Manager
	class EntityManager& getEntities();



	//Gets the World Manager
	class MapManager& getWorlds();



	//Gets the Renderer
	class RendererManager& getRenderer();



	//Gets the Logger
	class GameLogger& getLogger();



	//Gets the Timer
	class GameTimer& getTimer();

	//TODO make private
	class Game *game;
private:


};

#endif /* GAME_STATE_H_ */




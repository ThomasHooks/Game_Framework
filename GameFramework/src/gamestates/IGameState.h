//============================================================================
// Name       		: IGameState.h
// Author     		: Thomas Hooks
// Last Modified	: 04/06/2020
//============================================================================




#ifndef GAME_STATE_H_
#define GAME_STATE_H_




class IGameState {

public:

	virtual ~IGameState(){}



	IGameState(class Game *Game, int StateID);



	virtual void onInputEvent() = 0;



	/*
	 * @param	camera Reference to the Game's Camera
	 *
	 * @param	worldIn The current World
	 *
	 * @param	deltaTime Amount of time that has elapsed since the last tick
	 *
	 * Causes the current Game State to update
	 */
	virtual void tick(const class GameCamera &camera, class TileMap &worldIn, float deltaTime) = 0;



	/*
	 * @param	camera Reference to the Game's Camera
	 *
	 * Renders the current GameState
	 */
	virtual void render(const class GameCamera &camera) = 0;



	virtual void ChangeState(int StateFlag, class Game *Game) = 0;



	int nGameStateID;

protected:

	//Gets the Entity Manager
	class EntityManager& getEntities();



	//Gets the World Manager
	class WorldStack& getWorlds();



	//Gets the Renderer Manager
	class Renderer& getRenderer();



	//Gets the Audio Manager
	class AudioMixer& getMixer();



	//Gets the Logger
	class Logger& getLogger();



	//Gets the Timer
	class GameTimer& getTimer();

	//TODO make private
	class Game *game;
private:


};

#endif /* GAME_STATE_H_ */




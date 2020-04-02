//============================================================================
// Name       		: Game_Manager.h
// Author     		: Thomas Hooks
// Last Modified	: 02/24/2020
//============================================================================




#ifndef SRC_GAME_MANAGER_H_
#define SRC_GAME_MANAGER_H_




#include <vector>
#include <memory>

#include "../utilities/GameLogger.h"




template<typename T> class GameManager {

public:

	GameManager(class Game *gamePtr){game = gamePtr;}

	~GameManager(){}

	GameManager(const GameManager &other) = delete;

	GameManager(GameManager &&other) = delete;


	//------------------------------------------------------------------------


	void Push(T *newElement){
		/*
		 * *brief* Adds a new element to the stack
		 */




		//Verify that the new pointer is not pointing to null
		if (!(newElement == nullptr)) {

			v_stack.emplace_back(std::unique_ptr<T>(newElement));

			//This is done to prevent the user from trying to access the pointer
			//Or from trying to free the pointer after they passed it
			newElement = nullptr;
		}

		else {

			//game->Log.Message(Level::Warning, "Cannot add null to the stack!", Output::Console);
		}

		return;
	}


	//------------------------------------------------------------------------


	void Pop(void){
		/*
		 * *brief* Removes the top element from the state stack
		 */




		if(v_stack.empty()){

			//game->Log.Message(Level::Warning, "Tried to free element, but stack is empty!", Output::Console);
		}

		else v_stack.pop_back();

		return;
	}


	//------------------------------------------------------------------------


	//Returns the number of objects in the stack
	int Size(void) {return v_stack.size();}


	//Returns if the stack is empty
	bool Empty(void) {return v_stack.empty();}


	//------------------------------------------------------------------------


protected:

	//Vector used to store all objects that are currently loaded into the game
	std::vector<std::unique_ptr<T>> v_stack;

	//Pointer back to the game
	class Game *game;
};


#endif /* SRC_GAME_MANAGER_H_ */




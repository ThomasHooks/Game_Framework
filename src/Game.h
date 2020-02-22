//============================================================================
// Name       		: Game.h
// Author     		: Thomas Hooks
// Last Modified	: 02/22/2020
//============================================================================




#ifndef GAME_H_
#define GAME_H_




#include "State_Manager.h"
#include "Asset_Manager.h"
#include "Game_Timer.h"
#include "Game_Logger.h"
#include "MapManager.h"




class Game{

public:

	Game();
	Game(const char * title, int Window_Height, int Window_Width, Uint32 flags, int Max_FPS);

	~Game();

	void run(void);

	bool init(const char * title, int Window_Height, int Window_Width, Uint32 flags, int Max_FPS);

	class State_Manager State;

	class MapManager Map;				//TODO Map_Manager

	//Entity_Manager Entities;			//TODO Entity_Manager

	class Asset_Manager Assets;

	class Game_Timer Timer;

	class Game_Logger Log;


	//Getters and setters
	bool get_gameOver() const {return b_gameOver;}
	void set_gameOver(bool flag) {b_gameOver = flag;}

	int get_maxFPS(void) const {return n_maxFPS;}
	void set_maxFPS(int Max_FPS) {if(Max_FPS != 0) n_maxFPS = Max_FPS;}

	int get_windowHeight(void) const {return WindowHeight;}
	void set_windowHeight(int height) {WindowHeight = height;}

	int get_windowWidth(void) const {return WindowWidth;}
	void set_windowWidth(int width) {WindowWidth = width;}

	SDL_Window* get_window(void) {return window;}
	SDL_Renderer* get_renderer(void) {return renderer;}

	float get_cameraX(void) const {return f_cameraX;}
	void set_cameraX(float positionX) {f_cameraX = positionX;}

	float get_cameraY(void) const {return f_cameraY;}
	void set_cameraY(float positionY) {f_cameraY = positionY;}


private:

	//Flags
	bool b_gameOver;			//If the game has ended
	bool b_hasBeenInit;

	//Coordinates of camera's top left corner
	float f_cameraX;
	float f_cameraY;

	//Maximum frames per second
	int n_maxFPS;

	//Window data members
	SDL_Window *window;			//Stores a pointer to the game window
	SDL_Renderer *renderer;		//Stores a pointer to the game renderer

	int WindowHeight;			//Stores the window height
	int WindowWidth;			//Stores the window width
};




#endif /* GAME_H_ */








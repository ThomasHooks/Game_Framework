//============================================================================
// Name       		: Game_Dynamic.cpp
// Author     		: Thomas Hooks
// Version    		: 1
// Last Modified	: 11/2/2019
// Description		:
//============================================================================


#include <iostream>
#include<sstream>
#include <list>
#include <SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <ctime>
#include <math.h>
#include <vector>
#include <list>
#include <memory>
#include <string>

#include "Game.h"
#include "Game_Dynamic.h"

#include "GameState.h"


//============================================================================
//                             Game_Dynamic Class


Game_Dynamic::Game_Dynamic(float x, float y, int width, int height, int name){
	//

	fX = x; fdX = 0; fd2X = 0;
	fY = y; fdY = 0; fd2Y = 0;

	nWidth = width;
	nHeight = height;

	nNameTag = name;
	bFriendly = true;
	bSolid = true;

	return;
}


//============================================================================


Game_Dynamic::~Game_Dynamic(){
	//

	return;
}


//============================================================================


void Game_Dynamic::UpdatePosition(float DeltaTime){
	/*
	 * This method updates the entities position and velocity
	 *
	 * */

	//Update velocity
	fdX = fdX +fd2X * DeltaTime;
	fdY = fdY +fd2Y * DeltaTime;

	//Update position
	fX = fX + fdX * DeltaTime;
	fY = fY + fdY * DeltaTime;

	return;
}



//////////////////////////////////////////////////////////////////////////////
//============================================================================
// cDynamicCharacter Class



cDynamicCharacter::cDynamicCharacter(float x, float y, int width,
		int height, int name)
		: Game_Dynamic(x, y, width, height, name){
	//

	nHealth = 1;
	nMaxHealth = 1;
	bOnGround = true;

	return;
}


//============================================================================


cDynamicCharacter::~cDynamicCharacter(){
	//

	return;
}


//============================================================================


void cDynamicCharacter::Update(float DeltaTime){
	//

	return;
}


//============================================================================


void cDynamicCharacter::Draw(SDL_Renderer *renderer, SDL_Texture *tTexture, float fOffSetX, float fOffSetY) {
	//

	//Set the draw color to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	//Select the right sprite from the sheet
	SDL_Rect CharScr = {0 * nWidth, 0,
			nWidth, nHeight};

	//Set the sprite size and location on map
	SDL_Rect CharRect = {(int)(fX - fOffSetX*nWidth), (int)(fY - fOffSetY*nHeight),
			nWidth, nHeight};//

	//Draw the Character to the screen
	SDL_RenderCopyEx(renderer, tTexture, &CharScr, &CharRect, 0,
			NULL, SDL_FLIP_NONE);

	return;
}



//////////////////////////////////////////////////////////////////////////////
//============================================================================
// cPlayerCharacter Class



cPlayerCharacter::cPlayerCharacter(float x, float y, int width, int height,
		int name)
		: cDynamicCharacter(x, y, width, height, name){
	//

	return;
}


//============================================================================


cPlayerCharacter::~cPlayerCharacter(){
	//

	return;
}


//============================================================================


void cPlayerCharacter::Update(float DeltaTime){
	//

	//----This should be removed----
	UpdatePosition(DeltaTime);
	const float fGravity = 128.0f;
	fdX = 0.0f;

	fd2Y += fGravity * DeltaTime;
	if(fd2Y >= fGravity) fd2Y = fGravity;
	if(fdY >= fGravity) fd2Y = fGravity;
	//----This should be removed----

	return;
}








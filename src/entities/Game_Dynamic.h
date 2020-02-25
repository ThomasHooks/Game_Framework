//============================================================================
// Name       		: Game_Dynamic.h
// Author     		: Thomas Hooks
// Last Modified	: 11/2/2019
//============================================================================



#ifndef GAME_DYNAMIC_H_
#define GAME_DYNAMIC_H_

#include <SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include <string>

//#include "Game.h"

class Game_Dynamic{
//

public:
	virtual ~Game_Dynamic() = 0;
	Game_Dynamic(float x, float y, int width, int height, int name); //std::string Name

	virtual void Update(float DeltaTime) = 0;
	virtual void Draw(SDL_Renderer *renderer, SDL_Texture *tTexture, float fOffSetX, float fOffSetY) = 0;

public:
	int nNameTag;
	bool bFriendly;
	bool bSolid;

	float fX, fY;
	float fdX, fdY;
	float fd2X, fd2Y;
	int nWidth, nHeight;

protected:
	void UpdatePosition(float DeltaTime);
};



//////////////////////////////////////////////////////////////////////////////
//============================================================================



class cDynamicCharacter : public Game_Dynamic{

public:
	cDynamicCharacter(float x, float y, int width, int height, int name);
	~cDynamicCharacter();

	void Update(float DeltaTime) override;
	void Draw(SDL_Renderer *renderer, SDL_Texture *tTexture, float fOffSetX, float fOffSetY) override;

public:
	int nHealth;
	int nMaxHealth;
	bool bOnGround;
};



//////////////////////////////////////////////////////////////////////////////
//============================================================================



class cPlayerCharacter : public cDynamicCharacter{

public:
	cPlayerCharacter(float x, float y, int width, int height, int name);
	~cPlayerCharacter();

	void Update(float DeltaTime) override;
	//void Draw(SDL_Renderer *renderer, SDL_Texture *tTexture) override;
};



#endif /* GAME_DYNAMIC_H_ */








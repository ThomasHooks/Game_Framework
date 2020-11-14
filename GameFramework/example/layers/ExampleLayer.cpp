#include <SDL.h>

#include "ExampleLayer.hpp"
#include "Game.hpp"
#include "utilities/GameCamera.h"
#include "world/WorldStack.h"
#include "world/TileMap.h"
#include "renderer/Renderer.h"
#include "audiomixer/AudioMixer.h"
#include "entities/EntityManager.h"
#include "entities/PlayerEntity.h"
#include "utilities/Loggers.hpp"




ExampleLayer::ExampleLayer(Game& game)
	: m_game(game)
{}



ExampleLayer::~ExampleLayer() 
{}



void ExampleLayer::onAttach(Game& game)
{
	game.worldStack().pushMap("tiletest", "data/map/test.map");

	Pos2N tileDim(16, 16);
	game.renderer().registerTexture("mario", "./data/gfx/Mario.png", tileDim);
	game.renderer().registerTexture("tiletest", "./data/gfx/tile_test.png", tileDim);
	game.renderer().setScale(2.0f);

	game.audioMixer().registerSample("hit01", "./data/sfx/hit01.wav");
	game.audioMixer().setSampleVolume("hit01", 0.75f);

	game.entities().registerEntity("mario", new EntityBuilder<PlayerEntity>());
	m_player = game.entities().spawn("mario", Pos2D(128.0, 224.0), EnumSide::RIGHT);
	game.getCamera()->trackEntity(m_player);
}



void ExampleLayer::onTick(const GameCamera& cameraIn, TileMap& worldIn, float deltaTime)
{
	if (Game::isKeyPressed(SDL_SCANCODE_W))
		m_player->updateVel(Pos2D(0.0, -576.0), 0.93f, deltaTime);
	else if (Game::isKeyPressed(SDL_SCANCODE_S))
		m_player->updateVel(Pos2D(0.0, 576.0), 0.93f, deltaTime);
	
	if (Game::isKeyPressed(SDL_SCANCODE_A))
		m_player->updateVel(Pos2D(-288.0, 0.0), 0.93f, deltaTime);
	else if (Game::isKeyPressed(SDL_SCANCODE_D))
		m_player->updateVel(Pos2D(288.0, 0.0), 0.93f, deltaTime);

	Pos2N windowSize(cameraIn.width(), cameraIn.height());
	getGame().entities().tickAll(cameraIn.getPos(), windowSize, worldIn, deltaTime);
}



void ExampleLayer::onRender(const GameCamera& cameraIn, Renderer& rendererIn)
{
	rendererIn.setDrawColor(0, 0, 0, 255);
	rendererIn.clear();

	Pos2N windowSize(cameraIn.width(), cameraIn.height());
	getGame().worldStack().draw(cameraIn.getPos(), windowSize, rendererIn);
	getGame().entities().drawAll(cameraIn.getPos(), windowSize, rendererIn, true);

	rendererIn.present();
}








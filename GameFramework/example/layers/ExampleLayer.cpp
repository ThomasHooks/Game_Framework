#include <SDL.h>

#include "ExampleLayer.hpp"
#include "Game.hpp"
#include "renderer/screen/GameCamera.h"
#include "world/WorldStack.h"
#include "world/TileMap.h"
#include "renderer/Renderer.h"
#include "audiomixer/AudioMixer.h"
#include "entities/Entities.hpp"
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

	game.entities().registerSpawner("mario", [this](Entity& entity)
		{
			entity
				.add<KinematicCapability>(0.0, 0.0)
				.add<ColliderCapability>(0.0, 0.0, 22.0, 32.0)
				.add<RenderableCapability>("mario", 0, 0, 16, 16);
		});
	Entity player = game.entities().spawn("mario", Pos2D(128.0, 224.0));
	m_entities.push_back(player);

	//game.getCamera()->trackEntity(m_player);
}



void ExampleLayer::onTick(const GameCamera& cameraIn, TileMap& worldIn, float deltaTime)
{
	KinematicCapability& cap = m_entities[0].get<KinematicCapability>();
	if (Game::isKeyPressed(SDL_SCANCODE_W))
		m_entities[0].movePos({ 0.0, -576.0 }, 0.93f, deltaTime);
	else if (Game::isKeyPressed(SDL_SCANCODE_S))
	m_entities[0].movePos({ 0.0, 576.0 }, 0.93f, deltaTime);
	
	if (Game::isKeyPressed(SDL_SCANCODE_A))
		m_entities[0].movePos({ -576.0, 0.0 }, 0.93f, deltaTime);
	else if (Game::isKeyPressed(SDL_SCANCODE_D))
		m_entities[0].movePos({ 576.0, 0.0 }, 0.93f, deltaTime);

	Pos2N windowSize(cameraIn.width(), cameraIn.height());
	//getGame().entities().tickAll(cameraIn.getPos(), windowSize, worldIn, deltaTime);
	m_entities[0].updatePos(0.93f, deltaTime);
}



void ExampleLayer::onRender(const GameCamera& cameraIn, Renderer& rendererIn)
{
	rendererIn.setDrawColor(0, 0, 0, 255);
	rendererIn.clear();

	Pos2N windowSize(cameraIn.width(), cameraIn.height());
	getGame().worldStack().draw(cameraIn.getPos(), windowSize, rendererIn);

	//getGame().entities().drawAll(cameraIn.getPos(), windowSize, rendererIn, true);
	RenderableCapability& renCap = m_entities[0].get<RenderableCapability>();
	rendererIn.drawSprite(renCap.sprite.tag(), m_entities[0].pos(), cameraIn.getPos(), renCap.sprite.getIndex(), false);

	rendererIn.present();
}








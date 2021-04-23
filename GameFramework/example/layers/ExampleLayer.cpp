#include <SDL.h>

#include "ExampleLayer.hpp"
#include "Game.hpp"
#include "renderer/screen/Camera.h"
#include "world/WorldStack.h"
#include "world/TileMap.h"
#include "renderer/Renderer.h"
#include "audiomixer/AudioMixer.h"
#include "entities/Entities.hpp"
#include "utilities/Loggers.hpp"
#include "renderer/texture/Sprite.hpp"
#include "renderer/materials/FlatColorMaterial.h"




ExampleLayer::ExampleLayer(Game& game)
	: m_game(game)
{}



ExampleLayer::~ExampleLayer() 
{}



void ExampleLayer::onAttach(Game& game)
{
	game.worldStack().pushMap("tiletest", "data/map/test.map");

	/*Pos2N tileDim(16, 16);
	game.renderer().registerTexture("mario", "./data/gfx/Mario.png", tileDim);
	game.renderer().registerTexture("tiletest", "./data/gfx/tile_test.png", tileDim);
	game.renderer().setScale(2.0f); */

	game.audioMixer().registerSample("hit01", "./data/sfx/hit01.wav");
	game.audioMixer().setSampleVolume("hit01", 0.75f);

	game.entities().registerSpawner("mario", [this](Entity& entity)
		{
			Pos2N tileSize(16, 16);
			Sprite sprite("mario", tileSize);
			entity
				.add<KinematicCapability>(0.0, 0.0)
				.add<ColliderCapability>(0.0, 0.0, 22.0, 32.0)
				.add<RenderableCapability>(sprite, tileSize);
		});
	Entity player = game.entities().spawn("mario", Pos2D(128.0, 224.0));
	m_entities.push_back(player);
}



void ExampleLayer::onTick(const Camera& cameraIn, TileMap& worldIn, float deltaTime)
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

	//Pos2N windowSize(cameraIn.width(), cameraIn.height());
	//getGame().entities().tickAll(cameraIn.getPos(), windowSize, worldIn, deltaTime);
	m_entities[0].updatePos(0.93f, deltaTime);
}



void ExampleLayer::onRender(const std::shared_ptr<Camera>& cameraIn, Renderer& rendererIn)
{
	rendererIn.begin(cameraIn);

	rendererIn.clear(0.1f, 0.1f, 0.1f, 1.0f);

	FlatColorMaterial material({ 0.8f, 0.2f, 0.3f, 1.0f });
	rendererIn.drawQuad({ (float)m_entities[0].pos().x, (float)m_entities[0].pos().y, 0.0f }, { 32, 32 }, material);

	material.color = { 0.2f, 0.3f, 0.8f, 1.0f };
	rendererIn.drawQuad({ 600.0f, 300.0f, 0.0f }, { 64, 128 }, material);

	rendererIn.end();
}








#include <SDL.h>

#include "ExampleLayer.hpp"
#include "Application.hpp"
#include "renderer/screen/Camera.h"
#include "world/WorldStack.h"
#include "world/TileMap.h"
#include "renderer/Renderer.h"
#include "audiomixer/AudioMixer.h"
#include "entities/Entities.hpp"
#include "utilities/Loggers.hpp"
#include "renderer/texture/Sprite.hpp"
#include "renderer/materials/FlatColorMaterial.h"




ExampleLayer::ExampleLayer(Application& app)
	: m_game(app)
{}



ExampleLayer::~ExampleLayer() 
{}



void ExampleLayer::onAttach(Application& app)
{
	app.worldStack().pushMap("tiletest", "data/map/test.map");

	app.assetLibrarian().addTexture("data/gfx/Mario.png");
	app.assetLibrarian().addTexture("data/gfx/flappy_bird_sprite_sheet.png");
	app.assetLibrarian().addTexture("data/gfx/null.png");
	app.assetLibrarian().addTexture("data/gfx/tile_test.png", { 16, 16 });
	app.assetLibrarian().addTexture("data/gfx/overworld sheet.png", { 16, 16 });

	app.audioMixer().registerSample("hit01", "./data/sfx/hit01.wav");
	app.audioMixer().setSampleVolume("hit01", 0.75f);

	app.entities().registerSpawner("mario", [this](Entity& entity)
		{
			Pos2N tileSize(16, 16);
			Sprite sprite("mario", tileSize);
			entity
				.add<KinematicCapability>(0.0, 0.0)
				.add<ColliderCapability>(0.0, 0.0, 22.0, 32.0);
		});
	Entity player = app.entities().spawn("mario", Pos2D(128.0, 224.0));
	m_entities.push_back(player);
}



void ExampleLayer::onTick(const Camera& cameraIn, float deltaTime)
{
	KinematicCapability& cap = m_entities[0].get<KinematicCapability>();
	if (Application::isKeyPressed(SDL_SCANCODE_W))
		m_entities[0].movePos({ 0.0, -576.0 }, 0.93f, deltaTime);
	else if (Application::isKeyPressed(SDL_SCANCODE_S))
	m_entities[0].movePos({ 0.0, 576.0 }, 0.93f, deltaTime);
	
	if (Application::isKeyPressed(SDL_SCANCODE_A))
		m_entities[0].movePos({ -576.0, 0.0 }, 0.93f, deltaTime);
	else if (Application::isKeyPressed(SDL_SCANCODE_D))
		m_entities[0].movePos({ 576.0, 0.0 }, 0.93f, deltaTime);

	m_entities[0].updatePos(0.93f, deltaTime);
}



void ExampleLayer::onRender(const std::shared_ptr<Camera>& cameraIn, Renderer& rendererIn)
{
	rendererIn.begin(cameraIn);

	rendererIn.clear(0.1f, 0.1f, 0.1f, 1.0f);

	rendererIn.drawQuad({ 256.0f, 256.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "null");

	rendererIn.drawQuad({ 328.0f, 256.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "flappy_bird_sprite_sheet");

	rendererIn.drawQuad({ 400.0f, 112.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "tile_test", 0);
	rendererIn.drawQuad({ 400.0f, 184.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "tile_test", 1);
	rendererIn.drawQuad({ 400.0f, 256.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "tile_test", 2);
	rendererIn.drawQuad({ 400.0f, 328.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "tile_test", 3);
	rendererIn.drawQuad({ 400.0f, 400.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "tile_test", 4);
	rendererIn.drawQuad({ 400.0f, 472.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "tile_test", 5);
	rendererIn.drawQuad({ 400.0f, 544.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "tile_test", 6);

	rendererIn.drawQuad({ 472.0f, 112.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 1);
	rendererIn.drawQuad({ 472.0f, 184.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 2);
	rendererIn.drawQuad({ 472.0f, 256.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 3);
	rendererIn.drawQuad({ 472.0f, 328.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 4);
	rendererIn.drawQuad({ 472.0f, 400.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 5);
	rendererIn.drawQuad({ 472.0f, 472.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 6);
	rendererIn.drawQuad({ 472.0f, 544.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 7);
	rendererIn.drawQuad({ 472.0f, 616.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 8);
	rendererIn.drawQuad({ 544.0f, 112.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 9);
	rendererIn.drawQuad({ 544.0f, 184.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 10);
	rendererIn.drawQuad({ 544.0f, 256.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 11);
	rendererIn.drawQuad({ 544.0f, 328.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 12);
	rendererIn.drawQuad({ 544.0f, 400.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 13);
	rendererIn.drawQuad({ 544.0f, 472.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 14);
	rendererIn.drawQuad({ 544.0f, 544.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 15);
	rendererIn.drawQuad({ 544.0f, 616.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 16);
	rendererIn.drawQuad({ 616.0f, 112.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 17);
	rendererIn.drawQuad({ 616.0f, 184.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 18);
	rendererIn.drawQuad({ 616.0f, 256.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 19);
	rendererIn.drawQuad({ 616.0f, 328.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 20);
	rendererIn.drawQuad({ 616.0f, 400.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 21);
	rendererIn.drawQuad({ 616.0f, 472.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 22);
	rendererIn.drawQuad({ 616.0f, 544.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 23);
	rendererIn.drawQuad({ 616.0f, 616.0f, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "overworld sheet", 24);

	rendererIn.drawQuad({ 688.0f, 256.0f, 0.0f }, { 64, 64 }, { 0.2f, 0.6f, 0.8f, 1.0f });

	rendererIn.drawQuad({ (float)m_entities[0].pos().x, (float)m_entities[0].pos().y, 0.0f }, { 64, 64 }, { 1.0f, 1.0f, 1.0f, 1.0f }, "Mario");

	rendererIn.end();
}




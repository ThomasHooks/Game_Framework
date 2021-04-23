#include <string>
#include <map>
#include <memory>

#include <SDL.h>
#include "SDL_image.h"
#include <spdlog/spdlog.h>

#include "renderer/Renderer.h"
#include "renderer/RendererFondation.h"
#include "renderer/texture/TextureSDL.h"
#include "renderer/texture/Sprite.hpp"
#include "renderer/shaders/Shader.h"
#include "renderer/materials/IMaterial.h"
#include "renderer/screen/Camera.h"
#include "utilities/Assertions.h"




Renderer::Renderer()
	: m_hasBeenInit(false), m_scale(1.0f), m_renderer(nullptr) 
{
	m_logger = Loggers::getLog();
}



Renderer::~Renderer() 
{
	m_logger->info("Rendering stopped");
}



void Renderer::init(SDL_Window *windowIn)
{
	if (!m_hasBeenInit) 
	{
		GAME_ASSERT(windowIn != nullptr);
		m_renderer = SDL_CreateRenderer(windowIn, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		m_logger->info("Renderer has been initialized");
		m_hasBeenInit = true;

		/*float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
		}; */

		float vertices[] = {
		200.0f, 200.0f, 0.0f,
		100.0f, 200.0f, 0.0f,
		100.0f, 100.0f, 0.0f,
		200.0f, 100.0f, 0.0f
		};
		m_vbo.create(nullptr, sizeof(vertices), VertexBuffer::Usage::Dynamic);
		m_vbo.setLayout(VertexBuffer::Layout().add(VertexBuffer::Attribute::Float3, "a_pos"));

		unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };
		m_ibo.create(indices, 6, IndexBuffer::Usage::Static);

		m_shaders.add("FlatColor", "data/shaders/flatColor.vsh", "data/shaders/flatColor.psh");
	}
}



void Renderer::shutdown()
{
	m_logger->info("Shutting down Renderer");
	if (m_hasBeenInit)
	{
		m_vbo.destroy();

		m_logger->info("Freeing SDL renderer");
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
		m_logger->info("SDL renderer has been freed");
	}
	this->deregisterAllTextures();
}



bool Renderer::registerTexture(const std::string& tag, const std::string& fileLocation, const Pos2N& tileSize)
{
	m_logger->info("Registering texture: '{0}' at '{1}'", tag, fileLocation);
	if (m_textureMap.find(tag) != m_textureMap.end()) 
	{
		m_logger->warn("Unable to register texture, tag: '{0}' is not unique", tag);
		return false;
	}

	//Tag is unique so it can be registered
	SDL_Surface *tmpSurface = IMG_Load(fileLocation.c_str());
	if (tmpSurface == NULL) 
	{
		m_logger->warn("Cannot find the file '{0}'. SDL Error: {1}", fileLocation, IMG_GetError());

		//Register this tag with the missing texture
		tmpSurface = IMG_Load("./data/gfx/null.png");
		Pos2N nullSize(16, 16);
		m_textureMap.insert({tag, std::unique_ptr<TextureSDL>(new TextureSDL(m_renderer, tmpSurface, nullSize))});
		SDL_FreeSurface(tmpSurface);
		tmpSurface = nullptr;
		return false;
	}
	else 
	{
		m_textureMap.insert({ tag, std::unique_ptr<TextureSDL>(new TextureSDL(m_renderer, tmpSurface, tileSize)) });
		SDL_FreeSurface(tmpSurface);
		tmpSurface = nullptr;
		m_logger->info("Texture file '{0}' has been registered", fileLocation);
		return true;
	}
}



bool Renderer::deregisterTexture(const std::string &tag)
{
	if (m_textureMap.find(tag) == m_textureMap.end()) 
	{
		m_logger->warn("Could not find tag: '{0}' unable to deregister texture", tag);
		return false;
	}

	m_logger->info("Deregistering texture '{0}'", tag);

	m_textureMap.erase(tag);

	m_logger->info("Texture '{0}' has been deregistered", tag);
	return true;
}



void Renderer::deregisterAllTextures()
{
	m_logger->info("Deregistering all textures");
	auto itr = m_textureMap.begin();
	while (itr != m_textureMap.end())
	{
		std::string tag = itr->first;
		m_logger->info("Deregistering texture '{0}'", tag);

		itr = m_textureMap.erase(itr);

		m_logger->info("Texture '{0}' has been deregistered", tag);
	}
}



bool Renderer::setDrawColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	SDL_SetRenderDrawColor(m_renderer, red, green, blue, alpha);
	return true;
}



bool Renderer::setTextureColor(const std::string &tag, uint8_t red, uint8_t green, uint8_t blue)
{
	SDL_SetTextureColorMod(this->getTexture(tag), red, green, blue);
	return true;
}



bool Renderer::setTextureAlpha(const std::string &tag, uint8_t alpha)
{
	SDL_SetTextureAlphaMod(this->getTexture(tag), alpha);
	return true;
}



bool Renderer::setTextureBlendMode(const std::string &tag, RendererBlendMode blendMode)
{
	switch (blendMode) 
	{
	case RendererBlendMode::NONE:
		SDL_SetTextureBlendMode(this->getTexture(tag), SDL_BLENDMODE_NONE);
		break;

	case RendererBlendMode::BLEND:
		SDL_SetTextureBlendMode(this->getTexture(tag), SDL_BLENDMODE_BLEND);
		break;

	case RendererBlendMode::ADD:
		SDL_SetTextureBlendMode(this->getTexture(tag), SDL_BLENDMODE_ADD);
		break;

	case RendererBlendMode::MOD:
		SDL_SetTextureBlendMode(this->getTexture(tag), SDL_BLENDMODE_MOD);
		break;
	}
	return true;
}



bool Renderer::present()
{
	SDL_RenderPresent(m_renderer);
	return true;
}



void Renderer::drawPoint(const Pos2D& pos)
{
	int code = SDL_RenderDrawPoint(m_renderer, static_cast<int>(pos.x + 0.5), static_cast<int>(pos.y + 0.5));
	if (code < 0) 
		m_logger->error("SDL Error while trying to draw a point: {0}", SDL_GetError());
}



void Renderer::drawLine(const Pos2D& startPos, const Pos2D& endPos)
{
	int code = SDL_RenderDrawLine(
		m_renderer, 
		static_cast<int>(startPos.x + 0.5), 
		static_cast<int>(startPos.y + 0.5), 
		static_cast<int>(endPos.x + 0.5), 
		static_cast<int>(endPos.y + 0.5)
	);
	if (code < 0) 
		m_logger->error("SDL Error while trying to draw a line: {0}", SDL_GetError());
}



void Renderer::drawRect(const Pos2D& pos, const Pos2N& dim, bool fill)
{
	SDL_Rect rect = { 
		static_cast<int>(pos.x + 0.5), 
		static_cast<int>(pos.y + 0.5), 
		dim.w, 
		dim.h 
	};
	int code = fill ? SDL_RenderFillRect(m_renderer, &rect) : SDL_RenderDrawRect(m_renderer, &rect);
	if (code < 0) 
		m_logger->error("SDL Error while trying to draw a rectangle: {0}", SDL_GetError());
}



void Renderer::drawSprite(const std::string& tag, const TilePos& pos, const TilePos& cameraOffset, const Pos2N& spriteLocation, const double angle, const bool flipSprite)
{
	//Select the right sprite from the sprite sheet
	Pos2N spriteSize(this->getTextureTileWidth(tag), this->getTextureTileHeight(tag));
	SDL_Rect spriteRect = {
		spriteLocation.u * spriteSize.w, 
		spriteLocation.v * spriteSize.h, 
		spriteSize.w, 
		spriteSize.h
	};

	double width = static_cast<double>(spriteSize.w) * m_scale;
	double height = static_cast<double>(spriteSize.h) * m_scale;
	double xPos = pos.x() - cameraOffset.x();
	double yPos = pos.y() - cameraOffset.y();

	SDL_Rect entityRect = {
		static_cast<int>(xPos + 0.5),
		static_cast<int>(yPos + 0.5),
		static_cast<int>(width + 0.5),
		static_cast<int>(height + 0.5)
	};

	SDL_RendererFlip flip = flipSprite ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	SDL_RenderCopyEx(m_renderer, this->getTexture(tag), &spriteRect, &entityRect, angle, NULL, flip);
}



void Renderer::drawSprite(const std::string& tag, const TilePos& pos, const TilePos& cameraOffset, const Pos2N& spriteLocation, const bool flipSprite)
{
	this->drawSprite(tag, pos, cameraOffset, spriteLocation, 0.0, flipSprite);
}



void Renderer::drawSprite(const Sprite& spriteIn, const TilePos& pos, const TilePos& cameraOffset)
{
	Pos2N spriteSize(this->getTextureTileWidth(spriteIn.tag()), this->getTextureTileHeight(spriteIn.tag()));
	SDL_Rect spriteRect = {
		spriteIn.index.u * spriteSize.w,
		spriteIn.index.v * spriteSize.h,
		(spriteIn.size.w + 1) * spriteSize.w - 1,
		(spriteIn.size.h + 1 ) * spriteSize.h - 1
	};

	float width = static_cast<float>(spriteSize.w) * spriteIn.scale;
	float height = static_cast<float>(spriteSize.h) * spriteIn.scale;
	double xPos = pos.x() - cameraOffset.x();
	double yPos = pos.y() - cameraOffset.y();

	SDL_Rect entityRect = {
		static_cast<int>(xPos + 0.5),
		static_cast<int>(yPos + 0.5),
		static_cast<int>(width + 0.5f),
		static_cast<int>(height + 0.5f)
	};

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	switch (spriteIn.fliped) 
	{
	case Sprite::Flip::NONE:
		flip = SDL_FLIP_NONE;
		break;

	case Sprite::Flip::HORIZONTAL:
		flip = SDL_FLIP_HORIZONTAL;
		break;

	case Sprite::Flip::VERTICAL:
		flip = SDL_FLIP_VERTICAL;
		break;
	}

	int code = SDL_RenderCopyEx(m_renderer, this->getTexture(spriteIn.tag()), &spriteRect, &entityRect, 0.0, NULL, flip);
	if (code < 0)
		m_logger->error("SDL Error while trying to draw '{0}' sprite: {1}", spriteIn.tag(), SDL_GetError());
}



void Renderer::setScale(float scaleIn)
{
	scaleIn <= 0.0f ? m_scale = 1.0f : m_scale = scaleIn;
}



void Renderer::begin(const std::shared_ptr<Camera>& cameraIn)
{
	m_camera = cameraIn;
}



void Renderer::end()
{
	m_camera.reset();
}



void Renderer::clear(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



void Renderer::clear()
{
	clear(0.1f, 0.1f, 0.1f, 1.0f);
}



void Renderer::drawQuad(const Pos3F& pos, const Pos2N& size, IMaterial& material)
{
	m_vbo.bind();
	m_ibo.bind();

	float vertices[] = {
		pos.x + static_cast<float>(size.w), pos.y + static_cast<float>(size.h), pos.z, 
		pos.x, pos.y + static_cast<float>(size.h), pos.z,
		pos.x, pos.y, pos.z,
		pos.x + static_cast<float>(size.w), pos.y, pos.z};
	m_vbo.submitData(vertices, sizeof(vertices));

	auto shaderPtr = m_shaders.get(material.getShaderName());
	auto shader = shaderPtr.lock();
	shader->bind();
	shader->setUniform("u_camera", ShaderUniform::Type::Mat4, m_camera->getViewProjection());
	material.submitData(shader);

	if (shader->validate())
		glDrawElements(GL_TRIANGLES, m_ibo.count(), GL_UNSIGNED_INT, nullptr);
	else
		m_logger->error("Shader '{0}' failed validation", material.getShaderName());
}



ShaderLibrarian& Renderer::shaderLibrarian()
{
	return m_shaders;
}



SDL_Texture* Renderer::getTexture(const std::string &tag)
{

	if(m_textureMap.find(tag) == m_textureMap.end())
	{
		m_logger->warn("Could not get the texture '{0}'", tag);
		return nullptr;
	}
	else 
		return m_textureMap[tag]->expose();
}



int Renderer::getTextureTileWidth(const std::string &tag)
{
	if(m_textureMap.find(tag) == m_textureMap.end())
	{
		m_logger->warn("Could not get the texture '{0}' width", tag);
		return 0;
	}
	else 
		return m_textureMap[tag]->getTileSize().w;
}



int Renderer::getTextureTileHeight(const std::string &tag)
{
	if(m_textureMap.find(tag) == m_textureMap.end())
	{
		m_logger->warn("Could not get the texture '{0}' height", tag);
		return 0;
	}
	else 
		return m_textureMap[tag]->getTileSize().h;
}



Pos2N Renderer::getTextureSize(const std::string &tag)
{
	return !m_hasBeenInit ? Pos2N() : Pos2N(this->getTextureTileWidth(tag), this->getTextureTileHeight(tag));
}








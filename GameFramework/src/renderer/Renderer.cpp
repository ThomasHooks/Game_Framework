#include <string>
#include <map>
#include <memory>

#include <SDL.h>
#include "SDL_image.h"
#include <spdlog/spdlog.h>

#include "Renderer.h"
#include "utilities/wrappers/SDLTextureWrapper.h"




Renderer::Renderer()
	: m_hasBeenInit(false), m_scale(1.0f), m_renderer(nullptr) 
{
	m_logger = Loggers::getLog();
}



Renderer::~Renderer() 
{
	m_logger->info("Stopping Rendering");
	m_logger->info("Freeing SDL renderer");
	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;
	m_logger->info("SDL renderer has been freed");

	this->deregisterAllTextures();
	m_logger->info("Rendering stopped");
}



void Renderer::init(SDL_Window *windowIn)
{
	if(!m_hasBeenInit) 
	{
		m_renderer = SDL_CreateRenderer(windowIn, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		m_logger->info("Renderer has been initialized");
		m_hasBeenInit = true;
	}
}



bool Renderer::registerTexture(const std::string& tag, const std::string& fileLocation, const Pos2N& tileSize)
{
	if(!m_hasBeenInit) 
	{
		m_logger->error("Cannot register textures, Renderer has not been initialized!");
		return false;
	}

	m_logger->info("Registering texture: '{0}' at '{1}'", tag, fileLocation);

	if(m_textureMap.find(tag) != m_textureMap.end()) 
	{
		m_logger->warn("Unable to register texture, tag: '{0}' is not unique", tag);
		return false;
	}

	//Tag is unique so it can be registered
	SDL_Surface *tmpSurface = IMG_Load(fileLocation.c_str());
	if(tmpSurface == NULL) 
	{
		//Could not find the sprite sheet
		std::string sdlMessage = IMG_GetError();
		m_logger->warn("Cannot find the file '{0}'. SDL Error: {1}", fileLocation, sdlMessage);

		//Register this tag with the missing texture
		tmpSurface = IMG_Load("./data/gfx/null.png");
		Pos2N nullSize(16, 16);
		m_textureMap.insert({tag, std::unique_ptr<SDLTextureWrapper>(new SDLTextureWrapper(m_renderer, tmpSurface, nullSize))});

		SDL_FreeSurface(tmpSurface);
		tmpSurface = nullptr;
		return false;
	}
	else 
	{
		//Sprite sheet was found
		m_textureMap.insert({ tag, std::unique_ptr<SDLTextureWrapper>(new SDLTextureWrapper(m_renderer, tmpSurface, tileSize)) });

		SDL_FreeSurface(tmpSurface);
		tmpSurface = nullptr;

		m_logger->info("Texture file '{0}' has been registered", fileLocation);
		return true;
	}
}



bool Renderer::deregisterTexture(const std::string &tag)
{
	if(m_hasBeenInit) 
	{
		if(m_textureMap.find(tag) == m_textureMap.end()) 
		{
			m_logger->warn("Could not find tag: '{0}' unable to deregister texture", tag);
			return false;
		}

		m_logger->info("Deregistering texture '{0}'", tag);

		m_textureMap.erase(tag);

		m_logger->info("Texture '{0}' has been deregistered", tag);
		return true;
	}
	else 
	{
		m_logger->error("Cannot deregister textures, Renderer has not been initialized!");
		return false;
	}
}



void Renderer::deregisterAllTextures()
{
	if(m_hasBeenInit) 
	{
		m_logger->info("Deregistering all textures");
		auto itr = m_textureMap.begin();
		while(itr != m_textureMap.end())
		{
			std::string tag = itr->first;
			m_logger->info("Deregistering texture '{0}'", tag);

			itr = m_textureMap.erase(itr);

			m_logger->info("Texture '{0}' has been deregistered", tag);
		}
	}
	else 
		m_logger->error("Cannot deregister textures, Renderer has not been initialized!");
}



bool Renderer::setDrawColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	if(m_hasBeenInit) 
	{
		SDL_SetRenderDrawColor(m_renderer, red, green, blue, alpha);
		return true;
	}
	else 
	{
		m_logger->error("Cannot set draw color, Renderer has not been initialized!");
		return false;
	}
}



bool Renderer::setTextureColor(const std::string &tag, uint8_t red, uint8_t green, uint8_t blue)
{
	if(m_hasBeenInit) 
	{
		SDL_SetTextureColorMod(this->getTexture(tag), red, green, blue);
		return true;
	}
	else 
	{
		m_logger->error("Cannot set texture color, Renderer has not been initialized!");
		return false;
	}
}



bool Renderer::setTextureAlpha(const std::string &tag, uint8_t alpha)
{
	if(m_hasBeenInit) 
	{
		SDL_SetTextureAlphaMod(this->getTexture(tag), alpha);
		return true;
	}
	else 
	{
		m_logger->error("Cannot set texture alpha, Renderer has not been initialized!");
		return false;
	}
}



bool Renderer::setTextureBlendMode(const std::string &tag, RendererBlendMode blendMode)
{
	if(!m_hasBeenInit) 
	{
		m_logger->error("Cannot set texture blend mode, Renderer has not been initialized!");
		return false;
	}

	switch(blendMode) 
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



bool Renderer::clear()
{
	if(m_hasBeenInit) 
	{
		SDL_RenderClear(m_renderer);
		return true;
	}
	else 
	{
		m_logger->error("Cannot clear, Renderer has not been initialized!");
		return false;
	}
}



bool Renderer::present()
{
	if(m_hasBeenInit) 
	{
		SDL_RenderPresent(m_renderer);
		return true;
	}
	else 
	{
		m_logger->error("Cannot present, Renderer has not been initialized!");
		return false;
	}
}



void Renderer::drawPoint(const Pos2D& pos)
{
	if(m_hasBeenInit) 
	{
		int code = SDL_RenderDrawPoint(m_renderer, static_cast<int>(pos.x + 0.5), static_cast<int>(pos.y + 0.5));
		if(code < 0) 
		{
			std::string sdlMessage = SDL_GetError();
			m_logger->error("SDL Error while trying to draw a point: {0}", sdlMessage);
		}
	}
	else 
		m_logger->error("Cannot draw point, Renderer has not been initialized!");
}



void Renderer::drawLine(const Pos2D& startPos, const Pos2D& endPos)
{
	if(m_hasBeenInit) 
	{
		int code = SDL_RenderDrawLine(m_renderer, 
			static_cast<int>(startPos.x + 0.5), 
			static_cast<int>(startPos.y + 0.5), 
			static_cast<int>(endPos.x + 0.5), 
			static_cast<int>(endPos.y + 0.5)
		);
		if(code < 0) 
		{
			std::string sdlMessage = SDL_GetError();
			m_logger->error("SDL Error while trying to draw a line: {0}", sdlMessage);
		}
	}
	else 
		m_logger->error("Cannot draw line, Renderer has not been initialized!");
}



void Renderer::drawRect(const Pos2D& pos, const Pos2N& dim, bool fill)
{
	if(m_hasBeenInit) 
	{
		SDL_Rect rect = { static_cast<int>(pos.x + 0.5), static_cast<int>(pos.y + 0.5), dim.w, dim.h };
		int code = fill ? SDL_RenderFillRect(m_renderer, &rect) : SDL_RenderDrawRect(m_renderer, &rect);
		if(code < 0) 
		{
			std::string sdlMessage = SDL_GetError();
			m_logger->error("SDL Error while trying to draw a rectangle: {0}", sdlMessage);
		}
	}

	else 
		m_logger->error("Cannot draw rectangle, Renderer has not been initialized!");
}



void Renderer::drawSprite(const std::string& tag, const TilePos& pos, const TilePos& cameraOffset, const Pos2N& spriteLocation, const double angle, const bool flipSprite)
{
	if(m_hasBeenInit) 
	{
		Pos2N spriteSize(this->getTextureTileWidth(tag), this->getTextureTileHeight(tag));
		//Select the right sprite from the sprite sheet
		SDL_Rect spriteRect = {
			spriteLocation.u * spriteSize.w, 
			spriteLocation.v * spriteSize.h, 
			spriteSize.w, 
			spriteSize.h
		};

		//calculate the entity's/tile's size and location in the world
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
	else
		m_logger->error("Cannot draw sprite, Renderer has not been initialized!");
}



void Renderer::drawSprite(const std::string& tag, const TilePos& pos, const TilePos& cameraOffset, const Pos2N& spriteLocation, const bool flipSprite)
{
	this->drawSprite(tag, pos, cameraOffset, spriteLocation, 0.0, flipSprite);
}



void Renderer::setScale(float scaleIn)
{
	scaleIn <= 0.0f ? m_scale = 1.0f : m_scale = scaleIn;
}



SDL_Texture* Renderer::getTexture(const std::string &tag)
{
	if(!m_hasBeenInit) 
		return nullptr;

	if(m_textureMap.find(tag) == m_textureMap.end())
	{
		m_logger->warn("Could not get the texture '{0}'", tag);
		return nullptr;
	}
	else 
		return m_textureMap[tag]->getTexture();
}



int Renderer::getTextureTileWidth(const std::string &tag)
{
	if(!this->m_hasBeenInit) 
		return 0;

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
	if(!m_hasBeenInit) 
		return 0;

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








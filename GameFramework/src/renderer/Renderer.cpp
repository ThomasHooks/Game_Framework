#include <string>
#include <map>
#include <memory>

#include <SDL.h>
#include "SDL_image.h"
#include <spdlog/spdlog.h>

#include "Renderer.h"
#include "utilities/physics/Dimension.h"
#include "utilities/physics/Position.h"
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



/*
 * @param	windowIn A pointer to the current window
 *
 * Initializes the Renderer Manager and must be called before using any other methods
 */
void Renderer::init(SDL_Window *windowIn)
{
	if(!m_hasBeenInit) 
	{
		m_renderer = SDL_CreateRenderer(windowIn, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		m_logger->info("Renderer has been initialized");
		m_hasBeenInit = true;
	}
}



/*
 * @param	tag The ID of the texture
 *
 * @param	fileLocation The location of the texture file
 *
 * @param	tileSize The dimensions of tiles in the texture
 *
 * @return	True if the texture was successfully registered
 *
 * Register a texture to the renderer manager
 */
bool Renderer::registerTexture(const std::string &tag, const std::string &fileLocation, Dimension &tileSize)
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
		Dimension nullSize(16, 16);
		m_textureMap.insert({tag, std::unique_ptr<SDLTextureWrapper>(new SDLTextureWrapper(m_renderer, tmpSurface, nullSize))});

		SDL_FreeSurface(tmpSurface);
		tmpSurface = nullptr;
		return false;
	}
	else 
	{
		//Sprite sheet was found
		m_textureMap.insert({tag, std::unique_ptr<SDLTextureWrapper>(new SDLTextureWrapper(m_renderer, tmpSurface, tileSize))});

		SDL_FreeSurface(tmpSurface);
		tmpSurface = nullptr;

		m_logger->info("Texture file '{0}' has been registered", fileLocation);
		return true;
	}
}



/*
 * @param	tag The ID of the texture to be deregistered
 *
 * @return	True if tag was successfully deregistered
 *
 * Deregister the texture specified by the tag argument
 */
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



//Deregister all textures in the Renderer Manager
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



/*
 * @param	red The amount of red in the new color
 *
 * @param	green The amount of green in the new color
 *
 * @param	blue The amount of blue in the new color
 *
 * @param	alpha The new opacity
 *
 * @return	True if the draw color was successfully changed
 *
 * Sets the drawing color
 */
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



/*
 * @param	tag The ID of the texture
 *
 * @param	red The amount of red in the new color
 *
 * @param	green The amount of green in the new color
 *
 * @param	blue The amount of blue in the new color
 *
 * @return	True if the textures color was successfully changed
 *
 * Sets the given texture's color
 */
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



/*
 * @param	tag The ID of the texture
 *
 * @param	alpha The new opacity for the texture
 *
 * @return	True if the textures opacity was successfully changed
 *
 * Sets the given texture's opacity
 */
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



/*
 * @param	tag The ID of the texture
 *
 * @param	blendMode The new blending mode
 *
 * @return	True if the textures blend mode was successfully changed
 *
 * Sets the given textures blend mode
 */
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



/*
 * @return	True if the renderer was cleared
 *
 * Clears the renderer and fill it in with the current draw color
 */
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



/*
 * @return	True if the renderer was presented
 *
 * Presents what has been drawn to the renderer on the screen
 */
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



/*
 * @param	pos The coordinates of the Point
 *
 * Draws a point at the given coordinates to the renderer
 */
void Renderer::drawPoint(const Position &pos)
{
	if(m_hasBeenInit) 
	{
		int code = SDL_RenderDrawPoint(m_renderer, pos.xPosN(), pos.yPosN());
		if(code < 0) 
		{
			std::string sdlMessage = SDL_GetError();
			m_logger->error("SDL Error while trying to draw a point: {0}", sdlMessage);
		}
	}
	else 
		m_logger->error("Cannot draw point, Renderer has not been initialized!");
}



/*
 * @param	startPos The coordinates of the starting point of the Line
 *
 * @param	endPos The coordinates of the ending point of the Line
 *
 * Draws a line to the renderer
 */
void Renderer::drawLine(const class Position &startPos, const class Position &endPos)
{
	if(m_hasBeenInit) 
	{
		int code = SDL_RenderDrawLine(m_renderer, startPos.xPosN(), startPos.yPosN(), endPos.xPosN(), endPos.yPosN());
		if(code < 0) 
		{
			std::string sdlMessage = SDL_GetError();
			m_logger->error("SDL Error while trying to draw a line: {0}", sdlMessage);
		}
	}
	else 
		m_logger->error("Cannot draw line, Renderer has not been initialized!");
}



/*
 * @param	pos The coordinates of the rectangle
 *
 * @param	dim The dimensions of the rectangle
 *
 * @param	fill Flag to draw a filled in rectangle
 *
 * Draws a rectangle to the renderer
 */
void Renderer::drawRect(const class Position &pos, const struct Dimension &dim, bool fill)
{
	if(m_hasBeenInit) 
	{
		SDL_Rect rect = {pos.xPosN(), pos.yPosN(), dim.width, dim.height};
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



/*
 * @param	tag The tag ID of the entity/tile
 *
 * @param	pos The coordinates of the entity/tile
 *
 * @param	cameraOffset The coordinates of the camera
 *
 * @param	spriteLocation The location of the sprite in the sprite sheet
 *
 * @param	angle The location of the sprite in the sprite sheet
 *
 * @param	flipSprite If the sprite should be flipped
 *
 * Draws a sprite given by tag to the renderer
 */
void Renderer::drawSprite(const std::string &tag, const Position &pos, const Position &cameraOffset, const Dimension &spriteLocation, const double angle, const bool flipSprite)
{
	if(m_hasBeenInit) 
	{
		Dimension spriteSize(this->getTextureTileWidth(tag), this->getTextureTileHeight(tag));
		//Select the right sprite from the sprite sheet
		SDL_Rect spriteRect = {
			spriteLocation.width * spriteSize.width, 
			spriteLocation.height * spriteSize.height, 
			spriteSize.width, 
			spriteSize.height
		};

		//calculate the entity's/tile's size and location in the world
		double width = static_cast<double>(spriteSize.width) * m_scale;
		double height = static_cast<double>(spriteSize.height) * m_scale;
		double xPos = pos.xPos() - cameraOffset.xPos();
		double yPos = pos.yPosN() - cameraOffset.yPos();

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



/*
 * @param	tag The tag ID of the entity/tile
 *
 * @param	pos The coordinates of the entity/tile
 *
 * @param	cameraOffset The coordinates of the camera
 *
 * @param	spriteLocation The location of the sprite in the sprite sheet
 *
 * @param	flipSprite If the sprite should be flipped
 *
 * Draws a sprite given by tag to the renderer
 */
void Renderer::drawSprite(const std::string &tag, const Position &pos, const Position &cameraOffset, const Dimension &spriteLocation, const bool flipSprite)
{
	this->drawSprite(tag, pos, cameraOffset, spriteLocation, 0.0, flipSprite);
}



/*
 * @param	scaleIn The new scale for all rendering
 *
 * The new scale cannot be zero or negative, and if scaleIn is either it will default to 1.0
 */
void Renderer::setScale(float scaleIn)
{
	scaleIn <= 0.0f ? m_scale = 1.0f : m_scale = scaleIn;
}



/*
 * @nullable
 *
 * @param	tag The ID of the texture
 *
 * @return	Pointer to the texture, or null if the tag is not found
 *
 * Gets the texture specified by the tag. If it doesn't find the texture it will return a null pointer
 */
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



/*
 * @param	tag The ID of the texture
 *
 * @return	The tile width of the textures, or 0 if not found
 *
 * Gets the tile width of the texture specified by the tag. If it doesn't find the texture it will return 0
 */
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
		return m_textureMap[tag]->getTileSize().width;
}



/*
 * @param	tag The ID of the texture
 *
 * @return	The tile height of the textures, or 0 if not found
 *
 * Gets the tile height of the texture specified by the tag. If it doesn't find the texture it will return 0
 */
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
		return m_textureMap[tag]->getTileSize().height;
}



/*
 * @param	tag The ID of the texture
 *
 * @return	The dimensions of the texture
 *
 * Gets a copy of  tile dimensions of the texture specified by the tag
 * if it doesn't find the texture it will return a size of (0, 0)
 */
Dimension Renderer::getTextureSize(const std::string &tag)
{
	return !m_hasBeenInit ? Dimension() : Dimension(this->getTextureTileWidth(tag), this->getTextureTileHeight(tag));
}








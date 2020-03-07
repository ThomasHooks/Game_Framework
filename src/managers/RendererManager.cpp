//============================================================================
// Name       		: RendererManager.cpp
// Author     		: Thomas Hooks
// Last Modified	: 03/06/2020
//============================================================================




#include <SDL.h>
#include "SDL_image.h"

#include <string>
#include <map>
#include <memory>

#include "RendererManager.h"
#include "../utilities/GameLogger.h"
#include "../utilities/Position.h"
#include "../utilities/Dimension.h"
#include "../utilities/SDLTextureWrapper.h"




RendererManager::RendererManager(class GameLogger *logger_ptr)
	: hasBeenInit(false),
	  scale(1.0f),
	  logger(logger_ptr),
	  renderer(nullptr) {}



RendererManager::~RendererManager() {

	logger->message(Level::INFO, "Freeing renderer", Output::TXT_FILE);
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	logger->message(Level::INFO, "Renderer has been freed", Output::TXT_FILE);

	this->deregisterAllTextures();
}



void RendererManager::init(SDL_Window *windowIn){
	/*
	 * @param	windowIn A pointer to the current window
	 *
	 * This method is used to initialize the Renderer Manager and must be called before using any other Renderer Manager methods
	 */




	if(!this->hasBeenInit) {
		this->renderer = SDL_CreateRenderer(windowIn, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		logger->message(Level::INFO, "Renderer has been initialized", Output::TXT_FILE);
		this->hasBeenInit = true;
	}
}



bool RendererManager::registerTexture(const std::string &tag, const std::string &fileLocation, Dimension &tileSize){
	/*
	 * @param	tag The ID of the texture
	 *
	 * @param	fileLocation The location of the texture file
	 *
	 * @param	tileSize The dimensions of tiles in the texture
	 *
	 * @return	True if the texture was successfully registered and False if otherwise
	 *
	 * This method will register a texture to the renderer manager
	 */




	if(!this->hasBeenInit) return false;

	logger->message(Level::INFO, "Registering texture '" + tag + "' at "+ fileLocation, Output::TXT_FILE);
	if(textureMap.find(tag) == textureMap.end()) {
		//Tag is unique so it can be registered

		SDL_Surface *tmpSurface = IMG_Load(fileLocation.c_str());
		if(tmpSurface == NULL) {
			//TODO Add a default sprite for that tag

			SDL_FreeSurface(tmpSurface);
			tmpSurface = nullptr;

			std::string sdlMessage = IMG_GetError();
			logger->message(Level::ERROR, "Cannot find the file: '" + fileLocation + "'. SDL: " + sdlMessage,	Output::TXT_FILE);
			return false;
		}

		textureMap.insert({tag, std::unique_ptr<SDLTextureWrapper>(new SDLTextureWrapper(this->renderer, tmpSurface, tileSize))});

		SDL_FreeSurface(tmpSurface);
		tmpSurface = nullptr;

		logger->message(Level::INFO, "File '" + fileLocation + "' has been registered", Output::TXT_FILE);
		return true;

	}

	logger->message(Level::WARNING, "Unable to register texture, tag: '" + tag +"' is not unique", Output::TXT_FILE);
	return false;
}



bool RendererManager::deregisterTexture(const std::string &tag){
	/*
	 * @param	tag The ID of the texture to be deregistered
	 *
	 * @return	True if tag was successfully deregistered, False otherwise
	 *
	 * This method will deregister the texture specified by the tag argument
	 */




	if(!hasBeenInit) return false;

	if(textureMap.find(tag) == textureMap.end()){
		logger->message(Level::WARNING, "Could not find tag: '" + tag + "' unable to deregister texture", Output::TXT_FILE);
		return false;
	}

	logger->message(Level::INFO, "Deregistering texture '" + tag +"'", Output::TXT_FILE);

	textureMap.erase(tag);

	logger->message(Level::INFO, "Texture '" + tag +"' has been deregistered", Output::TXT_FILE);
	return true;
}



void RendererManager::deregisterAllTextures(){
	/*
	 * This method will deregister all textures in the Renderer Manager
	 */




	if(!this->hasBeenInit) return;

	logger->message(Level::INFO, "Deregistering all textures", Output::TXT_FILE);
	auto itr = textureMap.begin();
	while(itr != textureMap.end()){

		std::string tag = itr->first;
		logger->message(Level::INFO, "Deregistering texture '" + tag + "'", Output::TXT_FILE);

		 itr = textureMap.erase(itr);

		 logger->message(Level::INFO, "Texture '" + tag + "' has been deregistered", Output::TXT_FILE);
	}
}



bool RendererManager::setDrawColor(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha){
	/*
	 *
	 */




	if(this->hasBeenInit) {
		SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
		return true;
	}
	else {
		logger->message(Level::ERROR, "Cannot set draw color, Renderer has not been initialized!", Output::TXT_FILE);
		return false;
	}
}



bool RendererManager::setTextureColor(const std::string &tag, uint32_t red, uint32_t green, uint32_t blue){
	/*
	 *
	 */




	if(this->hasBeenInit) {
		SDL_SetTextureColorMod(this->getTexture(tag), red, green, blue);
		return true;
	}
	else {
		logger->message(Level::ERROR, "Cannot set texture color, Renderer has not been initialized!", Output::TXT_FILE);
		return false;
	}
}



bool RendererManager::setTextureAlpha(const std::string &tag, uint32_t alpha){
	/*
	 *
	 */




	if(this->hasBeenInit) {
		SDL_SetTextureAlphaMod(this->getTexture(tag), alpha);
		return true;
	}
	else {
		logger->message(Level::ERROR, "Cannot set texture alpha, Renderer has not been initialized!", Output::TXT_FILE);
		return false;
	}
}



bool RendererManager::setTextureBlendMode(const std::string &tag, EnumBlendMode blendMode){
	/*
	 * @param	tag The ID of the texture
	 *
	 * @param	blendMode The new blending mode
	 */




	if(!this->hasBeenInit) {
		logger->message(Level::ERROR, "Cannot set texture blend mode, Renderer has not been initialized!", Output::TXT_FILE);
		return false;
	}

	switch(blendMode) {

	case EnumBlendMode::NONE:
		SDL_SetTextureBlendMode(this->getTexture(tag), SDL_BLENDMODE_NONE);
		break;

	case EnumBlendMode::BLEND:
		SDL_SetTextureBlendMode(this->getTexture(tag), SDL_BLENDMODE_BLEND);
		break;

	case EnumBlendMode::ADD:
		SDL_SetTextureBlendMode(this->getTexture(tag), SDL_BLENDMODE_ADD);
		break;

	case EnumBlendMode::MOD:
		SDL_SetTextureBlendMode(this->getTexture(tag), SDL_BLENDMODE_MOD);
		break;
	}


	return true;
}



bool RendererManager::clear(){
	/*
	 * This method will clear the screen and fill it in with the current draw color
	 */




	if(this->hasBeenInit) {
		SDL_RenderClear(this->renderer);
		return true;
	}
	else {
		logger->message(Level::ERROR, "Cannot clear, Renderer has not been initialized!", Output::TXT_FILE);
		return false;
	}
}



bool RendererManager::present(){
	/*
	 * This method will present what has been drawn to the renderer on the screen
	 */




	if(this->hasBeenInit) {
		SDL_RenderPresent(this->renderer);
		return true;
	}
	else {
		logger->message(Level::ERROR, "Cannot present, Renderer has not been initialized!", Output::TXT_FILE);
		return false;
	}
}



void RendererManager::drawPoint(const Position &pos){
	/*
	 * @param	pos		The coordinates of the Point
	 */




	if(this->hasBeenInit) {
		int code = SDL_RenderDrawPoint(this->renderer, pos.xPosN(), pos.yPosN());
		if(code < 0) {
			std::string sdlMessage = SDL_GetError();
			logger->message(Level::ERROR, "SDL Error while trying to draw a point: " + sdlMessage, Output::CONSOLE);
		}
	}

	else logger->message(Level::ERROR, "Cannot draw point, Renderer has not been initialized!", Output::TXT_FILE);
}



void RendererManager::drawLine(const class Position &startPos, const class Position &endPos){
	/*
	 * @param	startPos	The coordinates of the starting point of the Line
	 *
	 * @param	endPos		The coordinates of the ending point of the Line
	 */




	if(this->hasBeenInit) {
		int code = SDL_RenderDrawLine(this->renderer,
				startPos.xPosN(),
				startPos.yPosN(),
				endPos.xPosN(),
				endPos.yPosN());

		if(code < 0) {
			std::string sdlMessage = SDL_GetError();
			logger->message(Level::ERROR, "SDL Error while trying to draw a line: " + sdlMessage, Output::CONSOLE);
		}
	}

	else logger->message(Level::ERROR, "Cannot draw rectangle, Renderer has not been initialized!", Output::TXT_FILE);
}



void RendererManager::drawRect(const class Position &pos, const class Dimension &dim, bool fill){
	/*
	 * @param	pos		The coordinates of the rectangle
	 *
	 * @param	dim		The dimensions of the rectangle
	 *
	 * @param	fill	Flag to draw a filled in rectangle
	 */




	if(this->hasBeenInit) {
		SDL_Rect rect = {pos.xPosN(), pos.yPosN(), dim.width, dim.height};

		int code = fill ? SDL_RenderFillRect(this->renderer, &rect) : SDL_RenderDrawRect(this->renderer, &rect);

		if(code < 0) {
			std::string sdlMessage = SDL_GetError();
			logger->message(Level::ERROR, "SDL Error while trying to draw a rectangle: " + sdlMessage, Output::CONSOLE);
		}
	}

	else logger->message(Level::ERROR, "Cannot draw rectangle, Renderer has not been initialized!", Output::TXT_FILE);
}



void RendererManager::drawSprite(const std::string &tag,
		const Position &pos,
		const Position &cameraOffset,
		const Dimension &spriteLocation,
		const bool flipSprite){
	/*
	 * @param	tag The tag ID of the entity/tile
	 *
	 * @param	pos The coordinates of the entity/tile
	 *
	 * @param	cameraOffset The coordinates of the camera
	 *
	 * @param	spriteSize The dimensions of the sprite on the sprite sheet
	 *
	 * @param	spriteLocation The location of the sprite in the sprite sheet
	 */




	if(this->hasBeenInit) {

		Dimension spriteSize(this->getTextureTileWidth(tag), this->getTextureTileHeight(tag));
		//Select the right sprite from the sprite sheet
		SDL_Rect spriteRect = {spriteLocation.width * spriteSize.width,
				spriteLocation.height * spriteSize.height,
				spriteSize.width,
				spriteSize.height};

		//calculate the entity's/tile's size and location in the world
		int xPos = pos.xPosN() - cameraOffset.xPosN() * spriteSize.width;
		int yPos = pos.yPosN() - cameraOffset.yPosN() * spriteSize.height;
		SDL_Rect entityRect = {xPos,
				yPos,
				static_cast<int>((spriteSize.width * this->scale) + 0.5f),
				static_cast<int>((spriteSize.height * this->scale) + 0.5f)};

		SDL_RendererFlip flip = flipSprite ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

		SDL_RenderCopyEx(this->renderer, this->getTexture(tag), &spriteRect, &entityRect, 0, NULL, flip);
	}

	else logger->message(Level::ERROR, "Cannot render sprite, Renderer has not been initialized!", Output::TXT_FILE);
}



void RendererManager::setScale(float scaleIn){
	/*
	 * @param	scaleIn The new scale for all rendering
	 *
	 * The new scale cannot be zero or negative, and if scaleIn is either it will default to 1.0
	 */




	scaleIn <= 0.0f ? this->scale = 1.0f : this->scale = scaleIn;
}



//@nullable
SDL_Texture* RendererManager::getTexture(const std::string &tag){
	/*
	 * @param	tag The ID of the texture
	 *
	 * @return	Pointer to the texture, or null if the tag is not found
	 *
	 * This method will return a pointer to the texture specified by the tag.
	 * If it doesn't find the texture it will return a null pointer
	 */




	if(!this->hasBeenInit) return nullptr;

	if(textureMap.find(tag) == textureMap.end()){

		logger->message(Level::WARNING,
				"Could not get the texture '" + tag + "'",
				Output::TXT_FILE);

		return nullptr;
	}

	else return textureMap[tag]->getTexture();
}



int RendererManager::getTextureTileWidth(const std::string &tag){
	/*
	 * @param	tag The ID of the texture
	 *
	 * @return	The tile width of the textures, or 0 if not found
	 *
	 * This method will get the tile width of the texture specified by the tag.
	 * If it doesn't find the texture it will return 0
	 */




	if(!this->hasBeenInit) return 0;

	if(textureMap.find(tag) == textureMap.end()){

		logger->message(Level::WARNING, "Could not get the texture '" + tag + "' width", Output::TXT_FILE);
		return 0;
	}

	else return textureMap[tag]->getTileSize().width;
}



int RendererManager::getTextureTileHeight(const std::string &tag){
	/*
	 * @param	tag The ID of the texture
	 *
	 * @return	The tile height of the textures, or 0 if not found
	 *
	 * This method will get the tile height of the texture specified by the tag
	 * If it doesn't find the texture it will return 0
	 */




	if(!this->hasBeenInit) return 0;

	if(textureMap.find(tag) == textureMap.end()){

		logger->message(Level::WARNING, "Could not get the texture '" + tag + "' height", Output::TXT_FILE);
		return 0;
	}

	else return textureMap[tag]->getTileSize().height;
}








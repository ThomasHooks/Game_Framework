//============================================================================
// Name       		: RendererManager.cpp
// Author     		: Thomas Hooks
// Last Modified	: 04/04/2020
//============================================================================




#include <SDL.h>
#include "SDL_image.h"

#include <string>
#include <map>
#include <memory>

#include "RendererManager.h"
#include "../utilities/GameLogger.h"
#include "../utilities/physics/Dimension.h"
#include "../utilities/physics/Position.h"
#include "../utilities/wrappers/SDLTextureWrapper.h"




RendererManager::RendererManager(class GameLogger *logger_ptr)
	: hasBeenInit(false),
	  scale(1.0f),
	  logger(logger_ptr),
	  renderer(nullptr) {}



RendererManager::~RendererManager() {

	logger->message(EnumLogLevel::INFO, "Stopping Renderer Manager", EnumLogOutput::TXT_FILE);
	logger->message(EnumLogLevel::INFO, "Freeing SDL renderer", EnumLogOutput::TXT_FILE);
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	logger->message(EnumLogLevel::INFO, "SDL renderer has been freed", EnumLogOutput::TXT_FILE);

	this->deregisterAllTextures();
	logger->message(EnumLogLevel::INFO, "Rendering stopped", EnumLogOutput::TXT_FILE);
}



/*
 * @param	windowIn A pointer to the current window
 *
 * Initializes the Renderer Manager and must be called before using any other methods
 */
void RendererManager::init(SDL_Window *windowIn){

	if(!this->hasBeenInit) {
		this->renderer = SDL_CreateRenderer(windowIn, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		logger->message(EnumLogLevel::INFO, "Renderer has been initialized", EnumLogOutput::TXT_FILE);
		this->hasBeenInit = true;
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
bool RendererManager::registerTexture(const std::string &tag, const std::string &fileLocation, Dimension &tileSize){

	if(!this->hasBeenInit) {
		logger->message(EnumLogLevel::ERROR, "Cannot register textures, Renderer has not been initialized!", EnumLogOutput::TXT_FILE);
		return false;
	}

	logger->message(EnumLogLevel::INFO, "Registering texture '" + tag + "' at "+ fileLocation, EnumLogOutput::TXT_FILE);

	if(textureMap.find(tag) != textureMap.end()) {
		logger->message(EnumLogLevel::WARNING, "Unable to register texture, tag: '" + tag +"' is not unique", EnumLogOutput::TXT_FILE);
		return false;
	}

	//Tag is unique so it can be registered
	SDL_Surface *tmpSurface = IMG_Load(fileLocation.c_str());
	if(tmpSurface == NULL) {

		//Could not find the sprite sheet
		std::string sdlMessage = IMG_GetError();
		logger->message(EnumLogLevel::WARNING, "Cannot find the file '" + fileLocation + "'. SDL: " + sdlMessage, EnumLogOutput::TXT_FILE);

		//Register this tag with the missing texture
		tmpSurface = IMG_Load("./data/gfx/null.png");
		Dimension nullSize(16, 16);
		textureMap.insert({tag,
			std::unique_ptr<SDLTextureWrapper>(new SDLTextureWrapper(this->renderer, tmpSurface, nullSize))});

		SDL_FreeSurface(tmpSurface);
		tmpSurface = nullptr;
		return false;
	}
	else {
		//Sprite sheet was found
		textureMap.insert({tag,
			std::unique_ptr<SDLTextureWrapper>(new SDLTextureWrapper(this->renderer, tmpSurface, tileSize))});

		SDL_FreeSurface(tmpSurface);
		tmpSurface = nullptr;

		logger->message(EnumLogLevel::INFO, "File '" + fileLocation + "' has been registered", EnumLogOutput::TXT_FILE);
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
bool RendererManager::deregisterTexture(const std::string &tag){

	if(hasBeenInit) {

		if(textureMap.find(tag) == textureMap.end()) {
			logger->message(EnumLogLevel::WARNING, "Could not find tag: '" + tag + "' unable to deregister texture", EnumLogOutput::TXT_FILE);
			return false;
		}

		logger->message(EnumLogLevel::INFO, "Deregistering texture '" + tag +"'", EnumLogOutput::TXT_FILE);

		textureMap.erase(tag);

		logger->message(EnumLogLevel::INFO, "Texture '" + tag +"' has been deregistered", EnumLogOutput::TXT_FILE);
		return true;
	}
	else {
		logger->message(EnumLogLevel::ERROR, "Cannot deregister textures, Renderer has not been initialized!", EnumLogOutput::TXT_FILE);
		return false;
	}
}



//Deregister all textures in the Renderer Manager
void RendererManager::deregisterAllTextures(){

	if(this->hasBeenInit) {

		logger->message(EnumLogLevel::INFO, "Deregistering all textures", EnumLogOutput::TXT_FILE);
		auto itr = textureMap.begin();
		while(itr != textureMap.end()){

			std::string tag = itr->first;
			logger->message(EnumLogLevel::INFO, "Deregistering texture '" + tag + "'", EnumLogOutput::TXT_FILE);

			itr = textureMap.erase(itr);

			logger->message(EnumLogLevel::INFO, "Texture '" + tag + "' has been deregistered", EnumLogOutput::TXT_FILE);
		}
	}
	else logger->message(EnumLogLevel::ERROR, "Cannot deregister textures, Renderer has not been initialized!", EnumLogOutput::TXT_FILE);
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
bool RendererManager::setDrawColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha){

	if(this->hasBeenInit) {
		SDL_SetRenderDrawColor(this->renderer, red, green, blue, alpha);
		return true;
	}
	else {
		logger->message(EnumLogLevel::ERROR, "Cannot set draw color, Renderer has not been initialized!", EnumLogOutput::TXT_FILE);
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
bool RendererManager::setTextureColor(const std::string &tag, uint8_t red, uint8_t green, uint8_t blue){

	if(this->hasBeenInit) {
		SDL_SetTextureColorMod(this->getTexture(tag), red, green, blue);
		return true;
	}
	else {
		logger->message(EnumLogLevel::ERROR, "Cannot set texture color, Renderer has not been initialized!", EnumLogOutput::TXT_FILE);
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
bool RendererManager::setTextureAlpha(const std::string &tag, uint8_t alpha){

	if(this->hasBeenInit) {
		SDL_SetTextureAlphaMod(this->getTexture(tag), alpha);
		return true;
	}
	else {
		logger->message(EnumLogLevel::ERROR, "Cannot set texture alpha, Renderer has not been initialized!", EnumLogOutput::TXT_FILE);
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
bool RendererManager::setTextureBlendMode(const std::string &tag, EnumBlendMode blendMode){

	if(!this->hasBeenInit) {
		logger->message(EnumLogLevel::ERROR, "Cannot set texture blend mode, Renderer has not been initialized!", EnumLogOutput::TXT_FILE);
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



/*
 * @return	True if the renderer was cleared
 *
 * Clears the renderer and fill it in with the current draw color
 */
bool RendererManager::clear(){

	if(this->hasBeenInit) {
		SDL_RenderClear(this->renderer);
		return true;
	}
	else {
		logger->message(EnumLogLevel::ERROR, "Cannot clear, Renderer has not been initialized!", EnumLogOutput::TXT_FILE);
		return false;
	}
}



/*
 * @return	True if the renderer was presented
 *
 * Presents what has been drawn to the renderer on the screen
 */
bool RendererManager::present(){

	if(this->hasBeenInit) {
		SDL_RenderPresent(this->renderer);
		return true;
	}
	else {
		logger->message(EnumLogLevel::ERROR, "Cannot present, Renderer has not been initialized!", EnumLogOutput::TXT_FILE);
		return false;
	}
}



/*
 * @param	pos The coordinates of the Point
 *
 * Draws a point at the given coordinates to the renderer
 */
void RendererManager::drawPoint(const Position &pos){

	if(this->hasBeenInit) {
		int code = SDL_RenderDrawPoint(this->renderer, pos.xPosN(), pos.yPosN());
		if(code < 0) {
			std::string sdlMessage = SDL_GetError();
			logger->message(EnumLogLevel::ERROR, "SDL Error while trying to draw a point: " + sdlMessage, EnumLogOutput::CONSOLE);
		}
	}

	else logger->message(EnumLogLevel::ERROR, "Cannot draw point, Renderer has not been initialized!", EnumLogOutput::TXT_FILE);
}



/*
 * @param	startPos The coordinates of the starting point of the Line
 *
 * @param	endPos The coordinates of the ending point of the Line
 *
 * Draws a line to the renderer
 */
void RendererManager::drawLine(const class Position &startPos, const class Position &endPos){

	if(this->hasBeenInit) {
		int code = SDL_RenderDrawLine(this->renderer,
				startPos.xPosN(),
				startPos.yPosN(),
				endPos.xPosN(),
				endPos.yPosN());

		if(code < 0) {
			std::string sdlMessage = SDL_GetError();
			logger->message(EnumLogLevel::ERROR, "SDL Error while trying to draw a line: " + sdlMessage, EnumLogOutput::CONSOLE);
		}
	}

	else logger->message(EnumLogLevel::ERROR, "Cannot draw rectangle, Renderer has not been initialized!", EnumLogOutput::TXT_FILE);
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
void RendererManager::drawRect(const class Position &pos, const class Dimension &dim, bool fill){

	if(this->hasBeenInit) {
		SDL_Rect rect = {pos.xPosN(), pos.yPosN(), dim.width, dim.height};

		int code = fill ? SDL_RenderFillRect(this->renderer, &rect) : SDL_RenderDrawRect(this->renderer, &rect);

		if(code < 0) {
			std::string sdlMessage = SDL_GetError();
			logger->message(EnumLogLevel::ERROR, "SDL Error while trying to draw a rectangle: " + sdlMessage, EnumLogOutput::CONSOLE);
		}
	}

	else logger->message(EnumLogLevel::ERROR, "Cannot draw rectangle, Renderer has not been initialized!", EnumLogOutput::TXT_FILE);
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
void RendererManager::drawSprite(const std::string &tag,
		const class Position &pos,
		const class Position &cameraOffset,
		const struct Dimension &spriteLocation,
		const double angle,
		const bool flipSprite){

	if(this->hasBeenInit) {

		Dimension spriteSize(this->getTextureTileWidth(tag), this->getTextureTileHeight(tag));
		//Select the right sprite from the sprite sheet
		SDL_Rect spriteRect = {spriteLocation.width * spriteSize.width,
				spriteLocation.height * spriteSize.height,
				spriteSize.width,
				spriteSize.height};

		//calculate the entity's/tile's size and location in the world
		double width = spriteSize.width * this->scale;
		double height = spriteSize.height * this->scale;
		double xPos = pos.xPos() - cameraOffset.xPos();
		double yPos = pos.yPosN() - cameraOffset.yPos();

		SDL_Rect entityRect = {static_cast<int>(xPos + 0.5),
				static_cast<int>(yPos + 0.5),
				static_cast<int>(width + 0.5),
				static_cast<int>(height + 0.5)};

		SDL_RendererFlip flip = flipSprite ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

		SDL_RenderCopyEx(this->renderer, this->getTexture(tag), &spriteRect, &entityRect, angle, NULL, flip);
	}

	else logger->message(EnumLogLevel::ERROR, "Cannot render sprite, Renderer has not been initialized!", EnumLogOutput::TXT_FILE);
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
void RendererManager::drawSprite(const std::string &tag,
		const Position &pos,
		const Position &cameraOffset,
		const Dimension &spriteLocation,
		const bool flipSprite){

	this->drawSprite(tag, pos, cameraOffset, spriteLocation, 0.0, flipSprite);
}



/*
 * @param	scaleIn The new scale for all rendering
 *
 * The new scale cannot be zero or negative, and if scaleIn is either it will default to 1.0
 */
void RendererManager::setScale(float scaleIn){
	scaleIn <= 0.0f ? this->scale = 1.0f : this->scale = scaleIn;
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
SDL_Texture* RendererManager::getTexture(const std::string &tag){

	if(!this->hasBeenInit) return nullptr;

	if(textureMap.find(tag) == textureMap.end()){

		logger->message(EnumLogLevel::WARNING,
				"Could not get the texture '" + tag + "'",
				EnumLogOutput::TXT_FILE);

		return nullptr;
	}

	else return textureMap[tag]->getTexture();
}



/*
 * @param	tag The ID of the texture
 *
 * @return	The tile width of the textures, or 0 if not found
 *
 * Gets the tile width of the texture specified by the tag. If it doesn't find the texture it will return 0
 */
int RendererManager::getTextureTileWidth(const std::string &tag){

	if(!this->hasBeenInit) return 0;

	if(textureMap.find(tag) == textureMap.end()){

		logger->message(EnumLogLevel::WARNING, "Could not get the texture '" + tag + "' width", EnumLogOutput::TXT_FILE);
		return 0;
	}

	else return textureMap[tag]->getTileSize().width;
}



/*
 * @param	tag The ID of the texture
 *
 * @return	The tile height of the textures, or 0 if not found
 *
 * Gets the tile height of the texture specified by the tag. If it doesn't find the texture it will return 0
 */
int RendererManager::getTextureTileHeight(const std::string &tag){

	if(!this->hasBeenInit) return 0;

	if(textureMap.find(tag) == textureMap.end()){

		logger->message(EnumLogLevel::WARNING, "Could not get the texture '" + tag + "' height", EnumLogOutput::TXT_FILE);
		return 0;
	}

	else return textureMap[tag]->getTileSize().height;
}



/*
 * @param	tag The ID of the texture
 *
 * @return	The dimensions of the texture
 *
 * Gets a copy of  tile dimensions of the texture specified by the tag
 * if it doesn't find the texture it will return a size of (0, 0)
 */
Dimension RendererManager::getTextureSize(const std::string &tag){
	return !this->hasBeenInit ? Dimension() : Dimension(this->getTextureTileWidth(tag), this->getTextureTileHeight(tag));
}








#ifndef RENDERERMANAGER_H_
#define RENDERERMANAGER_H_


#include <string>
#include <map>
#include <memory>

#include "RendererBlendMode.h"
#include "utilities/Loggers.hpp"



//TODO add SDL2 TTF support
class Renderer {

public:

	Renderer();



	~Renderer();



	Renderer(const Renderer &other) = delete;



	Renderer(Renderer &&other) = delete;



	/*
	 * @param	windowIn A pointer to the current window
	 *
	 * Initializes the Renderer Manager and must be called before using any other methods
	 */
	void init(struct SDL_Window *windowIn);



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
	bool registerTexture(const std::string &tag,
			const std::string &fileLocation,
			struct Dimension &dim);



	/*
	 * @param	tag The ID of the texture to be deregistered
	 *
	 * @return	True if tag was successfully deregistered
	 *
	 * Deregister the texture specified by the tag argument
	 */
	bool deregisterTexture(const std::string &tag);



	//Deregister all textures in the Renderer Manager
	void deregisterAllTextures();



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
	bool setDrawColor(uint8_t red,
			uint8_t green,
			uint8_t blue,
			uint8_t alpha);



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
	bool setTextureColor(const std::string &tag,
			uint8_t red,
			uint8_t green,
			uint8_t blue);



	/*
	 * @param	tag The ID of the texture
	 *
	 * @param	alpha The new opacity for the texture
	 *
	 * @return	True if the textures opacity was successfully changed
	 *
	 * Sets the given texture's opacity
	 */
	bool setTextureAlpha(const std::string &tag,
			uint8_t alpha);



	/*
	 * @param	tag The ID of the texture
	 *
	 * @param	blendMode The new blending mode
	 *
	 * @return	True if the textures blend mode was successfully changed
	 *
	 * Sets the given textures blend mode
	 */
	bool setTextureBlendMode(const std::string &tag,
			RendererBlendMode blendMode);



	/*
	 * @return	True if the renderer was cleared
	 *
	 * Clears the renderer and fill it in with the current draw color
	 */
	bool clear();



	/*
	 * @return	True if the renderer was presented
	 *
	 * Presents what has been drawn to the renderer on the screen
	 */
	bool present();



	/*
	 * @param	pos The coordinates of the Point
	 *
	 * Draws a point at the given coordinates to the renderer
	 */
	void drawPoint(const class Position &pos);



	/*
	 * @param	startPos The coordinates of the starting point of the Line
	 *
	 * @param	endPos The coordinates of the ending point of the Line
	 *
	 * Draws a line to the renderer
	 */
	void drawLine(const class Position &startPos,
			const class Position &endPos);



	/*
	 * @param	pos The coordinates of the rectangle
	 *
	 * @param	dim The dimensions of the rectangle
	 *
	 * @param	fill Flag to draw a filled in rectangle
	 *
	 * Draws a rectangle to the renderer
	 */
	void drawRect(const class Position &pos,
			const struct Dimension &dim,
			bool fill);



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
	void drawSprite(const std::string &tag,
			const class Position &pos,
			const class Position &cameraOffset,
			const struct Dimension &spriteLocation,
			const bool flipSprite);



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
	void drawSprite(const std::string &tag,
			const class Position &pos,
			const class Position &cameraOffset,
			const struct Dimension &spriteLocation,
			const double angle,
			const bool flipSprite);



	/*
	 * @param	scaleIn The new scale for all rendering
	 *
	 * The new scale cannot be zero or negative, and if scaleIn is either it will default to 1.0
	 */
	void setScale(float scaleIn);



protected:

	/*
	 * @nullable
	 *
	 * @param	tag The ID of the texture
	 *
	 * @return	Pointer to the texture, or null if the tag is not found
	 *
	 * Gets the texture specified by the tag. If it doesn't find the texture it will return a null pointer
	 */
	struct SDL_Texture* getTexture(const std::string &tag);



	/*
	 * @param	tag The ID of the texture
	 *
	 * @return	The tile width of the textures, or 0 if not found
	 *
	 * Gets the tile width of the texture specified by the tag. If it doesn't find the texture it will return 0
	 */
	int getTextureTileWidth(const std::string &tag);



	/*
	 * @param	tag The ID of the texture
	 *
	 * @return	The tile height of the textures, or 0 if not found
	 *
	 * Gets the tile height of the texture specified by the tag. If it doesn't find the texture it will return 0
	 */
	int getTextureTileHeight(const std::string &tag);



	/*
	 * @param	tag The ID of the texture
	 *
	 * @return	The dimensions of the texture
	 *
	 * Gets a copy of  tile dimensions of the texture specified by the tag
	 * if it doesn't find the texture it will return a size of (0, 0)
	 */
	struct Dimension getTextureSize(const std::string &tag);



private:

	bool m_hasBeenInit;

	float m_scale;

	struct SDL_Renderer *m_renderer;

	std::map<std::string, std::unique_ptr<class SDLTextureWrapper>> m_textureMap;

	std::shared_ptr<spdlog::logger> m_logger;
};


#endif /* RENDERERMANAGER_H_ */




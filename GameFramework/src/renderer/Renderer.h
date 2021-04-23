#ifndef RENDERER_H_
#define RENDERER_H_


#include <string>
#include <map>
#include <memory>

#include <glm/glm.hpp>

#include "renderer/shaders/ShaderLibrarian.h"
#include "RendererBlendMode.h"
#include "utilities/math/Pos2.hpp"
#include "utilities/math/Pos3.hpp"
#include "utilities/physics/TilePos.h"
#include "utilities/Loggers.hpp"

#include "renderer/buffers/VertexBuffer.h"
#include "renderer/buffers/IndexBuffer.h"



//TODO add TTF support
class Renderer 
{
public:

	Renderer();



	~Renderer();



	Renderer(const Renderer &other) = delete;



	Renderer(Renderer &&other) = delete;



	/// <summary>
	/// Initializes the Renderer and must be called before using any other methods
	/// </summary>
	/// <param name="windowIn">A pointer to the current window</param>
	void init(struct SDL_Window *windowIn);



	/// <summary>
	/// 
	/// </summary>
	void shutdown();



	/// <summary>
	/// Register a texture to the Rrenderer
	/// </summary>
	/// <param name="tag">The ID of the texture</param>
	/// <param name="fileLocation">The location of the texture file</param>
	/// <param name="dim">The dimensions of tiles in the texture</param>
	/// <returns>True if the texture was successfully registered</returns>
	bool registerTexture(const std::string &tag, const std::string &fileLocation, const Pos2N& dim);



	/// <summary>
	/// Deregister the texture specified by it's tag
	/// </summary>
	/// <param name="tag">The ID of the texture to be deregistered</param>
	/// <returns>True if the texture was successfully deregistered</returns>
	bool deregisterTexture(const std::string &tag);



	//Deregister all textures in the Renderer Manager

	/// <summary>
	/// Deregister all textures in the Renderer
	/// </summary>
	void deregisterAllTextures();



	/// <summary>
	/// Sets the drawing color
	/// </summary>
	/// <param name="red">The amount of red in the new color</param>
	/// <param name="green">The amount of green in the new color</param>
	/// <param name="blue">The amount of blue in the new color</param>
	/// <param name="alpha">The new opacity</param>
	/// <returns>True if the draw color was successfully changed</returns>
	bool setDrawColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);



	/// <summary>
	/// Sets the given texture's color
	/// </summary>
	/// <param name="tag">The ID of the texture</param>
	/// <param name="red">The amount of red in the new color</param>
	/// <param name="green">The amount of green in the new color</param>
	/// <param name="blue">The amount of blue in the new color</param>
	/// <returns>True if the textures color was successfully changed</returns>
	bool setTextureColor(const std::string &tag, uint8_t red, uint8_t green, uint8_t blue);



	/// <summary>
	/// Sets the given texture's opacity
	/// </summary>
	/// <param name="tag">The ID of the texture</param>
	/// <param name="alpha">alpha The new opacity for the texture</param>
	/// <returns>True if the textures opacity was successfully changed</returns>
	bool setTextureAlpha(const std::string &tag, uint8_t alpha);



	/// <summary>
	/// Sets the given textures blend mode
	/// </summary>
	/// <param name="tag">The ID of the texture</param>
	/// <param name="blendMode">The new blending mode</param>
	/// <returns>True if the textures blend mode was successfully changed</returns>
	bool setTextureBlendMode(const std::string &tag, RendererBlendMode blendMode);



	/// <summary>
	/// Presents what has been drawn by the Renderer to the screen
	/// </summary>
	/// <returns>True if the renderer was presented</returns>
	bool present();



	/// <summary>
	/// Draws a point at the given coordinates
	/// </summary>
	/// <param name="pos"></param>
	void drawPoint(const Pos2D& pos);



	/// <summary>
	/// Draws a line to the screen
	/// </summary>
	/// <param name="startPos">The coordinates of the starting point of the Line</param>
	/// <param name="endPos">The coordinates of the ending point of the Line</param>
	void drawLine(const Pos2D& startPos, const Pos2D& endPos);



	/// <summary>
	/// Draws a rectangle to the screen
	/// </summary>
	/// <param name="pos">The coordinates of the rectangle</param>
	/// <param name="dim">The dimensions of the rectangle</param>
	/// <param name="fill">Flag to draw a filled in rectangle</param>
	void drawRect(const Pos2D& pos, const Pos2N& dim, bool fill);



	/// <summary>
	/// Draws a sprite given by tag to the renderer
	/// </summary>
	/// <param name="tag">The tag ID of the entity/tile</param>
	/// <param name="pos">The coordinates of the entity/tile</param>
	/// <param name="cameraOffset">The coordinates of the camera</param>
	/// <param name="spriteLocation">The location of the sprite in the sprite sheet</param>
	/// <param name="flipSprite">If the sprite should be flipped</param>
	void drawSprite(const std::string& tag, const TilePos& pos, const TilePos& cameraOffset, const Pos2N& spriteLocation, const bool flipSprite);



	/// <summary>
	/// Draws a sprite given by tag to the screen
	/// </summary>
	/// <param name="tag">The tag ID of the entity/tile</param>
	/// <param name="pos">The coordinates of the entity/tile</param>
	/// <param name="cameraOffset">The coordinates of the camera</param>
	/// <param name="spriteLocation">The location of the sprite in the sprite sheet</param>
	/// <param name="angle">Specifies the rotation in degrees that will be applied to the sprite</param>
	/// <param name="flipSprite">If the sprite should be flipped</param>
	void drawSprite(const std::string& tag, const TilePos& pos, const TilePos& cameraOffset, const Pos2N& spriteLocation, const double angle, const bool flipSprite);



	/// <summary>
	/// 
	/// </summary>
	/// <param name="spriteIn"></param>
	/// <param name="pos"></param>
	/// <param name="cameraOffset"></param>
	void drawSprite(const class Sprite& spriteIn, const TilePos& pos, const TilePos& cameraOffset);



	/// <summary>
	/// The new scale cannot be zero or negative, and if scaleIn is either it will default to 1.0
	/// </summary>
	/// <param name="scaleIn">The new scale for all rendering</param>
	void setScale(float scaleIn);

	//**************************************************************************************************************************************************************************

	/// <summary>
	/// 
	/// </summary>
	/// <param name="cameraIn"></param>
	void begin(const std::shared_ptr<class Camera>& cameraIn);



	/// <summary>
	/// 
	/// </summary>
	void end();



	/// <summary>
	/// Clears the screen and fills it in with the given color
	/// </summary>
	/// <param name="red">Specifies the amount of red</param>
	/// <param name="green">Specifies the amount of green</param>
	/// <param name="blue">Specifies the amount of blue</param>
	/// <param name="alpha">Specifies the amount of alpha</param>
	void clear(float red, float green, float blue, float alpha);



	/// <summary>
	/// Clears the screen and fills it with black
	/// </summary>
	void clear();



	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="size"></param>
	/// <param name="material"></param>
	void drawQuad(const Pos3F& pos, const Pos2N& size, class IMaterial& material);



	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	ShaderLibrarian& shaderLibrarian();



protected:

	/// <summary>
	/// <para>nullable</para>
	/// Gets the texture specified by the tag. If it doesn't find the texture it will return a null pointer
	/// </summary>
	/// <param name="tag">The ID of the texture</param>
	struct SDL_Texture* getTexture(const std::string &tag);



	/// <summary>
	/// Gets the tile width of the texture specified by the tag
	/// </summary>
	/// <param name="tag">The ID of the texture</param>
	/// <returns>The tile width of the textures, or 0 if not found</returns>
	int getTextureTileWidth(const std::string &tag);



	/// <summary>
	/// Gets the tile height of the texture specified by the tag
	/// </summary>
	/// <param name="tag">The ID of the texture</param>
	/// <returns>The tile height of the textures, or 0 if not found</returns>
	int getTextureTileHeight(const std::string &tag);



	/// <summary>
	/// Gets a copy of tile dimensions of the texture specified by the tag. If it doesn't find the texture it will return a size of (0, 0)
	/// </summary>
	/// <param name="tag">The ID of the texture</param>
	/// <returns>The dimensions of the texture, or (0, 0) if not found</returns>
	Pos2N getTextureSize(const std::string &tag);



private:

	std::shared_ptr<spdlog::logger> m_logger;

	ShaderLibrarian m_shaders;

	std::shared_ptr<class Camera> m_camera;

	bool m_hasBeenInit;

	float m_scale;

	struct SDL_Renderer *m_renderer;

	std::map<std::string, std::unique_ptr<class TextureSDL>> m_textureMap;

	VertexBuffer m_vbo;

	IndexBuffer m_ibo;
};


#endif /* RENDERER_H_ */




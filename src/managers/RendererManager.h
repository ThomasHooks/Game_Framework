//============================================================================
// Name       		: RendererManager.h
// Author     		: Thomas Hooks
// Last Modified	: 03/06/2020
//============================================================================




#ifndef RENDERERMANAGER_H_
#define RENDERERMANAGER_H_




#include <string>
#include <map>
#include <memory>

#include "../utilities/EnumBlendMode.h"



//TODO add SDL2 TTF support
class RendererManager {

public:

	RendererManager(class GameLogger *logger_ptr);

	~RendererManager();

	RendererManager(const RendererManager &other) = delete;

	RendererManager(RendererManager &&other) = delete;

	void init(struct SDL_Window *windowIn);

	bool registerTexture(const std::string &tag,
			const std::string &fileLocation,
			struct Dimension &dim);

	bool deregisterTexture(const std::string &tag);
	void deregisterAllTextures();

	bool setDrawColor(uint32_t red,
			uint32_t green,
			uint32_t blue,
			uint32_t alpha);

	bool setTextureColor(const std::string &tag,
			uint32_t red,
			uint32_t green,
			uint32_t blue);

	bool setTextureAlpha(const std::string &tag,
			uint32_t alpha);

	bool setTextureBlendMode(const std::string &tag,
			EnumBlendMode blendMode);

	bool clear();

	bool present();

	void drawPoint(const class Position &pos);

	void drawLine(const class Position &startPos,
			const class Position &endPos);

	void drawRect(const class Position &pos,
			const struct Dimension &dim,
			bool fill);

	void drawSprite(const std::string &tag,
			const class Position &pos,
			const class Position &cameraOffset,
			const struct Dimension &spriteLocation,
			const bool flipSprite);

	void setScale(float scaleIn);

protected:

	struct SDL_Texture* getTexture(const std::string &tag);

	int getTextureTileWidth(const std::string &tag);
	int getTextureTileHeight(const std::string &tag);

private:

	bool hasBeenInit;

	float scale;

	class GameLogger *logger;

	struct SDL_Renderer *renderer;

	std::map<std::string, std::unique_ptr<class SDLTextureWrapper>> textureMap;
};


#endif /* RENDERERMANAGER_H_ */




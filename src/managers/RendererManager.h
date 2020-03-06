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



//TODO add SDL2 TTF support
class RendererManager {

public:
	RendererManager(class GameLogger *logger_ptr);

	~RendererManager();

	RendererManager(const RendererManager &other) = delete;

	RendererManager(RendererManager &&other) = delete;

	void init(struct SDL_Window *windowIn);

	bool registerTexture(const std::string &tag,
			const std::string &fileLocation);

	bool deregisterTexture(const std::string &tag);
	bool deregisterAllTextures();

	bool setDrawColor(uint32_t red,
			uint32_t green,
			uint32_t blue,
			uint32_t alpha);

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
			const struct Dimension &spriteSize,
			const struct Dimension &spriteLocation,
			const bool flipSprite);

	void setScale(float scaleIn);

protected:

	struct SDL_Texture* getTexture(const std::string &tag) const;
	//const struct Dimension& getTextureSize(const std::string &tag) const;

private:

	bool hasBeenInit;

	float scale;

	class GameLogger *logger;

	struct SDL_Renderer *renderer;

	std::map<std::string, std::unique_ptr<class SDLTextureWrapper>> textureMap;
};


#endif /* RENDERERMANAGER_H_ */




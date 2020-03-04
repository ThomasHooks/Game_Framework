//============================================================================
// Name       		: RendererManager.h
// Author     		: Thomas Hooks
// Last Modified	: 03/04/2020
//============================================================================




#ifndef RENDERERMANAGER_H_
#define RENDERERMANAGER_H_




#include <string>




class RendererManager {

public:
	RendererManager(class GameLogger *logger_ptr,
			class AssetManager *assest_ptr,
			struct SDL_Renderer *renderer);

	~RendererManager();

	RendererManager(const RendererManager &other) = delete;

	RendererManager(RendererManager &&other) = delete;

	void drawSprite(const std::string &tag,
			const class Position &pos,
			const class Position &cameraOffset,
			const class Dimension &spriteSize,
			const class Dimension &spriteLocation,
			const bool flipSprite) const;

	void setScale(float scaleIn);

private:

	float scale;

	class GameLogger *logger;

	class AssetManager *assests;

	struct SDL_Renderer *renderer;
};


#endif /* RENDERERMANAGER_H_ */




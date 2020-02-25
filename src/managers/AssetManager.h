//============================================================================
// Name       		: AssetManager.h
// Author     		: Thomas Hooks
// Last Modified	: 11/2/2019
//============================================================================




#ifndef SRC_ASSET_MANAGER_H_
#define SRC_ASSET_MANAGER_H_


#include <map>
#include <string>


//TODO add SDL music assets
//TODO add SDL sound assets
//TODO add SDL ttf assets


class AssetManager {

public:

	AssetManager();

	~AssetManager();

	AssetManager(const AssetManager &other) = delete;

	AssetManager(AssetManager &&other) = delete;


	void init(class GameLogger *log_ptr, struct SDL_Renderer *renderer_ptr);

	bool add_texture(std::string key, std::string fileDirectory);

	struct SDL_Texture* get_texture(std::string key);

	bool remove_texture(std::string key);

	void remove_allTextures(void);


private:

	std::map<std::string, struct SDL_Texture*> textureMap;

	bool b_hasBeenInit;

	class GameLogger *log;

	struct SDL_Renderer *renderer;
};


#endif /* SRC_ASSET_MANAGER_H_ */








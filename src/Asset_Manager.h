//============================================================================
// Name       		: Asset_Manager.h
// Author     		: Thomas Hooks
// Version    		: 1
// Last Modified	: 11/2/2019
// Description		:
//============================================================================




#ifndef SRC_ASSET_MANAGER_H_
#define SRC_ASSET_MANAGER_H_


#include <map>
#include <string>


//TODO add SDL music assets
//TODO add SDL sound assets
//TODO add SDL ttf assets


class Asset_Manager {

public:

	Asset_Manager();

	~Asset_Manager();

	Asset_Manager(const Asset_Manager &other) = delete;

	Asset_Manager(Asset_Manager &&other) = delete;


	void init(class Game_Logger *log_ptr, struct SDL_Renderer *renderer_ptr);

	bool add_texture(std::string key, std::string fileDirectory);

	struct SDL_Texture* get_texture(std::string key);

	bool remove_texture(std::string key);

	void remove_allTextures(void);


private:

	std::map<std::string, struct SDL_Texture*> textureMap;

	bool b_hasBeenInit;

	class Game_Logger *log;

	struct SDL_Renderer *renderer;
};


#endif /* SRC_ASSET_MANAGER_H_ */








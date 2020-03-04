//============================================================================
// Name       		: AssetManager.cpp
// Author     		: Thomas Hooks
// Last Modified	: 11/2/2019
//============================================================================




#include "AssetManager.h"

#include <SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include "../Game.h"




AssetManager::AssetManager()
	: b_hasBeenInit(false), log(nullptr), renderer(nullptr){

	return;
}



AssetManager::~AssetManager() {
	//Destructor
}


//----------------------------------------------------------------------------


void AssetManager::init(class GameLogger *log_ptr, struct SDL_Renderer *renderer_ptr){
	/*
	 * brief		This method initializes the asset manager
	 *
	 * param		log_ptr			pointer to the logger
	 *
	 * param		renderer_ptr	pointer to the renderer
	 *
	 * This method will initialize the asset manger only once and must be
	 * called before any assets can be added or removed
	 */




	if(!b_hasBeenInit){
		//Only initialize once

		log = log_ptr;

		renderer = renderer_ptr;

		b_hasBeenInit = true;
	}

	return;
}


//----------------------------------------------------------------------------


bool AssetManager::add_texture(std::string key, std::string fileDirectory){
	/*
	 * brief		This method will add a texture with the given key
	 *
	 * param		key					the name of the texture
	 *
	 * param		fileDirectory		path to the sprite file
	 *
	 * retrn		true if successful, false otherwise
	 *
	 * This method will add a texture with the key argument as its index.
	 * If it is unable to add the texture it will return false and log the
	 * failure, otherwise it will return true and make a log
	 */




	if(!b_hasBeenInit) return false;


	//Check if the key already exist
	if(textureMap.find(key) == textureMap.end()){
		//Could not find the key, so add the texture

		//Temporary pointer used to load the sprite
		SDL_Surface *tmp;
		tmp = IMG_Load(fileDirectory.c_str());

		//IMG_Load will return null if it is unable to load the image file
		if(tmp == NULL){
			//Error handle

			//TODO Add a default sprite for that key

			//Free the temporary pointer
			SDL_FreeSurface(tmp);
			tmp = nullptr;

			//Log warning message
			std::string sdlMessage = IMG_GetError();

			log->message(Level::WARNING, "Cannot find the file: '"
					+ fileDirectory + "'. SDL: " + sdlMessage, Output::CONSOLE);

			return false;
		}


		else{
			//SDL successfully made a surface
			//Create a texture and insert it into the map with its key
			textureMap.insert({key, SDL_CreateTextureFromSurface(renderer, tmp)});

			//Free the temporary pointer
			SDL_FreeSurface(tmp);
			tmp = nullptr;

			//Log that the texture was successfully loaded
			log->message(Level::INFO, "File '" + fileDirectory
					+ "' has been loaded", Output::TXT_FILE);

			return true;
		}
	}


	else{
		//Was able to find the key, so warn the user

		log->message(Level::WARNING, "Unable to add texture, key: '"
				+ key +"' is not unique", Output::TXT_FILE);

		return false;
	}
}


//----------------------------------------------------------------------------


struct SDL_Texture* AssetManager::get_texture(std::string key){
	/*
	 * brief		This method will return a texture for the given key
	 *
	 * param		key		the name of the texture
	 *
	 * retrn		Pointer to the texture, or null if the key is invalid
	 *
	 * This method will return a pointer to the texture specified by the key.
	 * It will check if the key exist, if it doesn't it will return a null
	 * pointer and log that the key could not be found.
	 */




	if(!b_hasBeenInit) return nullptr;

	if(textureMap.find(key) == textureMap.end()){
		//Could not find the key, so log and return a null pointer

		log->message(Level::WARNING, "Could not find key: " + key,
				Output::TXT_FILE);

		return nullptr;
	}


	else{
		//Was able to find the key so return a pointer to the texture

		return textureMap[key];
	}
}


//----------------------------------------------------------------------------


bool AssetManager::remove_texture(std::string key){
	/*
	 * brief		This method will remove a texture for the given key
	 *
	 * param		key		the name of the texture
	 *
	 * retrn		true if successful, false otherwise
	 *
	 * This method will remove a texture specified by the key argument.  If it
	 * is unable to remove the texture it will return false and log the failure,
	 * otherwise it will return true and make a log
	 */




	if(!b_hasBeenInit) return false;

	if(textureMap.find(key) == textureMap.end()){
		//Could not find the key

		log->message(Level::WARNING, "Could not find key: '" + key +
				"' unable to remove", Output::TXT_FILE);

		return false;
	}


	else{
		//Was able to find the key

		log->message(Level::INFO, "Freeing texture '" + key +"'", Output::TXT_FILE);

		SDL_DestroyTexture(textureMap[key]);
		textureMap[key] = nullptr;
		textureMap.erase(key);

		log->message(Level::INFO, "Texture '" + key +"' has been freed", Output::TXT_FILE);

		return true;
	}
}


//----------------------------------------------------------------------------


void AssetManager::remove_allTextures(void){
	/*
	 * brief		This method will free all textures in the asset manager
	 * 				and should be called at the end of the application
	 *
	 * note			This method will only free textures once but should only
	 * 				be called at the end of the application
	 *
	 * This method will iterates over all textures stored in the asset manager
	 * and first frees the texture and then removes the element from the map.
	 */




	if(!b_hasBeenInit) return;

	log->message(Level::INFO, "Freeing all textures", Output::TXT_FILE);

	//iterate over the texture map and free all SDL textures
	std::map<std::string, struct SDL_Texture*>::iterator itr = textureMap.begin();
	while(itr != textureMap.end()){

		//the first element in the iterator is the key
		std::string key = itr->first;

		log->message(Level::INFO, "Freeing texture '" + key
				+ "'", Output::TXT_FILE);

		//Free the texture, and remove it from the map
		SDL_DestroyTexture(textureMap[key]);
		textureMap[key] = nullptr;
		//If key was used instead it would return the number of elements erased
		 itr = textureMap.erase(itr);

		 log->message(Level::INFO, "Texture '" + key
				+ "' has been freed", Output::TXT_FILE);
	}

	return;
}








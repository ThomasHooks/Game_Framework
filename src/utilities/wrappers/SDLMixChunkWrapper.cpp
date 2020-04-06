//============================================================================
// Name       		: SDLMixChunkWrapper.cpp
// Author     		: Thomas Hooks
// Last Modified	: Apr 4, 2020
//============================================================================




#include <SDL_mixer.h>

#include "SDLMixChunkWrapper.h"




/*
 * Wrapper used to encapsulate SDL Mix Chunks
 * this can store WAVE, AIFF, RIFF, OGG, and VOC audio files
 */
SDLMixChunkWrapper::SDLMixChunkWrapper(const std::string &location)
	: sfx(nullptr) {

	this->sfx = Mix_LoadWAV(location.c_str());
}



SDLMixChunkWrapper::~SDLMixChunkWrapper() {

	Mix_FreeChunk(this->sfx);
	this->sfx = nullptr;
}



/*
 * @nullable
 *
 * @return	Pointer to the SDL Mixer Chunk that is stored in this wrapper or null
 */
struct Mix_Chunk* SDLMixChunkWrapper::get(){
	return this->sfx;
}








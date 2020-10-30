//============================================================================
// Name       		: SDLMixChunkWrapper.h
// Author     		: Thomas Hooks
// Last Modified	: Apr 4, 2020
//============================================================================




#ifndef UTILITIES_WRAPPERS_SDLMIXCHUNKWRAPPER_H_
#define UTILITIES_WRAPPERS_SDLMIXCHUNKWRAPPER_H_


#include <string>


/*
 * Wrapper used to encapsulate SDL Mix Chunks
 * this can store WAVE, AIFF, RIFF, OGG, and VOC audio files
 */
class SDLMixChunkWrapper {

public:

	SDLMixChunkWrapper(const std::string &location);



	~SDLMixChunkWrapper();



	/*
	 * @nullable
	 *
	 * @return	The SDL sound that is stored in this wrapper
	 */
	struct Mix_Chunk* get();



private:

	struct Mix_Chunk *sfx;
};


#endif /* UTILITIES_WRAPPERS_SDLMIXCHUNKWRAPPER_H_ */




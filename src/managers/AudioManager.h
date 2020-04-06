//============================================================================
// Name       		: AudioManager.h
// Author     		: Thomas Hooks
// Last Modified	: Apr 5, 2020
//============================================================================




#ifndef MANAGERS_AUDIOMANAGER_H_
#define MANAGERS_AUDIOMANAGER_H_


#include <string>
#include <map>
#include <unordered_map>
#include <memory>


//TODO add SDL music
class AudioManager {

public:

	AudioManager(class GameLogger *loggerPtr);



	~AudioManager();



	/*
	 * @param	frequency
	 *
	 * @param	format
	 *
	 * @param	channels
	 *
	 * Initializes this Audio Manager
	 */
	bool init();



	/*
	 * @param	tag The ID of the sound
	 *
	 * @param	location The location of the sound file
	 * 					 supports WAVE, AIFF, RIFF, OGG, and VOC audio files
	 *
	 * @return	True if the sound was successfully registered
	 *
	 * Register a sound to the Audio Manager
	 */
	bool registerSFX(const std::string &tag, const std::string &location);



	/*
	 * @param	tag The ID of the texture to be deregistered
	 *
	 * @return	True if tag was successfully deregistered
	 *
	 * Deregister the sound specified by its tag
	 */
	bool deregisterSFX(const std::string &tag);



	//Deregister all sounds in the Audio Manager
	void deregisterAllSFX();



	/*
	 * @param	tag The ID of the sound
	 *
	 * @param	channel	The channel that the sound is to be played on
	 * 					If -1 is passed it will pick the first open channel
	 *
	 * @param	loops The number of times the sound is to be played
	 * 				  If 0 is passed it will play once
	 * 				  If -1 is passed it will loop infinitely
	 *
	 * @return The channel the sound is being played on
	 *
	 * Plays a sound given by its tag
	 */
	int playSFX(const std::string &tag, int channel, int loops);



	/*
	 * @param	tag The ID of the sound
	 *
	 * @param	loops The number of times the sound is to be played
	 * 				  If 0 is passed it will play once
	 * 				  If -1 is passed it will loop infinitely
	 *
	 * @return The channel the sound is being played on
	 *
	 * Plays a sound given by its tag
	 */
	int playSFX(const std::string &tag, int loops);



	/*
	 * @param	tag The ID of the sound
	 *
	 * @return The channel the sound is being played on
	 *
	 * Plays a sound given by its tag once
	 */
	int playSFX(const std::string &tag);



	/*
	 * @param	tag The ID of the sound
	 *
	 * @param	channel	The channel that the sound is to be played on
	 * 					If -1 is passed it will pick the first open channel
	 *
	 * @param	ticks The amount of time the sound is played in millisecond
	 *
	 * @return The channel the sound is being played on
	 *
	 * Plays a sound given by its tag for a certain amount of time
	 */
	int playSFX(const std::string &tag, int channel, unsigned int ticks);



	/*
	 * @param	tag The ID of the sound
	 *
	 * @param	ticks The amount of time the sound is played in millisecond
	 *
	 * @return The channel the sound is being played on
	 *
	 * Plays a sound given by its tag for a certain amount of time
	 */
	int playSFX(const std::string &tag, unsigned int ticks);



protected:

	/*
	 * @nullable
	 *
	 * @return	Pointer to the sound wrapper or null if the tag cannot be found
	 */
	class SDLMixChunkWrapper* getSound(const std::string &tag);



private:

	class GameLogger *logger;

	bool hasBeenInit;

	std::unordered_map<std::string, std::unique_ptr<class SDLMixChunkWrapper>> sounds;
};


#endif /* MANAGERS_AUDIOMANAGER_H_ */




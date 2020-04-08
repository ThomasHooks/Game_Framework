//============================================================================
// Name       		: AudioManager.h
// Author     		: Thomas Hooks
// Last Modified	: Apr 7, 2020
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
	 * @param	frequency Output sampling frequency in samples per second
	 *
	 * @param	format Output sample format
	 *
	 * @param	channels Number of hardware channels
	 * 					 2 for stereo and 1 for mono
	 *
	 * Initializes this Audio Manager
	 */
	bool init();



	/*
	 * @param	tag The ID of the audio sample
	 *
	 * @param	location The location of the sample file
	 * 					 supports WAVE, AIFF, RIFF, OGG, and VOC audio files
	 *
	 * @return	True if the audio sample was successfully registered
	 *
	 * Register an audio sample to the Audio Manager
	 */
	bool registerSample(const std::string &tag, const std::string &location);



	/*
	 * @param	tag The ID of the audio sample to be deregistered
	 *
	 * @return	True if tag was successfully deregistered
	 *
	 * Deregister the audio sample specified by its tag
	 */
	bool deregisterSample(const std::string &tag);



	//Deregister all audio samples in the Audio Manager
	void deregisterAllSamples();



	/*
	 * @param	tag The ID of the audio sample
	 *
	 * @param	channel	The channel that the audio sample is to be played on
	 * 					If -1 is passed it will pick the first open channel
	 *
	 * @param	loops The number of times the audio sample is to be played
	 * 				  If 0 is passed it will play once
	 * 				  If -1 is passed it will loop infinitely
	 *
	 * @return The channel the audio sample is being played on
	 *
	 * Plays an audio sample given by its tag
	 */
	int playSample(const std::string &tag, int channel, int loops);



	/*
	 * @param	tag The ID of the audio sample
	 *
	 * @param	loops The number of times the audio sample is to be played
	 * 				  If 0 is passed it will play once
	 * 				  If -1 is passed it will loop infinitely
	 *
	 * @return The channel the audio sample is being played on
	 *
	 * Plays an audio sample given by its tag
	 */
	int playSample(const std::string &tag, int loops);



	/*
	 * @param	tag The ID of the audio sample
	 *
	 * @return The channel the audio sample is being played on
	 *
	 * Plays an audio sample given by its tag once
	 */
	int playSample(const std::string &tag);



	/*
	 * @param	tag The ID of the audio sample
	 *
	 * @param	channel	The channel that the audio sample is to be played on
	 * 					If -1 is passed it will pick the first open channel
	 *
	 * @param	ticks The amount of time the audio sample is played in millisecond
	 *
	 * @return The channel the audio sample is being played on
	 *
	 * Plays an audio sample given by its tag for a certain amount of time
	 */
	int playSampleTimed(const std::string &tag, int channel, unsigned int ticks);



	/*
	 * @param	tag The ID of the audio sample
	 *
	 * @param	ticks The amount of time the sample is played in millisecond
	 *
	 * @return The channel the audio sample is being played on
	 *
	 * Plays an audio sample given by its tag for a certain amount of time
	 */
	int playSampleTimed(const std::string &tag, unsigned int ticks);



	/*
	 * @param	tag The ID of the audio sample
	 *
	 * @param	volume The volume of the audio sample ranging from 0 to 128
	 *
	 * Sets the volume that the given audio sample will be played at
	 */
	void setSampleVolume(const std::string &tag, int volumeIn);



	/*
	 * @param	channel The ID of the channel
	 *
	 * @param	volume The volume of the channel ranging from 0 to 128
	 *
	 * Sets the volume that the given channel will be played at
	 */
	void setChannelVolume(int channel, int volumeIn);



	/*
	 * @param	channel The ID of the channel
	 *
	 * Gets the volume of the given channel
	 */
	int getChannelVolume(int channel) const;



	/*
	 * @param	channel The ID of the channel
	 *
	 * Stops the given channel
	 */
	void stopChannel(int channel);



	/*
	 * @param	channel The ID of the channel
	 *
	 * @param	ticks The amount of time in milliseconds
	 * 				  until the channel is stopped
	 *
	 * Stops the given channel
	 */
	void stopChannel(int channel, int ticks);



	/*
	 * @param	channel The ID of the channel
	 *
	 * Pauses the given channel
	 * only channels that are currently playing can be paused
	 */
	void pauseChannel(int channel);



	/*
	 * @param	channel The ID of the channel
	 *
	 * Unpause the given channel
	 * only channels that are currently paused can be unpaused
	 */
	void unpauseChannel(int channel);



	/*
	 * @param	channel The ID of the channel
	 *
	 * Checks if the given channel is playing
	 */
	bool isChannelPlaying(int channel) const;



	/*
	 * @param	channel The ID of the channel
	 *
	 * Checks if the given channel is paused
	 */
	bool isChannelPaused(int channel) const;



protected:

	/*
	 * @nullable
	 *
	 * @return	Pointer to the audio sample wrapper or null if the tag cannot be found
	 */
	class SDLMixChunkWrapper* getSample(const std::string &tag);



private:

	const int NUMBEROFCHANNELS = 16;

	class GameLogger *logger;

	bool hasBeenInit;

	std::unordered_map<std::string, std::unique_ptr<class SDLMixChunkWrapper>> samples;
};


#endif /* MANAGERS_AUDIOMANAGER_H_ */




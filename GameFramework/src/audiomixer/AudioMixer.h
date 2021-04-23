#ifndef AUDIOMIXER_H_
#define AUDIOMIXER_H_


#include <string>
#include <map>
#include <unordered_map>
#include <memory>

#include "utilities/Loggers.hpp"



//TODO add SDL music
class AudioMixer 
{
public:

	AudioMixer();



	~AudioMixer();



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
	bool registerSample(const std::string& tag, const std::string& location);



	/*
	 * @param	tag The ID of the audio sample to be deregistered
	 *
	 * @return	True if tag was successfully deregistered
	 *
	 * Deregister the audio sample specified by its tag
	 */
	bool deregisterSample(const std::string& tag);



	//Deregister all audio samples in the Audio Manager
	void deregisterAllSamples();



	/*
	 * @param	tag The ID of the audio sample
	 *
	 * @return	The channel the audio sample is being played on or -1 on error
	 *
	 * Plays an audio sample given by its tag once
	 */
	int playSample(const std::string& tag);



	/*
	 * @param	tag The ID of the audio sample
	 *
	 * @param	loops The number of times the audio sample is to be played
	 * 				  If 0 is passed it will play once
	 * 				  If -1 is passed it will loop infinitely
	 *
	 * @return	The channel the audio sample is being played on or -1 on error
	 *
	 * Plays an audio sample given by its tag
	 */
	int playSample(const std::string& tag, int loops);



	/*
	 * @param	tag The ID of the audio sample
	 *
	 * @param	loops The number of times the audio sample is to be played
	 * 				  If 0 is passed it will play once
	 * 				  If -1 is passed it will loop infinitely
	 *
	 * @param	volume The volume the audio sample will be played at ranging from 0.0 to 1.0
	 *
	 * @return	The channel the audio sample is being played on or -1 on error
	 *
	 * Plays an audio sample given by its tag
	 */
	int playSample(const std::string& tag, int loops, float volume);



	/*
	 * @param	tag The ID of the audio sample
	 *
	 * @param	ticks The amount of time the sample is played in millisecond
	 *
	 * @return	The channel the audio sample is being played on or -1 on error
	 *
	 * Plays an audio sample given by its tag for a certain amount of time
	 */
	int playSample(const std::string& tag, uint32_t ticks);



	/*
	 * @param	tag The ID of the audio sample
	 *
	 * @param	ticks The amount of time the sample is played in millisecond
	 *
	 * @param	volume The volume the audio sample will be played at ranging from 0.0 to 1.0
	 *
	 * @return	The channel the audio sample is being played on or -1 on error
	 *
	 * Plays an audio sample given by its tag for a certain amount of time
	 */
	int playSample(const std::string& tag, uint32_t ticks, float volume);



	/*
	 * @param	tag The ID of the audio sample
	 *
	 * @param	volume The volume the audio sample will be played at ranging from 0.0 to 1.0
	 *
	 * @return	The channel the audio sample is being played on or -1 on error
	 *
	 * Plays an audio sample given by its tag once at the given volume
	 */
	int playSample(const std::string& tag, float volume);



	/*
	 * @param	camera Reference to the Game's Camera
	 *
	 * @param	origin Coordinates where the sample is being played from
	 *
	 * @param	tag The ID of the audio sample
	 *
	 * @param	volume The volume of the audio sample ranging from 0.0 to 1.0
	 *
	 * @return	The channel the audio sample is being played on or -1 on error
	 *
	 * Plays an audio sample given by its tag once at the given position and volume
	 */
	int playSample(const class Camera& camera, const class TilePos& origin, const std::string& tag, float volume);



	/*
	 * @param	tag The ID of the audio sample
	 *
	 * @param	volume The volume of the audio sample ranging from 0 to 128
	 *
	 * Sets the volume that the given audio sample will be played at
	 */
	void setSampleVolume(const std::string& tag, float volume);



	/*
	 * @param	channel The ID of the channel, passing -1 will set all channels
	 *
	 * @param	volume The volume of the channel ranging from 0.0 to 1.0
	 *
	 * Sets the volume that the given channel will be played at
	 */
	void setChannelVolume(int channel, float volume);



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
	 * @param	tag The ID of the audio sample
	 *
	 * @param	channel	The channel that the audio sample is to be played on
	 * 					If -1 is passed it will pick the first open channel
	 *
	 * @param	loops The number of times the audio sample is to be played
	 * 				  If 0 is passed it will play once
	 * 				  If -1 is passed it will loop infinitely
	 *
	 * @param	ticks The amount of time the sample is played in millisecond
	 *
	 * @return The channel the audio sample is being played on or -1 on error
	 *
	 * Plays an audio sample given by its tag until it has played for either the given number of loops or ticks
	 */
	int playSample(const std::string& tag, int channel, int loops, uint32_t ticks);



	/*
	 * @nullable
	 *
	 * @return	Pointer to the audio sample wrapper or null if the tag cannot be found
	 */
	class SampleChunk* getSample(const std::string& tag);



private:

	const int NUMBEROFCHANNELS = 16;

	bool m_hasBeenInit;

	std::unordered_map<std::string, std::unique_ptr<class SampleChunk>> m_samples;

	std::shared_ptr<spdlog::logger> m_logger;
};


#endif




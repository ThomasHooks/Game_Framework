#include <cmath>

#include "SDL_mixer.h"

#include "AudioMixer.h"
#include "utilities/GameCamera.h"
#include "../utilities/Logger.h"
#include "../utilities/physics/Position.h"
#include "../utilities/wrappers/SDLMixChunkWrapper.h"




AudioMixer::AudioMixer(Logger *loggerPtr)
	: logger(loggerPtr),
	  hasBeenInit(false) {

	logger->message(Logger::Level::INFO, "Starting Audio Manager", Logger::Output::TXT_FILE);
}



AudioMixer::~AudioMixer() {

	logger->message(Logger::Level::INFO, "Stopping Audio Manager", Logger::Output::TXT_FILE);
	deregisterAllSamples();

	logger->message(Logger::Level::INFO, "Unloading dynamic mixer libraries", Logger::Output::TXT_FILE);
	while(Mix_Init(0)) {
		Mix_Quit();
	}

	logger->message(Logger::Level::INFO, "Quitting SDL Mixer", Logger::Output::TXT_FILE);
	Mix_CloseAudio();
	logger->message(Logger::Level::INFO, "Audio Manager stopped", Logger::Output::TXT_FILE);
}



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
bool AudioMixer::init() {

	if(!this->hasBeenInit) {
		logger->message(Logger::Level::INFO, "Initializing Audio Manager", Logger::Output::TXT_FILE);

		int formats = MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG;
		int mixerFlag = Mix_Init(formats);
		if((mixerFlag & formats) != formats) {
			std::string mixerErrorCode = Mix_GetError();
			logger->message(Logger::Level::ERROR, "SDL Mixer failed to initialize! Error Code: " + mixerErrorCode, Logger::Output::TXT_FILE);
			return false;
		}

		Mix_AllocateChannels(NUMBEROFCHANNELS);

		mixerFlag = Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);
		if(mixerFlag == -1) {
			std::string mixerErrorCode = Mix_GetError();
			logger->message(Logger::Level::ERROR, "SDL Mixer failed to initialize! Error Code: " + mixerErrorCode, Logger::Output::TXT_FILE);
			return false;
		}

		this->hasBeenInit = true;
		logger->message(Logger::Level::INFO, "Audio Manager has been initialized", Logger::Output::TXT_FILE);
	}
	return true;
}



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
bool AudioMixer::registerSample(const std::string &tag, const std::string &location) {

	if(!this->hasBeenInit) {
		logger->message(Logger::Level::ERROR, "Mixer has not been initialized cannot register samples!", Logger::Output::TXT_FILE);
		return false;
	}

	logger->message(Logger::Level::INFO, "Registering sample '" + tag + "' at '" + location + "'", Logger::Output::TXT_FILE);
	auto itr = this->samples.insert({tag, std::make_unique<SDLMixChunkWrapper>(location)});
	if(!itr.second) {
		//Tag isn't unique
		logger->message(Logger::Level::ERROR, "The sample was not registered tag: '" + tag + "' is not unique!", Logger::Output::TXT_FILE);
		return itr.second;
	}
	if(itr.first->second->get() == nullptr) {
		//Failed to load the audio file
		std::string mixerErrorCode = Mix_GetError();
		logger->message(Logger::Level::ERROR, "Could not load sample '" + tag + "' at '" + location + "' Error Code: " + mixerErrorCode, Logger::Output::TXT_FILE);
		this->samples.erase(tag);
		return false;
	}

	logger->message(Logger::Level::INFO, "Sample '" + tag + "' has been registered", Logger::Output::TXT_FILE);
	return itr.second;
}



/*
 * @param	tag The ID of the audio sample to be deregistered
 *
 * @return	True if tag was successfully deregistered
 *
 * Deregister the audio sample specified by its tag
 */
bool AudioMixer::deregisterSample(const std::string &tag) {

	if(!this->hasBeenInit) {
		logger->message(Logger::Level::ERROR, "Mixer has not been initialized cannot deregister samples!", Logger::Output::TXT_FILE);
		return false;
	}

	logger->message(Logger::Level::INFO, "Deregistering sample '" + tag + "'", Logger::Output::TXT_FILE);
	this->samples.erase(tag);
	logger->message(Logger::Level::INFO, "Sample '" + tag +"' has been deregistered", Logger::Output::TXT_FILE);
	return true;
}



//Deregister all audio samples in the Audio Manager
void AudioMixer::deregisterAllSamples() {

	if(!this->hasBeenInit) {
		logger->message(Logger::Level::ERROR, "Mixer has not been initialized cannot deregister sample!", Logger::Output::TXT_FILE);
		return;
	}

	logger->message(Logger::Level::INFO, "Deregistering all samples", Logger::Output::TXT_FILE);
	auto itr = this->samples.begin();
	while(itr != this->samples.end()) {
		std::string tag = itr->first;
		logger->message(Logger::Level::INFO, "Deregistering sample '" + tag + "'", Logger::Output::TXT_FILE);
		itr = this->samples.erase(itr);
		logger->message(Logger::Level::INFO, "Sample '" + tag + "' has been deregistered", Logger::Output::TXT_FILE);
	}
}



/*
 * @param	tag The ID of the audio sample
 *
 * @return	The channel the audio sample is being played on or -1 on error
 *
 * Plays an audio sample given by its tag once
 */
int AudioMixer::playSample(const std::string &tag) {
	return playSample(tag, -1, 0, -1);
}



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
int AudioMixer::playSample(const std::string &tag, int loops) {
	return playSample(tag, -1, loops, -1);
}



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
int AudioMixer::playSample(const std::string &tag, int loops, float volume) {

	int channel = playSample(tag, -1, loops, -1);
	if(channel != -1) setChannelVolume(channel, volume);
	return channel;
}



/*
 * @param	tag The ID of the audio sample
 *
 * @param	ticks The amount of time the sample is played in millisecond
 *
 * @return	The channel the audio sample is being played on or -1 on error
 *
 * Plays an audio sample given by its tag for a certain amount of time
 */
int AudioMixer::playSample(const std::string &tag, uint32_t ticks) {
	return playSample(tag, -1, -1, ticks);
}



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
int AudioMixer::playSample(const std::string &tag, uint32_t ticks, float volume) {

	int channel = playSample(tag, -1, -1, ticks);
	if(channel != -1) setChannelVolume(channel, volume);
	return channel;
}



/*
 * @param	tag The ID of the audio sample
 *
 * @param	volume The volume the audio sample will be played at ranging from 0.0 to 1.0
 *
 * @return	The channel the audio sample is being played on or -1 on error
 *
 * Plays an audio sample given by its tag once at the given volume
 */
int AudioMixer::playSample(const std::string &tag, float volume) {

	int channel = playSample(tag, -1, 0, -1);
	if(channel != -1) setChannelVolume(channel, volume);
	return channel;
}



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
int AudioMixer::playSample(const GameCamera &camera, const Position &origin, const std::string &tag, float volume) {

	int channel = playSample(tag, -1, 0, -1);
	if(channel != -1) {

		Position listener(camera.getPos().xPos(), camera.getPos().yPos());

		/*
		 * The angle ranges from 0 degrees to 360 degrees
		 * 0 = directly in front
		 * 90 = directly to the right
		 * 180 = directly behind
		 * 270 = directly to the left
		 */
		const double pi = 3.14159;
		double theta = std::atan2(listener.yPos() - origin.yPos(), listener.xPos() - origin.xPos()) * (180.0 / pi);
		Sint16 angle = static_cast<Sint16>(theta + 90.5 - 180.0);
		if (angle < 0)
			angle += 360;

		//The distance factor ranges from 0(near) to 255(far)
		double distance = std::sqrt(std::pow(listener.xPos() - origin.xPos(), 2.0) + std::pow(listener.yPos() - origin.yPos(), 2.0));
		Uint8 distanceFactor = static_cast<Uint8>(std::abs(distance/15.938) + 0.5);
		if(distanceFactor > 255) distanceFactor = 255;

		Mix_SetPosition(channel, angle, distanceFactor);
		setChannelVolume(channel, volume);
	}
	return channel;
}



/*
 * @param	tag The ID of the audio sample
 *
 * @param	volume The volume of the audio sample ranging from 0.0 to 1.0
 *
 * Sets the volume that the given audio sample will be played at
 */
void AudioMixer::setSampleVolume(const std::string &tag, float volume) {

	if(!this->hasBeenInit) {
		logger->message(Logger::Level::ERROR, "Mixer has not been initialized cannot set volume!", Logger::Output::TXT_FILE);
		return;
	}

	SDLMixChunkWrapper *sample = getSample(tag);
	if(sample == nullptr) {
		logger->message(Logger::Level::ERROR, "Cannot set the volume for sample, '" + tag + "' sample cannot be found!", Logger::Output::TXT_FILE);
		return;
	}

	std::abs(volume) > 1.0f ? Mix_VolumeChunk(sample->get(), 128) : Mix_VolumeChunk(sample->get(), static_cast<int>(128.0f * std::abs(volume) + 0.5f));
}



/*
 * @param	channel The ID of the channel, passing -1 will set all channels
 *
 * @param	volume The volume of the channel ranging from 0.0 to 1.0
 *
 * Sets the volume that the given channel will be played at
 */
void AudioMixer::setChannelVolume(int channel, float volume) {
	std::abs(volume) > 1.0f ? Mix_Volume(channel, 128) : Mix_Volume(channel, static_cast<int>(128.0f * std::abs(volume) + 0.5f));
}



/*
 * @param	channel The ID of the channel
 *
 * Gets the volume of the given channel
 */
int AudioMixer::getChannelVolume(int channel) const {
	return Mix_Volume(channel, -1);
}



/*
 * @param	channel The ID of the channel
 *
 * Stops the given channel
 */
void AudioMixer::stopChannel(int channel) {
	Mix_HaltChannel(channel);
}



/*
 * @param	channel The ID of the channel
 *
 * @param	ticks The amount of time in milliseconds until the channel is stopped
 *
 * Stops the given channel
 */
void AudioMixer::stopChannel(int channel, int ticks) {
	Mix_ExpireChannel(channel, ticks);
}



/*
 * @param	channel The ID of the channel
 *
 * Pauses the given channel
 * only channels that are currently playing can be paused
 */
void AudioMixer::pauseChannel(int channel) {
	Mix_Pause(channel);
}



/*
 * @param	channel The ID of the channel
 *
 * Unpause the given channel
 * only channels that are currently paused can be unpaused
 */
void AudioMixer::unpauseChannel(int channel) {
	Mix_Resume(channel);
}



/*
 * @param	channel The ID of the channel
 *
 * Checks if the given channel is playing
 */
bool AudioMixer::isChannelPlaying(int channel) const {
	return Mix_Playing(channel) && !Mix_Paused(channel);
}



/*
 * @param	channel The ID of the channel
 *
 * Checks if the given channel is paused
 */
bool AudioMixer::isChannelPaused(int channel) const {
	return Mix_Paused(channel);
}



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
int AudioMixer::playSample(const std::string &tag, int channel, int loops, uint32_t ticks) {

	if(!this->hasBeenInit) {
		logger->message(Logger::Level::ERROR, "Mixer has not been initialized cannot play sample!", Logger::Output::TXT_FILE);
		return -1;
	}

	SDLMixChunkWrapper *sample = getSample(tag);
	if(sample == nullptr) {
		logger->message(Logger::Level::ERROR, "Cannot play sample, '" + tag + "' cannot be found!", Logger::Output::TXT_FILE);
		return -1;
	}

	return Mix_PlayChannelTimed(channel, sample->get(), loops, ticks);
}



/*
 * @nullable
 *
 * @return	Pointer to the audio sample wrapper or null if the tag cannot be found
 */
SDLMixChunkWrapper* AudioMixer::getSample(const std::string &tag) {
	auto itr = this->samples.find(tag);
	return itr == this->samples.end() ? nullptr : itr->second.get();
}








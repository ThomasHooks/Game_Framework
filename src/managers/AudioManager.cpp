//============================================================================
// Name       		: AudioManager.cpp
// Author     		: Thomas Hooks
// Last Modified	: Apr 7, 2020
//============================================================================




#include "SDL_mixer.h"
#include "AudioManager.h"
#include "../utilities/GameLogger.h"
#include "../utilities/wrappers/SDLMixChunkWrapper.h"




AudioManager::AudioManager(GameLogger *loggerPtr)
	: logger(loggerPtr),
	  hasBeenInit(false) {

	logger->message(EnumLogLevel::INFO, "Starting Audio Manager", EnumLogOutput::TXT_FILE);
}



AudioManager::~AudioManager() {

	logger->message(EnumLogLevel::INFO, "Stopping Audio Manager", EnumLogOutput::TXT_FILE);
	deregisterAllSamples();

	logger->message(EnumLogLevel::INFO, "Unloading dynamic mixer libraries", EnumLogOutput::TXT_FILE);
	while(Mix_Init(0)) {
		Mix_Quit();
	}

	logger->message(EnumLogLevel::INFO, "Quitting SDL Mixer", EnumLogOutput::TXT_FILE);
	Mix_CloseAudio();
	logger->message(EnumLogLevel::INFO, "Audio Manager stopped", EnumLogOutput::TXT_FILE);
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
bool AudioManager::init() {

	if(!this->hasBeenInit) {
		logger->message(EnumLogLevel::INFO, "Initializing Audio Manager", EnumLogOutput::TXT_FILE);

		int formats = MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG;
		int mixerFlag = Mix_Init(formats);
		if(mixerFlag & formats != formats) {
			std::string mixerErrorCode = Mix_GetError();
			logger->message(EnumLogLevel::ERROR, "SDL Mixer failed to initialize! Error Code: " + mixerErrorCode, EnumLogOutput::TXT_FILE);
			return false;
		}

		Mix_AllocateChannels(NUMBEROFCHANNELS);

		mixerFlag = Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);
		if(mixerFlag == -1) {
			std::string mixerErrorCode = Mix_GetError();
			logger->message(EnumLogLevel::ERROR, "SDL Mixer failed to initialize! Error Code: " + mixerErrorCode, EnumLogOutput::TXT_FILE);
			return false;
		}

		this->hasBeenInit = true;
		logger->message(EnumLogLevel::INFO, "Audio Manager has been initialized", EnumLogOutput::TXT_FILE);
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
bool AudioManager::registerSample(const std::string &tag, const std::string &location) {

	if(!this->hasBeenInit) {
		logger->message(EnumLogLevel::ERROR, "Mixer has not been initialized cannot register samples!", EnumLogOutput::TXT_FILE);
		return false;
	}

	logger->message(EnumLogLevel::INFO, "Registering sample '" + tag + "' at '" + location + "'", EnumLogOutput::TXT_FILE);
	auto itr = this->samples.insert({tag, std::make_unique<SDLMixChunkWrapper>(location)});
	if(!itr.second) {
		//Tag isn't unique
		logger->message(EnumLogLevel::ERROR, "The sample was not registered tag: '" + tag + "' is not unique!", EnumLogOutput::TXT_FILE);
		return itr.second;
	}
	if(itr.first->second->get() == nullptr) {
		//Failed to load the audio file
		std::string mixerErrorCode = Mix_GetError();
		logger->message(EnumLogLevel::ERROR, "Could not load sample '" + tag + "' at '" + location + "' Error Code: " + mixerErrorCode, EnumLogOutput::TXT_FILE);
		this->samples.erase(tag);
		return false;
	}

	logger->message(EnumLogLevel::INFO, "Sample '" + tag + "' has been registered", EnumLogOutput::TXT_FILE);
	return itr.second;
}



/*
 * @param	tag The ID of the audio sample to be deregistered
 *
 * @return	True if tag was successfully deregistered
 *
 * Deregister the audio sample specified by its tag
 */
bool AudioManager::deregisterSample(const std::string &tag) {

	if(!this->hasBeenInit) {
		logger->message(EnumLogLevel::ERROR, "Mixer has not been initialized cannot deregister samples!", EnumLogOutput::TXT_FILE);
		return false;
	}

	logger->message(EnumLogLevel::INFO, "Deregistering sample '" + tag + "'", EnumLogOutput::TXT_FILE);
	this->samples.erase(tag);
	logger->message(EnumLogLevel::INFO, "Sample '" + tag +"' has been deregistered", EnumLogOutput::TXT_FILE);
	return true;
}



//Deregister all audio samples in the Audio Manager
void AudioManager::deregisterAllSamples() {

	if(!this->hasBeenInit) {
		logger->message(EnumLogLevel::ERROR, "Mixer has not been initialized cannot deregister sample!", EnumLogOutput::TXT_FILE);
		return;
	}

	logger->message(EnumLogLevel::INFO, "Deregistering all samples", EnumLogOutput::TXT_FILE);
	auto itr = this->samples.begin();
	while(itr != this->samples.end()) {
		std::string tag = itr->first;
		logger->message(EnumLogLevel::INFO, "Deregistering sample '" + tag + "'", EnumLogOutput::TXT_FILE);
		itr = this->samples.erase(itr);
		logger->message(EnumLogLevel::INFO, "Sample '" + tag + "' has been deregistered", EnumLogOutput::TXT_FILE);
	}
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
 * @return The channel the audio sample is being played on
 *
 * Plays an audio sample given by its tag
 */
int AudioManager::playSample(const std::string &tag, int channel, int loops) {

	if(!this->hasBeenInit) {
		logger->message(EnumLogLevel::ERROR, "Mixer has not been initialized cannot play sample!", EnumLogOutput::TXT_FILE);
		return -1;
	}

	SDLMixChunkWrapper *sound = getSample(tag);
	if(sound == nullptr) {
		logger->message(EnumLogLevel::ERROR, "Cannot play sample, '" + tag + "' cannot be found!", EnumLogOutput::TXT_FILE);
		return -1;
	}

	return Mix_PlayChannel(channel, sound->get(), loops);
}



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
int AudioManager::playSample(const std::string &tag, int loops) {
	return playSample(tag, -1, loops);
}



/*
 * @param	tag The ID of the audio sample
 *
 * @return The channel the audio sample is being played on
 *
 * Plays an audio sample given by its tag once
 */
int AudioManager::playSample(const std::string &tag) {
	return playSample(tag, -1, 0);
}



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
int AudioManager::playSampleTimed(const std::string &tag, int channel, unsigned int ticks) {

	if(!this->hasBeenInit) {
		logger->message(EnumLogLevel::ERROR, "Mixer has not been initialized cannot play sample!", EnumLogOutput::TXT_FILE);
		return -1;
	}

	SDLMixChunkWrapper *sample = getSample(tag);
	if(sample == nullptr) {
		logger->message(EnumLogLevel::ERROR, "Cannot play sample, '" + tag + "' cannot be found!", EnumLogOutput::TXT_FILE);
		return -1;
	}

	return Mix_PlayChannelTimed(channel, sample->get(), -1, ticks);
}



/*
 * @param	tag The ID of the audio sample
 *
 * @param	ticks The amount of time the sample is played in millisecond
 *
 * @return The channel the audio sample is being played on
 *
 * Plays an audio sample given by its tag for a certain amount of time
 */
int AudioManager::playSampleTimed(const std::string &tag, unsigned int ticks) {
	return playSample(tag, -1, ticks);
}



/*
 * @param	tag The ID of the audio sample
 *
 * @param	volume The volume of the audio sample ranging from 0 to 128
 *
 * Sets the volume that the given audio sample will be played at
 */
void AudioManager::setSampleVolume(const std::string &tag, int volumeIn) {

	if(!this->hasBeenInit) {
		logger->message(EnumLogLevel::ERROR, "Mixer has not been initialized cannot set volume!", EnumLogOutput::TXT_FILE);
		return;
	}

	SDLMixChunkWrapper *sample = getSample(tag);
	if(sample == nullptr) {
		logger->message(EnumLogLevel::ERROR, "Cannot set the volume for sample, '" + tag + "' sample cannot be found!", EnumLogOutput::TXT_FILE);
		return;
	}

	int volume;
	volumeIn < 0 ? volume = 0 : volume = volumeIn;
	Mix_VolumeChunk(sample->get(), volume);
}



/*
 * @param	channel The ID of the channel
 *
 * @param	volume The volume of the channel ranging from 0 to 128
 *
 * Sets the volume that the given channel will be played at
 */
void AudioManager::setChannelVolume(int channel, int volumeIn) {

	int volume;
	volumeIn < 0 ? volume = 0 : volume = volumeIn;
	Mix_Volume(channel, volume);
}



/*
 * @param	channel The ID of the channel
 *
 * Gets the volume of the given channel
 */
int AudioManager::getChannelVolume(int channel) const {
	return Mix_Volume(channel, -1);
}



/*
 * @param	channel The ID of the channel
 *
 * Stops the given channel
 */
void AudioManager::stopChannel(int channel) {
	Mix_HaltChannel(channel);
}



/*
 * @param	channel The ID of the channel
 *
 * @param	ticks The amount of time in milliseconds until the channel is stopped
 *
 * Stops the given channel
 */
void AudioManager::stopChannel(int channel, int ticks) {
	Mix_ExpireChannel(channel, ticks);
}



/*
 * @param	channel The ID of the channel
 *
 * Pauses the given channel
 * only channels that are currently playing can be paused
 */
void AudioManager::pauseChannel(int channel) {
	Mix_Pause(channel);
}



/*
 * @param	channel The ID of the channel
 *
 * Unpause the given channel
 * only channels that are currently paused can be unpaused
 */
void AudioManager::unpauseChannel(int channel) {
	Mix_Resume(channel);
}



/*
 * @param	channel The ID of the channel
 *
 * Checks if the given channel is playing
 */
bool AudioManager::isChannelPlaying(int channel) const {
	return Mix_Playing(channel) && !Mix_Paused(channel);
}



/*
 * @param	channel The ID of the channel
 *
 * Checks if the given channel is paused
 */
bool AudioManager::isChannelPaused(int channel) const {
	return Mix_Paused(channel);
}



/*
 * @nullable
 *
 * @return	Pointer to the audio sample wrapper or null if the tag cannot be found
 */
SDLMixChunkWrapper* AudioManager::getSample(const std::string &tag) {
	auto itr = this->samples.find(tag);
	return itr == this->samples.end() ? nullptr : itr->second.get();
}








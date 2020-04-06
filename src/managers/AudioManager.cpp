//============================================================================
// Name       		: AudioManager.cpp
// Author     		: Thomas Hooks
// Last Modified	: Apr 5, 2020
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
	deregisterAllSFX();

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
 * @param	tag The ID of the sound
 *
 * @param	location The location of the sound file
 * 					 supports WAVE, AIFF, RIFF, OGG, and VOC audio files
 *
 * @return	True if the sound was successfully registered
 *
 * Register a sound to the Audio Manager
 */
bool AudioManager::registerSFX(const std::string &tag, const std::string &location) {

	if(!this->hasBeenInit) {
		logger->message(EnumLogLevel::ERROR, "Mixer has not been initialized cannot register sounds!", EnumLogOutput::TXT_FILE);
		return false;
	}

	logger->message(EnumLogLevel::INFO, "Registering sound '" + tag + "' at '" + location + "'", EnumLogOutput::TXT_FILE);
	auto itr = this->sounds.insert({tag, std::make_unique<SDLMixChunkWrapper>(location)});
	if(!itr.second) {
		//Tag isn't unique
		logger->message(EnumLogLevel::ERROR, "The sound was not registered tag: '" + tag + "' is not unique!", EnumLogOutput::TXT_FILE);
		return itr.second;
	}
	if(itr.first->second->get() == nullptr) {
		//Failed to load the audio file
		std::string mixerErrorCode = Mix_GetError();
		logger->message(EnumLogLevel::ERROR, "Could not load sound '" + tag + "' at '" + location + "' Error Code: " + mixerErrorCode, EnumLogOutput::TXT_FILE);
		this->sounds.erase(tag);
		return false;
	}

	logger->message(EnumLogLevel::INFO, "Sound '" + tag + "' has been registered", EnumLogOutput::TXT_FILE);
	return itr.second;
}



/*
 * @param	tag The ID of the texture to be deregistered
 *
 * @return	True if tag was successfully deregistered
 *
 * Deregister the sound specified by its tag
 */
bool AudioManager::deregisterSFX(const std::string &tag) {

	if(!this->hasBeenInit) {
		logger->message(EnumLogLevel::ERROR, "Mixer has not been initialized cannot deregister sounds!", EnumLogOutput::TXT_FILE);
		return false;
	}

	logger->message(EnumLogLevel::INFO, "Deregistering sound '" + tag + "'", EnumLogOutput::TXT_FILE);
	this->sounds.erase(tag);
	logger->message(EnumLogLevel::INFO, "Sound '" + tag +"' has been deregistered", EnumLogOutput::TXT_FILE);
	return true;
}



//Deregister all sounds in the Audio Manager
void AudioManager::deregisterAllSFX() {

	if(!this->hasBeenInit) {
		logger->message(EnumLogLevel::ERROR, "Mixer has not been initialized cannot deregister sounds!", EnumLogOutput::TXT_FILE);
		return;
	}

	logger->message(EnumLogLevel::INFO, "Deregistering all sounds", EnumLogOutput::TXT_FILE);
	auto itr = this->sounds.begin();
	while(itr != this->sounds.end()) {
		std::string tag = itr->first;
		logger->message(EnumLogLevel::INFO, "Deregistering sound '" + tag + "'", EnumLogOutput::TXT_FILE);
		itr = this->sounds.erase(itr);
		logger->message(EnumLogLevel::INFO, "sound '" + tag + "' has been deregistered", EnumLogOutput::TXT_FILE);
	}
}



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
int AudioManager::playSFX(const std::string &tag, int channel, int loops) {

	if(!this->hasBeenInit) {
		logger->message(EnumLogLevel::ERROR, "Mixer has not been initialized cannot play sound!", EnumLogOutput::TXT_FILE);
		return -1;
	}

	SDLMixChunkWrapper *sound = getSound(tag);
	if(sound == nullptr) {
		logger->message(EnumLogLevel::ERROR, "Cannot play sound, '" + tag + "' cannot be found!", EnumLogOutput::TXT_FILE);
		return -1;
	}

	return Mix_PlayChannel(channel, sound->get(), loops);
}



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
int AudioManager::playSFX(const std::string &tag, int loops) {
	return playSFX(tag, -1, loops);
}



/*
 * @param	tag The ID of the sound
 *
 * @return The channel the sound is being played on
 *
 * Plays a sound given by its tag once
 */
int AudioManager::playSFX(const std::string &tag) {
	return playSFX(tag, -1, 0);
}



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
int AudioManager::playSFX(const std::string &tag, int channel, unsigned int ticks) {

	if(!this->hasBeenInit) {
		logger->message(EnumLogLevel::ERROR, "Mixer has not been initialized cannot play sound!", EnumLogOutput::TXT_FILE);
		return -1;
	}

	SDLMixChunkWrapper *sound = getSound(tag);
	if(sound == nullptr) {
		logger->message(EnumLogLevel::ERROR, "Cannot play sound, '" + tag + "' cannot be found!", EnumLogOutput::TXT_FILE);
		return -1;
	}

	return Mix_PlayChannelTimed(channel, sound->get(), -1, ticks);
}



/*
 * @param	tag The ID of the sound
 *
 * @param	ticks The amount of time the sound is played in millisecond
 *
 * @return The channel the sound is being played on
 *
 * Plays a sound given by its tag for a certain amount of time
 */
int AudioManager::playSFX(const std::string &tag, unsigned int ticks) {
	return playSFX(tag, -1, ticks);
}



/*
 * @nullable
 *
 * @return	Pointer to the sound wrapper or null if the tag cannot be found
 */
SDLMixChunkWrapper* AudioManager::getSound(const std::string &tag) {
	auto itr = this->sounds.find(tag);
	return itr == this->sounds.end() ? nullptr : itr->second.get();
}








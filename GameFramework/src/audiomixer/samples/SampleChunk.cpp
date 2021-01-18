#include <SDL_mixer.h>

#include "audiomixer/samples/SampleChunk.h"




SampleChunk::SampleChunk(const std::string &location)
	: m_sfx(nullptr)
{

	m_sfx = Mix_LoadWAV(location.c_str());
}



SampleChunk::~SampleChunk() 
{
	Mix_FreeChunk(m_sfx);
	m_sfx = nullptr;
}








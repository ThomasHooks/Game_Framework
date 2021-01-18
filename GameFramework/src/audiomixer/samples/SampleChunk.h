#ifndef SAMPLECHUNK_H_
#define SAMPLECHUNK_H_


#include <string>




/// <summary>
/// Encapsulates SDL Mix Chunks
/// <para>
/// this can store WAVE, AIFF, RIFF, OGG, and VOC audio files
/// </para>
/// </summary>
class SampleChunk 
{
public:

	SampleChunk(const std::string &location);



	~SampleChunk();
	
	

	/// <summary>
	/// <para>nullable</para>
	/// Gets the SDL sound that is in this wrapper
	/// </summary>
	struct Mix_Chunk* expose() { return m_sfx; }



private:

	struct Mix_Chunk *m_sfx;
};


#endif




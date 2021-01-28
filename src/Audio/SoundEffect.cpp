#include "SoundEffect.h"

#include "../Assert.h"
#include <stb_vorbis.h>

namespace Aegis{

	SoundEffect::SoundEffect(const std::string& file_path)
	{
		int channels, sample_rate, samples;
		short* data;

		samples = stb_vorbis_decode_filename(file_path.c_str(), &channels, &sample_rate, &data);
		AE_ASSERT(samples != -1, "Unable to decode .ogg file. Make sure the path is valid.");

		alGenBuffers(1, &buffer_);
		alBufferData(buffer_, AL_FORMAT_STEREO16, data, samples * channels * sizeof(short), sample_rate);

		alGenSources(1, &source_);
		alSourceQueueBuffers(source_, 1, &buffer_);
	}

	SoundEffect::~SoundEffect()
	{
		alDeleteSources(1, &source_);
		alDeleteBuffers(1, &buffer_);
	}

	void SoundEffect::Play()
	{
		alSourcePlay(source_);
	}
	void SoundEffect::Stop()
	{
		alSourceStop(source_);
	}
	bool SoundEffect::IsPlaying()
	{
		ALenum state;
		alGetSourcei(source_, AL_SOURCE_STATE, &state);

		return state == AL_PLAYING;
	}
}

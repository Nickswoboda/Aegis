#include "SoundEffect.h"

#include "../Assert.h"
#include <stb_vorbis.h>

namespace Aegis{

	SoundEffect::SoundEffect(const std::string& file_path, unsigned int volume)
	{
		//clamp between 0 and 100
		volume_ = volume < 0 ? 0 : (volume > 100 ? 1 : (volume/100.0f));
		int channels, sample_rate, samples;
		short* data;

		samples = stb_vorbis_decode_filename(file_path.c_str(), &channels, &sample_rate, &data);
		AE_ASSERT(samples != -1, "Unable to decode .ogg file. Make sure the path is valid.");

		auto format = channels == 1 ? AL_FORMAT_STEREO8 : AL_FORMAT_STEREO16;
		
		alGenBuffers(1, &buffer_id_);
		alBufferData(buffer_id_, format, data, samples * channels * sizeof(short), sample_rate);

		alGenSources(1, &source_id_);
		alSourceQueueBuffers(source_id_, 1, &buffer_id_);
	}

	SoundEffect::~SoundEffect()
	{
		alDeleteSources(1, &source_id_);
		alDeleteBuffers(1, &buffer_id_);
	}

	void SoundEffect::Stop()
	{
		alSourceStop(source_id_);
	}
	bool SoundEffect::IsPlaying()
	{
		ALenum state;
		alGetSourcei(source_id_, AL_SOURCE_STATE, &state);

		return state == AL_PLAYING;
	}
}

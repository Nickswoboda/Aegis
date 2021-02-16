#pragma once

#include <AL/al.h>
#include <stb_vorbis.h>

namespace Aegis{

	struct Sound
	{
		stb_vorbis* stream;
		
		int samples;
		unsigned int sample_rate;

		int channels;
		int format;

		short* data = nullptr;

		float volume = 1.0f;
		bool looping;
		bool streaming;

		static const int buffer_size = 8192;
		static const int num_buffers = 4;
		ALuint buffer_ids[num_buffers];
	};
}

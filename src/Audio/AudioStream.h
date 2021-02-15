#pragma once

#include <AL/al.h>
#include <stb_vorbis.h>

#include <string>
namespace Aegis {
	class AudioStream
	{
	public:

		struct StreamData 
		{
			stb_vorbis* stream;
			stb_vorbis_info info;
			int samples;
			short* data;
			int format;

		};
		AudioStream(const std::string& path, unsigned int volume = 100, bool looping = false);

		~AudioStream();

		void Play();
		void Update();
		void Stop();

		static const int num_buffers_ = 4;
		static const int buffer_samples_ = 8192;
		
		StreamData stream_data_;
		ALuint buffer_ids_[num_buffers_];
		ALuint source_id_;
		unsigned int volume_;
		bool looping_;
	};
}
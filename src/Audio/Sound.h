#pragma once

#include <AL/al.h>
#include <stb_vorbis.h>

#include <string>

namespace Aegis{

	class Sound
	{
		friend class AudioPlayer;
	public:
		Sound(const std::string& path, bool looping, bool streaming);
		~Sound();

	private:
		void StartStream(unsigned int volume);
		bool UpdateBuffer(ALuint buffer_id);

		stb_vorbis* stream_;
		
		int samples_;
		unsigned int sample_rate_;

		int channels_;
		int format_;

		short* data_ = nullptr;

		float volume_ = 1.0f;
		bool looping_;
		bool streaming_;

		static const int buffer_size_ = 4096;
		static const int num_buffers_ = 4;
		ALuint buffer_ids_[num_buffers_];
	};
}

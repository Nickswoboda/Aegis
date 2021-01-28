#pragma once

#include <AL/al.h>

#include <string>

namespace Aegis{
	class SoundEffect
	{
	public:
		SoundEffect(const std::string& file_path);
		~SoundEffect();

		void Play();
		void Stop();
		bool IsPlaying();

		ALuint buffer_ = 0;
		ALuint source_ = 0;
	};
}

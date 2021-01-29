#pragma once

#include <AL/al.h>

#include <string>

namespace Aegis{
	class SoundEffect
	{
	public:
		SoundEffect(const std::string& file_path);
		~SoundEffect();

		void Stop();
		bool IsPlaying();

		ALuint buffer_id_ = 0;
		ALuint source_id_ = 0;
	};
}

#pragma once

#include <AL/al.h>

#include <string>

namespace Aegis{
	class SoundEffect
	{
	public:
		SoundEffect(const std::string& file_path, unsigned int volume = 100, bool looping = false);
		~SoundEffect();

		void Stop();
		bool IsPlaying();
		float GetVolume() const { return volume_; }

		ALuint buffer_id_ = 0;
		ALuint source_id_ = 0;
	private:
		float volume_ = 1.0f;
	};
}

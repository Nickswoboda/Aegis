#pragma once

#include "SoundEffect.h"
#include "AudioStream.h"

#include <AL/alc.h>

namespace Aegis
{
	class AudioPlayer
	{
	public:
		~AudioPlayer();

		static void Init();
		static void SetVolume(unsigned int volume);
		static void Play(const SoundEffect& sound, unsigned int volume = 100);
		static void Stream(AudioStream& stream, unsigned int volume = 100);
		static void Update();

	private:
		static ALCdevice* device_;
		static ALCcontext* context_;
	};

}

#pragma once

#include "Sound.h"

#include <AL/alc.h>

#include <unordered_map>
#include <memory>

namespace Aegis
{
	typedef unsigned int SoundID;

	class AudioPlayer
	{
	public:
		static void Init();
		static void Update();
		static void Shutdown();

		static SoundID LoadSound(const std::string& path, bool looping = false, bool streaming = false);
		static void UnloadSound(SoundID id);

		static void PlaySound(SoundID id, unsigned int volume = 100);
		static void StopSound(SoundID id);

		static void SetMasterVolume(unsigned int volume);
		static void SetSoundVolume(SoundID id, unsigned int volume);

	private:

		static void DeleteSound(SoundID id);
		static ALCdevice* device_;
		static ALCcontext* context_;

		static std::unordered_map<SoundID, std::shared_ptr<Sound>> sound_map_;
		static float master_volume_;
	};

}

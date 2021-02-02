#include "AudioPlayer.h"

#include "../Assert.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <stb_vorbis.h>

#include <iostream>
#include <vector>

namespace Aegis {

	ALCdevice* AudioPlayer::device_ = nullptr;
	ALCcontext* AudioPlayer::context_ = nullptr;

	static std::vector<const SoundEffect*> currently_playing_;
	static unsigned int volume_ = 100;
	void AudioPlayer::Init()
	{
		device_ = alcOpenDevice(nullptr);
		AE_ASSERT(device_, "Unable to open get sound device");

		context_ = alcCreateContext(device_, nullptr);
		AE_ASSERT(context_, "Unable to open audio context");
		
		AE_ASSERT(alcMakeContextCurrent(context_), "Unable set current audio context");

		const ALCchar* name = nullptr;
		if (alcIsExtensionPresent(device_, "ALC_ENUMERATE_ALL_EXT"))
			name = alcGetString(device_, ALC_ALL_DEVICES_SPECIFIER);
		if (!name || alcGetError(device_) != AL_NO_ERROR)
			name = alcGetString(device_, ALC_DEVICE_SPECIFIER);

		std::cout << "Audio Device Opened: " << name << "\n";
	}

	AudioPlayer::~AudioPlayer()
	{
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(context_);
		alcCloseDevice(device_);
	}

	void AudioPlayer::Play(const SoundEffect& sound,  unsigned int volume)
	{
		volume = volume < 0 ? 0 : (volume > 100 ? 100 : volume);
		alSourcef(sound.source_id_, AL_GAIN, sound.GetVolume() *  (volume / 100.0f) * (volume_/100.0f));
		alSourcePlay(sound.source_id_);

		currently_playing_.push_back(&sound);
	}

	void AudioPlayer::SetVolume(unsigned int volume)
	{
		//clamp to between 0 and 100
		volume_ = volume < 0 ? 0 : (volume > 100 ? 100 : volume);
		
		for (auto& sound : currently_playing_){
			alSourcef(sound->source_id_, AL_GAIN, sound->GetVolume() * (volume_ / 100.0f));
		}
	}
}

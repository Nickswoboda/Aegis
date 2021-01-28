#include "AudioPlayer.h"

#include "../Assert.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <stb_vorbis.h>

#include <iostream>

namespace Aegis {

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
}

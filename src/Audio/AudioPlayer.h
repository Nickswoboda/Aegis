#pragma once

#include "SoundEffect.h"

#include <AL/alc.h>

namespace Aegis
{
	class AudioPlayer
	{
	public:
		~AudioPlayer();

		void Init();

		ALCdevice* device_;
		ALCcontext* context_;
	};

}

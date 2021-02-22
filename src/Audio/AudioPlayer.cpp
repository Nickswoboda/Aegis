#include "AudioPlayer.h"

#include "../Core/Assert.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <stb_vorbis.h>

#include <iostream>
#include <vector>

namespace Aegis {

	ALCdevice* AudioPlayer::device_ = nullptr;
	ALCcontext* AudioPlayer::context_ = nullptr;

	std::unordered_map<std::string, SoundID> AudioPlayer::id_map_;
	std::unordered_map<SoundID, std::shared_ptr<Sound>> AudioPlayer::sound_map_;
	std::unordered_set<SoundID> AudioPlayer::playing_set_;
	float AudioPlayer::master_volume_ = 1.0f;

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

	void AudioPlayer::Shutdown()
	{
		for (auto it : sound_map_) {
			DeleteSound(it.first);
		}
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(context_);
		alcCloseDevice(device_);
	}

	SoundID AudioPlayer::LoadSound(const std::string& path, bool looping, bool streaming)
	{
		if (id_map_.count(path)) {
			return id_map_[path];
		}

		auto sound = std::make_shared<Sound>();
        sound->stream = stb_vorbis_open_filename(path.c_str(), NULL, NULL);
        auto info = stb_vorbis_get_info(sound->stream);
		sound->samples = stb_vorbis_stream_length_in_samples(sound->stream) * info.channels;
		sound->sample_rate = info.sample_rate;
		sound->channels = info.channels;
		sound->format = sound->channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
		sound->looping = looping;
		sound->streaming = streaming;
		AE_ASSERT(sound->samples != -1, "Unable to decode .ogg file. Make sure the path is valid.");
		
		ALuint source_id;
        alGenSources(1, &source_id);

		if (!streaming){
			int data_size = sound->samples * sound->channels * sizeof(short);
			sound->data = new short[data_size];
            int amount = stb_vorbis_get_samples_short_interleaved(sound->stream, sound->channels, sound->data, sound->samples*sound->channels);
			alGenBuffers(1, &sound->buffer_ids[0]);
			alBufferData(sound->buffer_ids[0], sound->format, sound->data, data_size, sound->sample_rate);
			delete[] sound->data;
			sound->data = nullptr;

			alSourceQueueBuffers(source_id, 1, &sound->buffer_ids[0]);
			alSourcei(source_id, AL_LOOPING, looping);

		} else {
			sound->data = new short[sound->buffer_size];
			alGenBuffers(sound->num_buffers, sound->buffer_ids);
		}

		id_map_[path] = source_id;
		sound_map_[source_id] = sound;
		return source_id;
	}

	void AudioPlayer::DeleteSound(SoundID id)
	{
		auto sound = sound_map_[id];
		if (sound->data != nullptr) {
			delete[] sound->data;
		}
		alDeleteSources(1, &id);
		if (sound->streaming) {
			alDeleteBuffers(sound->num_buffers, sound->buffer_ids);
		}
		else {
			alDeleteBuffers(1, &sound->buffer_ids[0]);
		}
	}

	void AudioPlayer::UnloadSound(SoundID id)
	{
		if (!sound_map_.count(id)){
			std::cout << "No sound found with id: " << id << "\n";
			return;
		} else {
			DeleteSound(id);
			sound_map_.erase(id);
		}
	}

	void AudioPlayer::PlaySound(SoundID id, unsigned int volume)
	{
 		AE_ASSERT(sound_map_.count(id), "Unable to play sound. Sound with id " << id << "not found\n");
		
		volume = volume < 0 ? 0 : (volume > 100 ? 100 : volume);
		alSourcef(id, AL_GAIN, (volume / 100.0f) * master_volume_);

		auto sound = sound_map_[id];
		sound->volume = volume;

		if (sound->streaming){
			alSourceRewind(id);
			alSourcei(id, AL_BUFFER, 0);
			//DECLARE, processed, state, amount, which TYPE int

			stb_vorbis_seek_start(sound->stream);
			for (int i = 0; i < sound->num_buffers; ++i) {
				int amount = stb_vorbis_get_samples_short_interleaved(sound->stream, sound->channels, sound->data, sound->buffer_size);
				alBufferData(sound->buffer_ids[i], sound->format, sound->data, sound->buffer_size * sizeof(short), sound->sample_rate);

				if (amount == 0) {
					break;
				}
			}

			alSourceQueueBuffers(id, sound->num_buffers, sound->buffer_ids);
		} 
		alSourcePlay(id);
		playing_set_.insert(id);
	}

	void AudioPlayer::StopSound(SoundID id)
	{
		alSourceStop(id);
		playing_set_.erase(id);
	}

	void AudioPlayer::Update()
	{
		std::vector<SoundID> stopped;

		for (SoundID id : playing_set_){

			int state;
			alGetSourcei(id, AL_SOURCE_STATE, &state);
			if (state == AL_STOPPED) {
				stopped.push_back(id);
				continue;
			}
			auto sound = sound_map_[id];

			if (sound->streaming){
				int processed;
				alGetSourcei(id, AL_BUFFERS_PROCESSED, &processed);

				while (processed > 0) {
					int amount = stb_vorbis_get_samples_short_interleaved(sound->stream, sound->channels, sound->data, sound->buffer_size);
					if (amount == 0) {
						if (sound->looping) {
							stb_vorbis_seek_start(sound->stream);
							stb_vorbis_get_samples_short_interleaved(sound->stream, sound->channels, sound->data, sound->buffer_size);
						}
						else {
							break;
						}
					} 
					else {
						ALuint buffer;
						alSourceUnqueueBuffers(id, 1, &buffer);
						--processed;
						alBufferData(buffer, sound->format, sound->data, sound->buffer_size * sizeof(short), sound->sample_rate);
						alSourceQueueBuffers(id, 1, &buffer);
					}
				}
			}
		}

		for (auto id : stopped) {
			playing_set_.erase(id);
		}
	}

	void AudioPlayer::SetMasterVolume(unsigned int volume)
	{
		//clamp to between 0 and 100
		master_volume_ = volume < 0 ? 0 : (volume > 100 ? 1 : volume/100.0f);
		
		for (auto it : sound_map_) {
			alSourcef(it.first, AL_GAIN, it.second->volume * master_volume_);
		}
	}

	void AudioPlayer::SetSoundVolume(SoundID id, unsigned int volume)
	{
		if (sound_map_.count(id)){
			std::cout << "Unable to set volume of sound id: " << id << ". ID does not exist\n.";
			return;
		}

		volume = volume < 0 ? 0 : (volume > 100 ? 1 : volume/100.0f);
		alSourcef(id, AL_GAIN, volume * master_volume_);
		sound_map_[id]->volume = volume;
	}
}

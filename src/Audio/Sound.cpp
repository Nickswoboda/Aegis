#include "Sound.h"

#include "../Core/Assert.h"

namespace Aegis {
	Sound::Sound(const std::string& path, bool looping, bool streaming)
		:looping_(looping), streaming_(streaming)
	{
		stream_ = stb_vorbis_open_filename(path.c_str(), NULL, NULL);
		AE_ASSERT(stream_, "Unable to open .ogg file");

		auto info = stb_vorbis_get_info(stream_);
		samples_ = stb_vorbis_stream_length_in_samples(stream_) * info.channels;
		AE_ASSERT(samples_ != 0, "Unable to decode .ogg file.");

		sample_rate_ = info.sample_rate;
		channels_ = info.channels;
		AE_ASSERT((channels_ == 1 || channels_ == 2), ".ogg has unsupported number of channels.");

		format_ = channels_ == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

		if (!streaming) {
			int data_size = samples_ * channels_ * sizeof(short);
			data_ = new short[data_size];
			int amount = stb_vorbis_get_samples_short_interleaved(stream_, channels_, data_, samples_ * channels_);
			alGenBuffers(1, &buffer_ids_[0]);
			alBufferData(buffer_ids_[0], format_, data_, data_size, sample_rate_);
			delete[] data_;
			data_ = nullptr;
		} else {
			data_ = new short[buffer_size_];
			alGenBuffers(num_buffers_, buffer_ids_);
		}
	}

	Sound::~Sound()
	{
		if (data_ != nullptr) {
			delete[] data_;
		}
		if (streaming_) {
			alDeleteBuffers(num_buffers_, buffer_ids_);
		}
		else {
			alDeleteBuffers(1, &buffer_ids_[0]);
		}
	}

	void Sound::StartStream(unsigned int volume)
	{
		volume_ = volume;
		stb_vorbis_seek_start(stream_);
		for (int i = 0; i < num_buffers_; ++i) {
			int amount = stb_vorbis_get_samples_short_interleaved(stream_, channels_, data_, buffer_size_);
			alBufferData(buffer_ids_[i], format_, data_, buffer_size_ * sizeof(short), sample_rate_);

			if (amount == 0) {
				break;
			}
		}
	}

	bool Sound::UpdateBuffer(ALuint buffer_id)
	{
		int amount = stb_vorbis_get_samples_short_interleaved(stream_, channels_,data_, buffer_size_);
		if (amount == 0){
			if (looping_) {
				stb_vorbis_seek_start(stream_);
				amount = stb_vorbis_get_samples_short_interleaved(stream_, channels_, data_, buffer_size_);
			}
			else {
				stopped_ = true;
			}
		}

		if (amount != 0){
			alBufferData(buffer_id, format_, data_, buffer_size_ * sizeof(short), sample_rate_);
			return true;
		}
		else {
			return false;
		}
	}
}
#include "AudioStream.h"

#include "../Assert.h"

namespace Aegis {
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "AL/alext.h"

    AudioStream::AudioStream(const std::string& path, unsigned int volume, bool looping)
        : looping_(looping)
    {
        //clamp between 0 and 100
        volume_ = volume < 0 ? 0 : (volume > 100 ? 1 : (volume / 100.0f));


        stream_data_.stream = stb_vorbis_open_filename(path.c_str(), NULL, NULL);
        stream_data_.info = stb_vorbis_get_info(stream_data_.stream);

        stream_data_.samples = stb_vorbis_stream_length_in_samples(stream_data_.stream) * stream_data_.info.channels;

        AE_ASSERT(stream_data_.samples != -1, "Unable to decode .ogg file. Make sure the path is valid.");

        stream_data_.format = stream_data_.info.channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
        stream_data_.data = new short[buffer_samples_];

        alGenBuffers(num_buffers_, buffer_ids_);
        alGenSources(1, &source_id_);

    }

    AudioStream::~AudioStream()
    {
        alDeleteSources(1, &source_id_);
        alDeleteBuffers(num_buffers_, buffer_ids_);

        delete stream_data_.data;
    }

    /* Prebuffers some audio from the file, and starts playing the source */
    void AudioStream::Play()
    {
        ALsizei i;

        alSourceRewind(source_id_);
        alSourcei(source_id_, AL_BUFFER, 0);
        //DECLARE, processed, state, amount, which TYPE int

        stb_vorbis_seek_start(stream_data_.stream);
        for (int i = 0; i < num_buffers_; ++i) {
            int amount = stb_vorbis_get_samples_short_interleaved(stream_data_.stream, stream_data_.info.channels, stream_data_.data, buffer_samples_);
            alBufferData(buffer_ids_[i], stream_data_.format, stream_data_.data, buffer_samples_ * sizeof(short), stream_data_.info.sample_rate);

            if (amount == 0) {
                break;
            }
        }

        alSourceQueueBuffers(source_id_, num_buffers_, buffer_ids_);
        alSourcePlay(source_id_);
    }

    void AudioStream::Update()
    {
        int processed;

        alGetSourcei(source_id_, AL_BUFFERS_PROCESSED, &processed);

        while (processed > 0) {
            ALuint buffer;
            alSourceUnqueueBuffers(source_id_, 1, &buffer);
            --processed;
            int amount = stb_vorbis_get_samples_short_interleaved(stream_data_.stream, stream_data_.info.channels, stream_data_.data, buffer_samples_);
            if (amount > 0) {
                alBufferData(buffer, stream_data_.format, stream_data_.data, buffer_samples_ * sizeof(short), stream_data_.info.sample_rate);
                alSourceQueueBuffers(source_id_, 1, &buffer);
            }
        }

        int state;
        alGetSourcei(source_id_, AL_SOURCE_STATE, &state);

        if (state != AL_PLAYING && state != AL_PAUSED)
        {
            int queued;
            alGetSourcei(source_id_, AL_BUFFERS_QUEUED, &queued);
            if (queued != 0){
                alSourcePlay(source_id_);
            }
            else if (state == AL_STOPPED && looping_) {
                Play();
            }
        }

        return;
    }
}
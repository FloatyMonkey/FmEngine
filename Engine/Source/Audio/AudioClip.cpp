// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "AudioClip.h"

#include "../ThirdParty/dr/dr_wav.h"

#include "../Utility/Logger/Log.h"

#include "../Utility/Memory.h"

#include <fstream>

namespace FM
{
	AudioClip::AudioClip()
	{
	}

	AudioClip::~AudioClip()
	{
	}

	bool AudioClip::Load(const char* filename)
	{
		std::ifstream file(filename, std::ios::binary | std::ios::ate);
		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector<char> buffer(size);

		if (!file.read(buffer.data(), size))
		{
			FM_LOG(Error) << "Failed to open audio file: " << filename;
			return false;
		}

		return LoadWav(&buffer[0], size, filename);
	}

	float AudioClip::Length() const
	{
		if (mSampleRate == 0) return 0;
		return (float)mSampleCount / (float)mSampleRate;
	}

	bool AudioClip::LoadWav(const void* data, usize size, const char* filename)
	{
		drwav* decoder = new drwav;

		if (!drwav_init_memory(decoder, data, size, nullptr))
		{
			FM_LOG(Error) << "Failed to decode WAV file: " << filename;
			return false;
		}

		mSampleRate = decoder->sampleRate;
		mSampleCount = decoder->totalPCMFrameCount;
		mChannelCount = decoder->channels;

		mData = std::vector<float>(mSampleCount * mChannelCount);

		drwav_read_pcm_frames_f32(decoder, mSampleCount, &mData[0]);

		drwav_uninit(decoder);
		delete decoder;

		return true;
	}
}

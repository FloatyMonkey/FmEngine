// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../Utility/CoreTypes.h"

#include <vector>

namespace FM
{
	class AudioClip
	{
	public:

		AudioClip();
		~AudioClip();

		bool Load(const char* filename);

		/// Returns the length of the AudioClip in seconds.
		float Length() const;

	private:

		bool LoadWav(const void* data, usize size, const char* filename);

	public: // TODO: Make this private.

		uint32 mSampleRate = 0;
		uint32 mSampleCount = 0;
		uint32 mChannelCount = 0;

		std::vector<float> mData;
	};
}

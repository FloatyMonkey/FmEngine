// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include <vector>

#include "AudioSource.h"

namespace FM
{
	class AudioSource;
	class IAudioDevice;

	class AudioMixer
	{
	public:

		void Mix(std::vector<AudioSource>& sources);

	public: // TODO: Make this private.

		IAudioDevice* mAudioDevice;
	};
}

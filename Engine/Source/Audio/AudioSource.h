// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

namespace FM
{
	class AudioClip;

	class AudioSource
	{
	public:

		bool repeat = false;
		bool isPlaying = false;
		int sampleIndex = 0;
		float volume = 0.0f;

		AudioClip* clip = nullptr;

		void Play()
		{
			sampleIndex = 0;
			isPlaying = true;
		}

		void Pause(bool pause)
		{
			isPlaying = !pause;
		}

		void Stop()
		{
			sampleIndex = 0;
			isPlaying = false;
		}
	};
}

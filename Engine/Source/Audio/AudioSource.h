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

		void Play();
		void Pause(bool pause);
		void Stop();
	};

	inline void AudioSource::Play()
	{
		sampleIndex = 0;
		isPlaying = true;
	}

	inline void AudioSource::Pause(bool pause)
	{
		isPlaying = !pause;
	}

	inline void AudioSource::Stop()
	{
		sampleIndex = 0;
		isPlaying = false;
	}
}

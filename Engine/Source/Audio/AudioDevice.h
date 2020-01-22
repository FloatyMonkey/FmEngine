// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../Utility/CoreTypes.h"

#include <cmath>

namespace FM
{
	static inline float LinearToDecibel(float linear)
	{
		return 20.0f * log10f(linear);
	}

	static inline float DecibelToLinear(float decibel)
	{
		return powf(10.0f, decibel * 0.05f);
	}

	static inline float MsToSamples(float ms, float sampleRate)
	{
		return ms * (sampleRate / 1000.0f);
	}

	static inline float SamplesToMs(float samples, float sampleRate)
	{
		return samples / (sampleRate / 1000.0f);
	}

	class IAudioDevice
	{
	public:

		virtual bool GetPosition(int& byteToLock, int& bytesToWrite) = 0;
		virtual bool SetBuffer(const int16* samples, int byteToLock, int bytesToWrite) = 0;

	public:

		uint32 mChannels = 2;		///< Number of channels.
		uint32 mSampleRate = 44100;	///< Sample rate in Hertz.
		uint32 mBufferSize = 44100;	///< Buffer size in amount of audio frames.
	};
}

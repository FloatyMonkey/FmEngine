// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Mixer.h"

#include "AudioClip.h"
#include "AudioSource.h"
#include "AudioDevice.h"

namespace FM
{
	void AudioMixer::Mix(std::vector<AudioSource>& sources)
	{
		int byteToLock;
		int bytesToWrite;

		mAudioDevice->GetPosition(byteToLock, bytesToWrite);

		if (!bytesToWrite) return;

		// Samples, counts one for L and R together.
		int samplesToWrite = bytesToWrite / 4; // Divided by BytesPerSample.

		std::vector<int16> mixBuffer(samplesToWrite * 2, 0);

		for (AudioSource& source : sources)
		{
			if (!source.isPlaying) continue;

			int offset = source.sampleIndex * 2;

			for (int i = 0; i < samplesToWrite * 2; i += 2)
			{
				if (source.sampleIndex >= source.clip->mSampleCount)
				{
					if (source.repeat)
					{
						source.sampleIndex = 0;
						offset = 0;
					}
					else
					{
						source.isPlaying = false;
						source.sampleIndex = 0;
						break;
					}
				}

				float L = source.clip->mData[offset + i + 0];
				float R = source.clip->mData[offset + i + 1];

				L *= DecibelToLinear(source.volume);
				R *= DecibelToLinear(source.volume);

				mixBuffer[i + 0] += static_cast<int16>(L * 32767.0f);
				mixBuffer[i + 1] += static_cast<int16>(R * 32767.0f);

				source.sampleIndex += 1;
			}
		}

		mAudioDevice->SetBuffer(&mixBuffer[0], byteToLock, bytesToWrite);
	}
}

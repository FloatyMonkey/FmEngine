// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../../Utility/CoreTypes.h"

#include "../../Audio/AudioDevice.h"

struct IDirectSound;
struct IDirectSoundBuffer;

namespace FM
{
	class AudioDevice : public IAudioDevice
	{
	public:

		AudioDevice() = default;

		AudioDevice(void* hwnd);
		~AudioDevice();

	public:

		bool Initialize(void* hwnd);

		bool GetPosition(int& byteToLock, int& bytesToWrite);
		bool SetBuffer(const int16* samples, int byteToLock, int bytesToWrite);

	private:

		IDirectSound* mDirectSound;
		IDirectSoundBuffer* mPrimaryBuffer;
		IDirectSoundBuffer* mSecondaryBuffer;

		uint32 mSampleIndex = 0;
		uint32 mBytesPerSample = 0;
		uint32 mOwnBufferSize = 0;
	};
}

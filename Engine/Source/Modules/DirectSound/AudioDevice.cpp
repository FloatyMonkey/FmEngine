// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "AudioDevice.h"

#include <dsound.h>
#include <Windows.h>

#pragma comment(lib, "dsound.lib")

#include "../../Utility/Logger/Log.h"

namespace FM
{
	template<typename T>
	void SafeRelease(T*& ptr)
	{
		if (ptr) { ptr->Release(); ptr = nullptr; }
	}

	AudioDevice::AudioDevice(void* hwnd)
	{
		Initialize(hwnd);
	}

	AudioDevice::~AudioDevice()
	{
		SafeRelease(mSecondaryBuffer);
		SafeRelease(mPrimaryBuffer);
		SafeRelease(mDirectSound);
	}

	bool AudioDevice::Initialize(void* hwnd)
	{
		mBytesPerSample = sizeof(int16) * mChannels;
		mOwnBufferSize = mBytesPerSample * mBufferSize;

		HRESULT hr;

		hr = DirectSoundCreate(0, &mDirectSound, nullptr);

		if (FAILED(hr))
		{
			FM_LOG(Error) << "Failed to create DirectSound device";
			return false;
		}

		hr = mDirectSound->SetCooperativeLevel((HWND)hwnd, DSSCL_PRIORITY);

		if (FAILED(hr))
		{
			FM_LOG(Error) << "Failed to set cooperative level for DirectSound";
			return false;
		}

		DSBUFFERDESC primaryBufferDesc = {};
		primaryBufferDesc.dwSize = sizeof(DSBUFFERDESC);
		primaryBufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER;
		primaryBufferDesc.dwBufferBytes = 0;
		primaryBufferDesc.dwReserved = 0;
		primaryBufferDesc.lpwfxFormat = nullptr;
		primaryBufferDesc.guid3DAlgorithm = GUID_NULL;

		hr = mDirectSound->CreateSoundBuffer(&primaryBufferDesc, &mPrimaryBuffer, nullptr);

		if (FAILED(hr))
		{
			FM_LOG(Error) << "Failed to create primary DirectSound buffer";
			return false;
		}

		WAVEFORMATEX waveFormat = {};
		waveFormat.wFormatTag = WAVE_FORMAT_PCM;
		waveFormat.nChannels = mChannels;
		waveFormat.nSamplesPerSec = mSampleRate;
		waveFormat.wBitsPerSample = sizeof(int16) * 8;
		waveFormat.nBlockAlign = (waveFormat.nChannels * waveFormat.wBitsPerSample) / 8;
		waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
		waveFormat.cbSize = 0;

		hr = mPrimaryBuffer->SetFormat(&waveFormat);

		if (FAILED(hr))
		{
			FM_LOG(Error) << "Failed to set wave format on primary DirectSound buffer";
			return false;
		}

		DSBUFFERDESC secondaryBufferDesc = {};
		secondaryBufferDesc.dwSize = sizeof(DSBUFFERDESC);
		secondaryBufferDesc.dwFlags = 0;
		secondaryBufferDesc.dwBufferBytes = mOwnBufferSize;
		secondaryBufferDesc.dwReserved = 0;
		secondaryBufferDesc.lpwfxFormat = &waveFormat;
		secondaryBufferDesc.guid3DAlgorithm = GUID_NULL;

		hr = mDirectSound->CreateSoundBuffer(&secondaryBufferDesc, &mSecondaryBuffer, nullptr);

		if (FAILED(hr))
		{
			FM_LOG(Error) << "Failed to create secondary DirectSound buffer";
			return false;
		}

		return true;
	}

	bool AudioDevice::GetPosition(int& byteToLock, int& bytesToWrite)
	{
		HRESULT hr;

		DWORD playCursor;
		DWORD writeCursor;

		hr = mSecondaryBuffer->GetCurrentPosition(&playCursor, &writeCursor);
		if (FAILED(hr))
		{
			FM_LOG(Error) << "Failed to get current secondary DirectSound buffer position";
			return false;
		}

		int latencySamples = 3200;

		DWORD lock = (mSampleIndex * mBytesPerSample) % mOwnBufferSize;
		DWORD targetCursor = (writeCursor + latencySamples * mBytesPerSample) % mOwnBufferSize;

		DWORD write = 0;

		if (lock > targetCursor)
		{
			write = (mOwnBufferSize - lock) + targetCursor;
		}
		else
		{
			write = targetCursor - lock;
		}

		byteToLock = lock;
		bytesToWrite = write;

		return true;
	}

	bool AudioDevice::SetBuffer(const int16* samples, int byteToLock, int bytesToWrite)
	{
		HRESULT hr;

		void* region1;
		DWORD size1;
		void* region2;
		DWORD size2;

		hr = mSecondaryBuffer->Lock(byteToLock, bytesToWrite, &region1, &size1, &region2, &size2, 0);

		// TODO: Commented out because hr fails the first times. Investigate this!

		//if (FAILED(hr))
		//{
		//	OL_LOG(Error) << "Failed to lock secondary DirectSound buffer";
		//	return false;
		//}

		int16* sample1 = (int16*)region1;
		memcpy(sample1, samples, size1);

		DWORD sample1_count = size1 / mBytesPerSample;
		samples += sample1_count * 2;
		mSampleIndex += sample1_count;

		int16* sample2 = (int16*)region2;
		memcpy(sample2, samples, size2);

		DWORD sample2_count = size2 / mBytesPerSample;
		samples += sample2_count * 2;
		mSampleIndex += sample2_count;

		hr = mSecondaryBuffer->Unlock(region1, size1, region2, size2);
		if (FAILED(hr))
		{
			FM_LOG(Error) << "Failed to unlock secondary DirectSound buffer";
			return false;
		}

		// TODO: Ugly hack!
		static bool first = false;

		if (!first)
		{
			hr = mSecondaryBuffer->Play(0, 0, DSBPLAY_LOOPING);

			if (FAILED(hr))
			{
				FM_LOG(Error) << "Failed to play secondary DirectSound buffer";
				return false;
			}

			first = true;
		}

		return true;
	}
}

// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Time.h"

#include <ctime>

namespace FM
{
	Time GTime;

	Time::Time()
	{
		mStartTime = clock();
	}

	float Time::GetTime() const
	{
		return mTime;
	}

	float Time::GetDeltaTime() const
	{
		return mDeltaTime;
	}

	int Time::GetFrameCount() const
	{
		return mFrameCount;
	}

	void Time::Update()
	{
		uint64 currentTime = clock();

		mTime = (currentTime - mStartTime) / (float)CLOCKS_PER_SEC;
		mDeltaTime = (currentTime - mLastTime) / (float)CLOCKS_PER_SEC;

		mLastTime = currentTime;

		mFrameCount += 1;
	}
}

// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "CoreTypes.h"

namespace FM
{
	/// The interface to get time information.

	class Time
	{
	public:

		Time();

		/// Returns the time (in seconds) since the start of the application.
		/// Gets updated once at the start of every new frame.
		float GetTime() const;

		/// Returns the time in seconds it took to complete the last frame.
		/// Use this value to make your application frame rate independent.
		/// When you multiply with GetDeltaTime() you essentially express: "I want to move this object 1 meter per second instead of 1 meter per frame".
		float GetDeltaTime() const;

		/// Returns the total number of frames that have passed.
		/// The first frame has an index of 0.
		int GetFrameCount() const;

	private:

		float mTime = 0.0f;
		float mDeltaTime = 0.0f;
		int mFrameCount = -1;

		uint64 mStartTime = 0;
		uint64 mLastTime = 0;

	public:

		/// Should be called once at the start of every new frame by the implementation.
		void Update();
	};

	/// The global Time object.
	extern Time GTime;
}

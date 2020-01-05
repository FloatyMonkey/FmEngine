// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../CoreTypes.h"

namespace FM
{
	/// Pseudo random number generator.
	/// This generator is an implementation of the Xorshift128 algorithm.
	/// It has a period of (2^128 - 1) and is suitable for high performance requirements.

	class Random
	{
	public:
		
		/// Initializes a new generator using the specified seed.
		Random(uint32 seed = 1);

		/// Changes the seed of the generator to the specified value.
		void SetSeed(uint32 seed);

		/// Returns a random value in the [0, uint32 MAX] range.
		uint32 GetValue();

		/// Returns a random value in the [0, 1] range.
		float GetUNorm();

		/// Returns a random value in the [-1, 1] range.
		float GetSNorm();

		/// Returns a random value in the [min, max] range.
		/// The minimum may be larger than the maximum.
		float GetRange(float min, float max);

	private:

		uint32 mX;
		uint32 mY;
		uint32 mZ;
		uint32 mW;
	};
}

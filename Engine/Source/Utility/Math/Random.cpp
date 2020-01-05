// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Random.h"

namespace FM
{
	Random::Random(uint32 seed)
	{
		// TODO: We should set the seed to a random number (e.g. time when constructing this class).
		SetSeed(seed);
	}

	void Random::SetSeed(uint32 seed)
	{
		// At least one of the seeds should be non-zero.
		// The numbers below are chosen randomly.

		mX = seed;
		mY = seed * 123456789 + 1;
		mZ = seed * 362436069 + 1;
		mW = seed * 521288629 + 1;
	}

	uint32 Random::GetValue()
	{
		uint32 t = (mX ^ (mX << 11));

		mX = mY;
		mY = mZ;
		mZ = mW;

		return (mW = mW ^ (mW >> 19) ^ (t ^ (t >> 8)));
	}

	float Random::GetUNorm()
	{
		return float(GetValue() & 0x7FFFFF) / 8388607.0f;
	}

	float Random::GetSNorm()
	{
		return GetUNorm() * 2.0f - 1.0f;
	}

	float Random::GetRange(float min, float max)
	{
		float range = max - min;
		return min + (GetUNorm() * range);
	}
}

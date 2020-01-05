// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "CoreTypes.h"

namespace FM
{
	// TODO: These are not efficient in terms of memory allocation.
	// TODO: Maybe implement a templated version of these functions.

	inline uint8 SwapEndianness(uint8 x)
	{
		return x;
	}

	inline uint16 SwapEndianness(uint16 x)
	{
		uint16 b0, b1;

		b0 = (x & 0x00FF) << 8;
		b1 = (x & 0xFF00) >> 8;

		return b0 | b1;
	}

	inline uint32 SwapEndianness(uint32 x)
	{
		uint32 b0, b1, b2, b3;

		b0 = (x & 0x000000FF) << 24;
		b1 = (x & 0x0000FF00) << 8;
		b2 = (x & 0x00FF0000) >> 8;
		b3 = (x & 0xFF000000) >> 24;

		return b0 | b1 | b2 | b3;
	}

	inline uint64 SwapEndianness(uint64 x)
	{
		uint64 b0, b1, b2, b3, b4, b5, b6, b7;

		b0 = (x & 0x00000000000000FF) << 56;
		b1 = (x & 0x000000000000FF00) << 40;
		b2 = (x & 0x0000000000FF0000) << 24;
		b3 = (x & 0x00000000FF000000) << 8;
		b4 = (x & 0x000000FF00000000) >> 8;
		b5 = (x & 0x0000FF0000000000) >> 24;
		b6 = (x & 0x00FF000000000000) >> 40;
		b7 = (x & 0xFF00000000000000) >> 56;

		return b0 | b1 | b2 | b3 | b4 | b5 | b6 | b7;
	}
}

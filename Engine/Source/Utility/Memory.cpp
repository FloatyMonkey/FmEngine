// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Memory.h"

#include <cstring>

namespace FM
{
	int Memory::Memcmp(const void* lhs, const void* rhs, usize size)
	{
		return std::memcmp(lhs, rhs, size);
	}

	void* Memory::Memset(void* dst, uint8 value, usize size)
	{
		return std::memset(dst, value, size);
	}

	void* Memory::Memcpy(void* dst, const void* src, usize size)
	{
		return std::memcpy(dst, src, size);
	}
}

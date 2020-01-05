// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "CoreTypes.h"

namespace FM
{
	class Memory
	{
	public:

		static int Memcmp(const void* lhs, const void* rhs, usize size);

		static void* Memset(void* dst, uint8 value, usize size);

		static void* Memcpy(void* dst, const void* src, usize size);
	};
}

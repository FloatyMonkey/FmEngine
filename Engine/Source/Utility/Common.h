// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "CoreTypes.h"

namespace FM
{
	/// Returns the element count of an array whose size is known at compile time.
	template <typename T, usize N>
	constexpr usize CountOf(const T(&)[N])
	{
		return N;
	}

	/// Returns the offset in bytes from an object to a member pointer.
	template <typename T, typename M>
	constexpr usize OffsetOf(M T::* member)
	{
		return reinterpret_cast<usize>(&(((T*)0)->*member));
	};
}

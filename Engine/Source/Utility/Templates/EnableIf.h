// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

namespace FM
{
	// Enable If

	template<bool B, typename T = void>
	struct TEnableIf {};

	template <typename T>
	struct TEnableIf<true, T> { typedef T Type; };

	// Disable If

	template<bool B, typename T = void>
	struct TDisableIf {};

	template <typename T>
	struct TDisableIf<false, T> { typedef T Type; };
}

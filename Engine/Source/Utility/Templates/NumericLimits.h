// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../CoreTypes.h"

namespace FM
{
	template <typename T>
	struct TNumericLimits;

	template <>
	struct TNumericLimits<int8>
	{
		using Type = int8;

		static constexpr Type Min = 0x80;
		static constexpr Type Max = 0x7f;
		static constexpr Type Lowest = Min;
	};

	template <>
	struct TNumericLimits<int16>
	{
		using Type = int16;

		static constexpr Type Min = 0x8000;
		static constexpr Type Max = 0x7fff;
		static constexpr Type Lowest = Min;
	};

	template <>
	struct TNumericLimits<int32>
	{
		using Type = int32;

		static constexpr Type Min = 0x80000000;
		static constexpr Type Max = 0x7fffffff;
		static constexpr Type Lowest = Min;
	};

	template <>
	struct TNumericLimits<int64>
	{
		using Type = int64;

		static constexpr Type Min = 0x8000000000000000;
		static constexpr Type Max = 0x7fffffffffffffff;
		static constexpr Type Lowest = Min;
	};

	template <>
	struct TNumericLimits<uint8>
	{
		using Type = uint8;

		static constexpr Type Min = 0x00;
		static constexpr Type Max = 0xff;
		static constexpr Type Lowest = Min;
	};

	template <>
	struct TNumericLimits<uint16>
	{
		using Type = uint16;

		static constexpr Type Min = 0x0000;
		static constexpr Type Max = 0xffff;
		static constexpr Type Lowest = Min;
	};

	template <>
	struct TNumericLimits<uint32>
	{
		using Type = uint32;

		static constexpr Type Min = 0x00000000;
		static constexpr Type Max = 0xffffffff;
		static constexpr Type Lowest = Min;
	};

	template <>
	struct TNumericLimits<uint64>
	{
		using Type = uint64;

		static constexpr Type Min = 0x0000000000000000;
		static constexpr Type Max = 0xffffffffffffffff;
		static constexpr Type Lowest = Min;
	};

	template <>
	struct TNumericLimits<float>
	{
		using Type = float;

		static constexpr Type Min = 1.175494351e-38f;
		static constexpr Type Max = 3.402823466e+38f;
		static constexpr Type Lowest = -Max;
	};

	template <>
	struct TNumericLimits<double>
	{
		using Type = double;

		static constexpr Type Min = 2.2250738585072014e-308;
		static constexpr Type Max = 1.7976931348623158e+308;
		static constexpr Type Lowest = -Max;
	};
}

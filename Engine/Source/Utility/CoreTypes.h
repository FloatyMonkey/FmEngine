// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

namespace FM
{
	// Signed base types.

	using int8  = signed char;		///< 8-bit signed integer.
	using int16 = signed short int;	///< 16-bit signed integer.
	using int32 = signed int;		///< 32-bit signed integer.
	using int64 = signed long long;	///< 64-bit signed integer.

	// Unsigned base types.

	using uint8  = unsigned char;		///< 8-bit unsigned integer.
	using uint16 = unsigned short int;	///< 16-bit unsigned integer.
	using uint32 = unsigned int;		///< 32-bit unsigned integer.
	using uint64 = unsigned long long;	///< 64-bit unsigned integer.

	// Special types.

	using uint = uint32;	///< Unsigned integer shorthand.
	using usize = uint64;	///< Unsigned integer with the same size as a pointer.

	// Check the size at compile time.

	static_assert(sizeof(int8) ==  1, "Size of int8 is incorrect.");
	static_assert(sizeof(int16) == 2, "Size of int16 is incorrect.");
	static_assert(sizeof(int32) == 4, "Size of int32 is incorrect.");
	static_assert(sizeof(int64) == 8, "Size of int64 is incorrect.");

	static_assert(sizeof(uint8) ==  1, "Size of uint8 is incorrect.");
	static_assert(sizeof(uint16) == 2, "Size of uint16 is incorrect.");
	static_assert(sizeof(uint32) == 4, "Size of uint32 is incorrect.");
	static_assert(sizeof(uint64) == 8, "Size of uint64 is incorrect.");

	static_assert(sizeof(usize) == sizeof(void*), "Size of usize is incorrect.");
}

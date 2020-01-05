// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

namespace FM
{
	// Signed base types.

	typedef	signed char			int8;	///< 8-bit signed integer.
	typedef signed short int	int16;	///< 16-bit signed integer.
	typedef signed int	 		int32;	///< 32-bit signed integer.
	typedef signed long long	int64;	///< 64-bit signed integer.

	// Unsigned base types.

	typedef unsigned char 		uint8;	///< 8-bit unsigned integer.
	typedef unsigned short int	uint16;	///< 16-bit unsigned integer.
	typedef unsigned int		uint32;	///< 32-bit unsigned integer.
	typedef unsigned long long	uint64;	///< 64-bit unsigned integer.

	// Special types.

	typedef uint64 usize; ///< Unsigned integer with the same size as a pointer.

	// Check the size at compile time.

	static_assert(sizeof(int8) == 1, "Size of int8 is incorrect.");
	static_assert(sizeof(int16) == 2, "Size of int16 is incorrect.");
	static_assert(sizeof(int32) == 4, "Size of int32 is incorrect.");
	static_assert(sizeof(int64) == 8, "Size of int64 is incorrect.");

	static_assert(sizeof(uint8) == 1, "Size of uint8 is incorrect.");
	static_assert(sizeof(uint16) == 2, "Size of uint16 is incorrect.");
	static_assert(sizeof(uint32) == 4, "Size of uint32 is incorrect.");
	static_assert(sizeof(uint64) == 8, "Size of uint64 is incorrect.");

	static_assert(sizeof(usize) == sizeof(void*), "Size of usize is incorrect.");
}

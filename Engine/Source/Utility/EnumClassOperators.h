// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

/// Generates bitwise operators for scoped enums.
#define ENUM_CLASS_OPERATORS(Enum) \
\
static inline bool operator! (Enum e) { return !(__underlying_type(Enum))e; } \
static inline Enum operator~ (Enum e) { return (Enum)~(__underlying_type(Enum))(e); } \
\
static inline Enum operator| (Enum lhs, Enum rhs) { return (Enum)((__underlying_type(Enum))(lhs) | (__underlying_type(Enum))(rhs)); } \
static inline Enum operator& (Enum lhs, Enum rhs) { return (Enum)((__underlying_type(Enum))(lhs) & (__underlying_type(Enum))(rhs)); } \
static inline Enum operator^ (Enum lhs, Enum rhs) { return (Enum)((__underlying_type(Enum))(lhs) ^ (__underlying_type(Enum))(rhs)); } \
\
static inline Enum& operator|= (Enum& lhs, Enum rhs) { return lhs = (lhs | rhs); } \
static inline Enum& operator&= (Enum& lhs, Enum rhs) { return lhs = (lhs & rhs); } \
static inline Enum& operator^= (Enum& lhs, Enum rhs) { return lhs = (lhs ^ rhs); } \

namespace FM
{
	template<typename T>
	static inline bool All(T flags, T contains)
	{
		return (((__underlying_type(T))flags) & (__underlying_type(T))contains) == ((__underlying_type(T))contains);
	}

	template<typename T>
	static inline bool Any(T flags, T contains)
	{
		return (((__underlying_type(T))flags) & (__underlying_type(T))contains) != 0;
	}
}

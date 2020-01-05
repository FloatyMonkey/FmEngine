// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../CoreTypes.h"

namespace FM
{
	template <typename T>
	struct TIsEnum
	{
		static constexpr bool Value = __is_enum(T);
	};

	template <typename T> inline constexpr bool TIsEnumV = TIsEnum<T>::Value;

	template <typename T>
	struct TUnderlyingType
	{
		typedef __underlying_type(T) Type;
	};

	template <typename T> using TUnderlyingTypeT = typename TUnderlyingType<T>::Type;

	// Integral Constant

	template <typename T, T v>
	struct TIntegralConstant
	{
		static constexpr T Value = v;

		typedef T ValueType;
		typedef TIntegralConstant Type;

		constexpr operator ValueType() const noexcept { return Value; }
		constexpr ValueType operator()() const noexcept { return Value; }
	};

	typedef TIntegralConstant<bool, true> TrueType;
	typedef TIntegralConstant<bool, false> FalseType;

	// Remove Const

	template <typename T>          struct TRemoveConst             { typedef T Type;    };
	template <typename T>          struct TRemoveConst<const T>    { typedef T Type;    };
	template <typename T>          struct TRemoveConst<const T[]>  { typedef T Type[];  };
	template <typename T, usize N> struct TRemoveConst<const T[N]> { typedef T Type[N]; };

	template <typename T> using TRemoveConstT = typename TRemoveConst<T>::Type;

	// Remove Volatile

	template <typename T>          struct TRemoveVolatile                { typedef T Type;    };
	template <typename T>          struct TRemoveVolatile<volatile T>    { typedef T Type;    };
	template <typename T>          struct TRemoveVolatile<volatile T[]>  { typedef T Type[];  };
	template <typename T, usize N> struct TRemoveVolatile<volatile T[N]> { typedef T Type[N]; };
	
	template <typename T> using TRemoveVolatileT = typename TRemoveVolatile<T>::Type;

	// Remove CV

	template <typename T> struct TRemoveCV { typedef typename TRemoveVolatile<typename TRemoveConst<T>::Type>::Type Type; };

	template <typename T> using TRemoveCvT = typename TRemoveCV<T>::Type;
}

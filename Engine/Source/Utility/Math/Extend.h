// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../CoreTypes.h"

#include "Vector.h"

namespace FM
{
	template <typename T, uint N>
	struct TExtend
	{
		TVector<T, N> position;
		TVector<T, N> size;

		constexpr TExtend() = default;
		constexpr TExtend(const TVector<T, N>& position, const TVector<T, N>& size) : position(position), size(size) {}
	};

	template <typename T>
	struct TExtend<T, 2>
	{
		union {
			TVector<T, 2> position;
			struct { T x, y; };
		};

		union {
			TVector<T, 2> size;
			struct { T w, h; };
		};

		constexpr TExtend() = default;
		constexpr TExtend(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) {}
		constexpr TExtend(const TVector<T, 2>& position, const TVector<T, 2>& size) : position(position), size(size) {}
	};

	template <typename T>
	struct TExtend<T, 3>
	{
		union {
			TVector<T, 3> position;
			struct { T x, y, z; };
		};

		union {
			TVector<T, 3> size;
			struct { T w, h, d; };
		};

		constexpr TExtend() = default;
		constexpr TExtend(T x, T y, T z, T w, T h, T d) : x(x), y(y), z(z), w(w), h(h), d(d) {}
		constexpr TExtend(const TVector<T, 3>& position, const TVector<T, 3>& size) : position(position), size(size) {}
	};

	template <typename T> using TExtend2 = TExtend<T, 2>;
	template <typename T> using TExtend3 = TExtend<T, 3>;

	using Extend2 = TExtend2<float>;
	using Extend3 = TExtend3<float>;

	using Extend2I = TExtend2<int>;
	using Extend3I = TExtend3<int>;
}

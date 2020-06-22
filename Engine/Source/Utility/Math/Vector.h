// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../CoreTypes.h"
#include "Functions.h"

namespace FM
{
	template <typename T, uint N>
	struct TVectorStorage {
		T data[N]{ 0 };
	};

	template <typename T>
	struct TVectorStorage<T, 2> {
		union {
			T data[2]{ 0 };
			struct { T x, y; };
		};
	};

	template <typename T>
	struct TVectorStorage<T, 3> {
		union {
			T data[3]{ 0 };
			struct { T x, y, z; };
		};
	};

	template <typename T>
	struct TVectorStorage<T, 4> {
		union {
			T data[4]{ 0 };
			struct { T x, y, z, w; };
		};
	};

	/// N dimensional Vector.

	template <typename T, uint N>
	struct TVector : public TVectorStorage<T, N>
	{
		using TVectorStorage<T, N>::data;

		constexpr TVector() = default;

		constexpr TVector(T all) {
			for (int i = 0; i < N; i++) data[i] = all;
		}

		template <typename ...Ts>
		constexpr TVector(const T& t, const Ts&... ts) : TVectorStorage<T, N> {t, ts...} {
			static_assert(sizeof...(ts) + 1 == N);
		}

		constexpr T& operator[] (usize i) { return data[i]; }
		constexpr const T& operator[] (usize i) const { return data[i]; }

		constexpr usize Size() const { return N; }
	};

	// Operators

	template <typename T, uint N>
	inline constexpr TVector<T, N> operator- (const TVector<T, N>& lhs)
	{
		TVector<T, N> r;
		for (int i = 0; i < N; i++) r[i] = -lhs[i];
		return r;
	}

	// Arithmetic Operators

	template <typename T, uint N>
	inline constexpr TVector<T, N> operator+ (const TVector<T, N>& lhs, const TVector<T, N>& rhs)
	{
		TVector<T, N> r;
		for (int i = 0; i < N; i++) r[i] = lhs[i] + rhs[i];
		return r;
	}

	template <typename T, uint N>
	inline constexpr TVector<T, N> operator- (const TVector<T, N>& lhs, const TVector<T, N>& rhs)
	{
		TVector<T, N> r;
		for (int i = 0; i < N; i++) r[i] = lhs[i] - rhs[i];
		return r;
	}

	template <typename T, uint N>
	inline constexpr TVector<T, N> operator* (const TVector<T, N>& lhs, const T& rhs)
	{
		TVector<T, N> r;
		for (int i = 0; i < N; i++) r[i] = lhs[i] * rhs;
		return r;
	}

	template <typename T, uint N>
	inline constexpr TVector<T, N> operator/ (const TVector<T, N>& lhs, const T& rhs)
	{
		TVector<T, N> r;
		for (int i = 0; i < N; i++) r[i] = lhs[i] / rhs;
		return r;
	}
	
	// Assignment operators

	template <typename T, uint N>
	inline constexpr TVector<T, N> operator+= (TVector<T, N>& lhs, const TVector<T, N>& rhs) {
		return lhs = lhs + rhs;
	}

	template <typename T, uint N>
	inline constexpr TVector<T, N> operator-= (TVector<T, N>& lhs, const TVector<T, N>& rhs) {
		return lhs = lhs - rhs;
	}

	template <typename T, uint N>
	inline constexpr TVector<T, N> operator*= (TVector<T, N>& lhs, const T& rhs) {
		return lhs = lhs * rhs;
	}

	template <typename T, uint N>
	inline constexpr TVector<T, N> operator/= (TVector<T, N>& lhs, const T& rhs) {
		return lhs = lhs / rhs;
	}

	// Relational operators

	template <typename T, uint N>
	inline constexpr TVector<T, N> operator== (const TVector<T, N>& lhs, const TVector<T, N>& rhs)
	{
		for (int i = 0; i < N; i++) if (lhs[i] != rhs[i]) return false;
		return true;
	}

	// Type aliases

	template <typename T> using TVector2 = TVector<T, 2>;
	template <typename T> using TVector3 = TVector<T, 3>;
	template <typename T> using TVector4 = TVector<T, 4>;

	using Vector2 = TVector2<float>;
	using Vector3 = TVector3<float>;
	using Vector4 = TVector4<float>;

	using Vector2I = TVector2<int>;
	using Vector3I = TVector3<int>;
	using Vector4I = TVector4<int>;

	// Calculations

	namespace Math
	{
		// Cross Product

		template <typename T>
		inline constexpr T Cross(const TVector<T, 2>& lhs, const TVector<T, 2>& rhs)
		{
			return lhs.x * rhs.y - lhs.y * rhs.x;
		}

		template <typename T>
		inline constexpr TVector<T, 3> Cross(const TVector<T, 3>& lhs, const TVector<T, 3>& rhs)
		{
			return TVector<T, 3>
			(
				lhs.y * rhs.z - lhs.z * rhs.y,
				lhs.z * rhs.x - lhs.x * rhs.z,
				lhs.x * rhs.y - lhs.y * rhs.x
			);
		}

		// Dot Product

		template <typename T>
		inline constexpr auto Dot(const T& lhs, const T& rhs) -> decltype(lhs[0] + rhs[0])
		{
			decltype(lhs[0] + rhs[0]) r(0);
			for (int i = 0; i < lhs.Size(); i++) r += lhs[i] * rhs[i];
			return r;
		}

		// Length

		template <typename T>
		inline constexpr auto LengthSquared(const T& x)
		{
			return Dot(x, x);
		}

		template <typename T>
		inline auto Length(const T& x)
		{
			return Sqrt(LengthSquared(x));
		}

		// Distance

		template <typename T>
		inline constexpr auto DistanceSquared(const T& lhs, const T& rhs)
		{
			return LengthSquared(lhs - rhs);
		}

		template <typename T>
		inline auto Distance(const T& lhs, const T& rhs)
		{
			return Length(lhs - rhs);
		}

		// Normalize

		template <typename T>
		inline constexpr auto Normalize(const T& x)
		{
			return x / Length(x);
		}
	}
}

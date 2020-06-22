// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "Vector.h"

namespace FM
{
	/// Quaternion used for 3D rotations.

	template <typename T>
	struct TQuaternion
	{
		union {
			T data[4];
			struct { T x, y, z, w; };
		};

		TQuaternion()
			: x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}

		TQuaternion(T x, T y, T z, T w)
			: x(x), y(y), z(z), w(w) {}

		TQuaternion(const TVector3<T>& v, T w = T(0))
			: x(v.x), y(v.y), z(v.z), w(w) {}

		static const TQuaternion Zero;
		static const TQuaternion Identity;

		constexpr T& operator[] (usize i) { return data[i]; }
		constexpr const T& operator[] (usize i) const { return data[i]; }
	};

	// Standard quaternions

	template <typename T>
	const TQuaternion<T> TQuaternion<T>::Zero(T(0), T(0), T(0), T(0));

	template <typename T>
	const TQuaternion<T> TQuaternion<T>::Identity(T(0), T(0), T(0), T(1));

	// Operators

	template <typename T>
	inline constexpr TQuaternion<T> operator- (const TQuaternion<T>& lhs)
	{
		return TQuaternion<T>(-lhs.x, -lhs.y, -lhs.z, -lhs.w);
	}

	// Arithmetic operators

	template <typename T>
	inline constexpr TQuaternion<T> operator+ (const TQuaternion<T>& lhs, const TQuaternion<T>& rhs)
	{
		return TQuaternion<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
	}

	template <typename T>
	inline constexpr TQuaternion<T> operator- (const TQuaternion<T>& lhs, const TQuaternion<T>& rhs)
	{
		return TQuaternion<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
	}

	template <typename T>
	inline constexpr TQuaternion<T> operator* (const TQuaternion<T>& lhs, const TQuaternion<T>& rhs)
	{
		return TQuaternion<T>
		(
			lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
			lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x
		);
	}

	template <typename T>
	inline constexpr TQuaternion<T> operator* (const TQuaternion<T>& lhs, T rhs)
	{
		return TQuaternion<T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
	}

	template <typename T>
	inline constexpr TQuaternion<T> operator/ (const TQuaternion<T>& lhs, T rhs)
	{
		return TQuaternion<T>(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs);
	}

	// Assignment operators

	template <typename T>
	inline constexpr TQuaternion<T>& operator+= (TQuaternion<T>& lhs, const TQuaternion<T>& rhs) {
		return lhs = lhs + rhs;
	}

	template <typename T>
	inline constexpr TQuaternion<T>& operator-= (TQuaternion<T>& lhs, const TQuaternion<T>& rhs) {
		return lhs = lhs - rhs;
	}

	template <typename T>
	inline constexpr TQuaternion<T>& operator*= (TQuaternion<T>& lhs, const TQuaternion<T>& rhs) {
		return lhs = lhs * rhs;
	}

	template <typename T>
	inline constexpr TQuaternion<T>& operator*= (TQuaternion<T>& lhs, T rhs) {
		return lhs = lhs * rhs;
	}

	template <typename T>
	inline constexpr TQuaternion<T>& operator/= (TQuaternion<T>& lhs, T rhs) {
		return lhs = lhs / rhs;
	}

	// Relational operators

	template <typename T>
	inline constexpr bool operator== (const TQuaternion<T>& lhs, const TQuaternion<T>& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
	}

	// Type aliases

	using Quaternion = TQuaternion<float>;

	// Calculations

	namespace Math
	{
		template <typename T>
		T Dot(const TQuaternion<T>& lhs, const TQuaternion<T>& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
		}

		template <typename T>
		TQuaternion<T> Inverse(const TQuaternion<T>& q)
		{
			return TQuaternion<T>(-q.x, -q.y, -q.z, q.w);
		}
	}
}

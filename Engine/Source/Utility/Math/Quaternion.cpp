// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Quaternion.h"

#include "Functions.h"
#include "Radian.h"
#include "Vector3.h"
#include "Matrix4.h"

namespace FM
{
	// Constructors

	template <typename T>
	TQuaternion<T>::TQuaternion()
		: x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}

	template <typename T>
	TQuaternion<T>::TQuaternion(T x, T y, T z, T w)
		: x(x), y(y), z(z), w(w) {}

	// Predefined quaternions

	template <typename T>
	const TQuaternion<T> TQuaternion<T>::Zero(T(0), T(0), T(0), T(0));

	template <typename T>
	const TQuaternion<T> TQuaternion<T>::Identity(T(1), T(0), T(0), T(0));

	// Calculations

	template <typename T>
	T TQuaternion<T>::Length() const
	{
		return Math::Sqrt(x * x + y * y + z * z + w * w);
	}

	template <typename T>
	TQuaternion<T> TQuaternion<T>::Normalize() const
	{
		T length = Math::Sqrt(x * x + y * y + z * z + w * w);
		return TQuaternion(x / length, y / length, z / length, w / length);
	}

	template <typename T>
	TQuaternion<T> TQuaternion<T>::Conjugate() const
	{
		return TQuaternion(-x, -y, -z, w);
	}

	template <typename T>
	T TQuaternion<T>::Dot(const TQuaternion& lhs, const TQuaternion& rhs)
	{
		return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w);
	}

	template <typename T>
	TQuaternion<T> TQuaternion<T>::RotationMatrix(const TMatrix4<T>& matrix)
	{
		T tr = matrix(1, 1) + matrix(2, 2) + matrix(3, 3);

		if (tr > T(0))
		{
			T s = Math::Sqrt(tr + T(1));
			T w = s / T(2);
			s = T(0.5) / s;

			return TQuaternion
			(
				(matrix(1, 2) - matrix(2, 1)) * s,
				(matrix(2, 0) - matrix(0, 2)) * s,
				(matrix(0, 1) - matrix(1, 0)) * s,
				w
			);
		}

		if ((matrix(0, 0) >= matrix(1, 1)) && (matrix(0, 0) >= matrix(2, 2)))
		{
			T s = Math::Sqrt(T(1) + matrix(0, 0) - matrix(1, 1) - matrix(2, 2));
			T x = s / T(2);
			s = T(0.5) / s;

			return TQuaternion
			(
				x,
				(matrix(0, 1) + matrix(1, 0)) * s,
				(matrix(0, 2) + matrix(2, 0)) * s,
				(matrix(1, 2) - matrix(2, 1)) * s
			);
		}

		if (matrix(1, 1) > matrix(2, 2))
		{
			T s = Math::Sqrt(T(1) + matrix(1, 1) - matrix(0, 0) - matrix(2, 2));
			T y = s / T(2);
			s = T(0.5) / s;

			return TQuaternion
			(
				(matrix(1, 0) + matrix(0, 1)) * s,
				y,
				(matrix(2, 1) + matrix(1, 2)) * s,
				(matrix(2, 0) - matrix(0, 2)) * s
			);
		}

		T s = Math::Sqrt(T(1) + matrix(2, 2) - matrix(0, 0) - matrix(1, 1));
		T z = s / T(2);
		s = T(0.5) / s;

		return TQuaternion
		(
			(matrix(2, 0) + matrix(0, 2)) * s,
			(matrix(2, 1) + matrix(1, 2)) * s,
			z,
			(matrix(0, 1) - matrix(1, 0)) * s
		);
	}

	template <typename T>
	TQuaternion<T> TQuaternion<T>::AxisAngle(const TVector3<T>& axis, const TRadian<T>& angle)
	{
		TRadian<T> half = angle / T(2);
		T sinX = Math::Sin(half);

		return TQuaternion
		(
			axis.x * sinX,
			axis.y * sinX,
			axis.z * sinX,
			Math::Cos(half)
		);
	}

	template <typename T>
	TQuaternion<T> TQuaternion<T>::YawPitchRoll(const TRadian<T>& yaw, const TRadian<T>& pitch, const TRadian<T>& roll)
	{
		TRadian<T> y = yaw / T(2);
		TRadian<T> p = pitch / T(2);
		TRadian<T> r = roll / T(2);

		T sy = Math::Sin(y);
		T cy = Math::Cos(y);
		T sp = Math::Sin(p);
		T cp = Math::Cos(p);
		T sr = Math::Sin(r);
		T cr = Math::Cos(r);

		return TQuaternion
		(
			cy * sp * cr + sy * cp * sr,
			sy * cp * cr - cy * sp * sr,
			cy * cp * sr - sy * sp * cr,
			cy * cp * cr + sy * sp * sr
		);
	}

	// Operators

	template <typename T>
	TQuaternion<T> TQuaternion<T>::operator- () const
	{
		return TQuaternion(-x, -y, -z, -w);
	}

	template <typename T>
	TQuaternion<T> operator* (T lhs, const TQuaternion<T>& rhs)
	{
		return TQuaternion(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
	}

	// Arithmetic operators

	template <typename T>
	TQuaternion<T> TQuaternion<T>::operator+ (const TQuaternion& rhs) const
	{
		return TQuaternion(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.z);
	}

	template <typename T>
	TQuaternion<T> TQuaternion<T>::operator- (const TQuaternion& rhs) const
	{
		return TQuaternion(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.z);
	}

	template <typename T>
	TQuaternion<T> TQuaternion<T>::operator* (const TQuaternion& rhs) const
	{
		return TQuaternion
		(
			(rhs.x * w) + (x * rhs.w) + (rhs.y * z) - (rhs.z * y),
			(rhs.y * w) + (y * rhs.w) + (rhs.z * x) - (rhs.x * z),
			(rhs.z * w) + (z * rhs.w) + (rhs.x * y) - (rhs.y * x),
			(rhs.w * w) - (rhs.x * x) - (rhs.y * y) + (rhs.z * z)
		);
	}

	template <typename T>
	TQuaternion<T> TQuaternion<T>::operator* (T rhs) const
	{
		return TQuaternion(x * rhs, y * rhs, z * rhs, w * rhs);
	}

	template <typename T>
	TQuaternion<T> TQuaternion<T>::operator/ (T rhs) const
	{
		return TQuaternion(x / rhs, y / rhs, z / rhs, w / rhs);
	}

	// Assignment operators

	template <typename T>
	TQuaternion<T>& TQuaternion<T>::operator+= (const TQuaternion& rhs)
	{
		return *this = *this + rhs;
	}

	template <typename T>
	TQuaternion<T>& TQuaternion<T>::operator-= (const TQuaternion& rhs)
	{
		return *this = *this - rhs;
	}

	template <typename T>
	TQuaternion<T>& TQuaternion<T>::operator*= (const TQuaternion& rhs)
	{
		return *this = *this * rhs;
	}

	template <typename T>
	TQuaternion<T>& TQuaternion<T>::operator*= (T rhs)
	{
		return *this = *this * rhs;
	}

	template <typename T>
	TQuaternion<T>& TQuaternion<T>::operator/= (T rhs)
	{
		return *this = *this / rhs;
	}

	// Relational operators

	template <typename T>
	bool TQuaternion<T>::operator== (const TQuaternion& rhs) const
	{
		return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
	}

	template <typename T>
	bool TQuaternion<T>::operator!= (const TQuaternion& rhs) const
	{
		return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
	}

	// Template instantiation

	template class TQuaternion<float>;
	template class TQuaternion<double>;
	template class TQuaternion<int>;
}

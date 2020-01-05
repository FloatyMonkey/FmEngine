// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Vector4.h"

#include "Functions.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4.h"

#include "../Assert.h"

namespace FM
{
	// Constructors

	template <typename T>
	TVector4<T>::TVector4()
		: x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}

	template <typename T>
	TVector4<T>::TVector4(T xyzw)
		: x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}

	template <typename T>
	TVector4<T>::TVector4(T x, T y, T z, T w)
		: x(x), y(y), z(z), w(w) {}

	template <typename T>
	TVector4<T>::TVector4(const TVector2<T>& vec, T z, T w)
		: x(vec.x), y(vec.y), z(z), w(w) {}

	template <typename T>
	TVector4<T>::TVector4(const TVector3<T>& vec, T w)
		: x(vec.x), y(vec.y), z(vec.z), w(w) {}

	// Predefined vectors

	template <typename T>
	const TVector4<T> TVector4<T>::One(T(1), T(1), T(1), T(1));

	template <typename T>
	const TVector4<T> TVector4<T>::Zero(T(0), T(0), T(0), T(0));

	template <typename T>
	const TVector4<T> TVector4<T>::UnitX(T(1), T(0), T(0), T(0));

	template <typename T>
	const TVector4<T> TVector4<T>::UnitY(T(0), T(1), T(0), T(0));

	template <typename T>
	const TVector4<T> TVector4<T>::UnitZ(T(0), T(0), T(1), T(0));

	template <typename T>
	const TVector4<T> TVector4<T>::UnitW(T(0), T(0), T(0), T(1));

	// Calculations

	template <typename T>
	T TVector4<T>::Length() const
	{
		return Math::Sqrt(x * x + y * y + z * z + w * w);
	}

	template <typename T>
	T TVector4<T>::LengthSquared() const
	{
		return x * x + y * y + z * z + w * w;
	}

	template <typename T>
	TVector4<T> TVector4<T>::Normalized() const
	{
		return *this / Length();
	}

	template <typename T>
	T TVector4<T>::Dot(const TVector4& lhs, const TVector4& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
	}

	template <typename T>
	T TVector4<T>::Distance(const TVector4& lhs, const TVector4& rhs)
	{
		return (lhs - rhs).Length();
	}

	template <typename T>
	TVector4<T> TVector4<T>::Transform(const TVector4& vector, const TMatrix4<T>& matrix)
	{
		return TVector4
		(
			vector.x * matrix(0, 0) + vector.y * matrix(1, 0) + vector.z * matrix(2, 0) + vector.w * matrix(3, 0),
			vector.x * matrix(0, 1) + vector.y * matrix(1, 1) + vector.z * matrix(2, 1) + vector.w * matrix(3, 1),
			vector.x * matrix(0, 2) + vector.y * matrix(1, 2) + vector.z * matrix(2, 2) + vector.w * matrix(3, 2),
			vector.x * matrix(0, 3) + vector.y * matrix(1, 3) + vector.z * matrix(2, 3) + vector.w * matrix(3, 3)
		);
	}

	// Operators

	template<typename T>
	T& TVector4<T>::operator[] (unsigned int i)
	{
		FM_ASSERT(i < 4);
		return elements[i];
	}

	template<typename T>
	const T& TVector4<T>::operator[] (unsigned int i) const
	{
		FM_ASSERT(i < 4);
		return elements[i];
	}

	template <typename T>
	TVector4<T> TVector4<T>::operator- () const
	{
		return TVector4(-x, -y, -z, -w);
	}

	template <typename T>
	TVector4<T> operator* (T lhs, const TVector4<T>& rhs)
	{
		return TVector4(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
	}

	template <typename T>
	TVector4<T> operator/ (T lhs, const TVector4<T>& rhs)
	{
		return TVector4(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z, lhs / rhs.w);
	}

	// Arithmetic operators

	template <typename T>
	TVector4<T> TVector4<T>::operator+ (const TVector4& rhs) const
	{
		return TVector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
	}

	template <typename T>
	TVector4<T> TVector4<T>::operator- (const TVector4& rhs) const
	{
		return TVector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
	}

	template <typename T>
	TVector4<T> TVector4<T>::operator* (T rhs) const
	{
		return TVector4(x * rhs, y * rhs, z * rhs, w * rhs);
	}

	template <typename T>
	TVector4<T> TVector4<T>::operator/ (T rhs) const
	{
		return TVector4(x / rhs, y / rhs, z / rhs, w / rhs);
	}

	// Assignment operators

	template <typename T>
	TVector4<T>& TVector4<T>::operator+= (const TVector4& rhs)
	{
		return *this = *this + rhs;
	}

	template <typename T>
	TVector4<T>& TVector4<T>::operator-= (const TVector4& rhs)
	{
		return *this = *this - rhs;
	}

	template <typename T>
	TVector4<T>& TVector4<T>::operator*= (T rhs)
	{
		return *this = *this * rhs;
	}

	template <typename T>
	TVector4<T>& TVector4<T>::operator/= (T rhs)
	{
		return *this = *this / rhs;
	}

	// Relational operators

	template <typename T>
	bool TVector4<T>::operator< (const TVector4& rhs) const
	{
		return x < rhs.x && y < rhs.y && z < rhs.z && w < rhs.w;
	}

	template <typename T>
	bool TVector4<T>::operator<= (const TVector4& rhs) const
	{
		return x <= rhs.x && y <= rhs.y && z <= rhs.z && w <= rhs.w;
	}

	template <typename T>
	bool TVector4<T>::operator== (const TVector4& rhs) const
	{
		return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
	}

	template <typename T>
	bool TVector4<T>::operator!= (const TVector4& rhs) const
	{
		return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
	}

	template <typename T>
	bool TVector4<T>::operator>= (const TVector4& rhs) const
	{
		return x >= rhs.x && y >= rhs.y && z >= rhs.z && w >= rhs.w;
	}

	template <typename T>
	bool TVector4<T>::operator> (const TVector4& rhs) const
	{
		return x > rhs.x && y > rhs.y && z > rhs.z && w > rhs.w;
	}

	// Template instantiation

	template class TVector4<float>;
	template class TVector4<double>;
	template class TVector4<int>;
}

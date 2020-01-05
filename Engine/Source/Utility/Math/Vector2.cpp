// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Vector2.h"

#include "Functions.h"
#include "Matrix3.h"
#include "Matrix4.h"

#include "../Assert.h"

namespace FM
{
	// Constructors

	template <typename T>
	TVector2<T>::TVector2()
		: x(T(0)), y(T(0)) {}

	template <typename T>
	TVector2<T>::TVector2(T xy)
		: x(xy), y(xy) {}

	template <typename T>
	TVector2<T>::TVector2(T x, T y)
		: x(x), y(y) {}

	// Predefined vectors

	template <typename T>
	const TVector2<T> TVector2<T>::One(T(1), T(1));

	template <typename T>
	const TVector2<T> TVector2<T>::Zero(T(0), T(0));

	template <typename T>
	const TVector2<T> TVector2<T>::UnitX(T(1), T(0));

	template <typename T>
	const TVector2<T> TVector2<T>::UnitY(T(0), T(1));

	// Calculations

	template <typename T>
	T TVector2<T>::Length() const
	{
		return Math::Sqrt(x * x + y * y);
	}

	template <typename T>
	T TVector2<T>::LengthSquared() const
	{
		return x * x + y * y;
	}

	template <typename T>
	TVector2<T> TVector2<T>::Normalized() const
	{
		return *this / Length();
	}

	template <typename T>
	T TVector2<T>::Dot(const TVector2& lhs, const TVector2& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}

	template <typename T>
	T TVector2<T>::Distance(const TVector2& lhs, const TVector2& rhs)
	{
		return (lhs - rhs).Length();
	}

	template <typename T>
	TVector2<T> TVector2<T>::Transform(const TVector2& vector, const TMatrix3<T>& matrix)
	{
		return TVector2
		(
			vector.x * matrix(0, 0) + vector.y * matrix(0, 1) + matrix(0, 2),
			vector.x * matrix(1, 0) + vector.y * matrix(1, 1) + matrix(1, 2)
		);
	}

	template <typename T>
	TVector2<T> TVector2<T>::Transform(const TVector2& vector, const TMatrix4<T>& matrix)
	{
		return TVector2
		(
			vector.x * matrix(0, 0) + vector.y * matrix(1, 0) + matrix(3, 0),
			vector.x * matrix(0, 1) + vector.y * matrix(1, 1) + matrix(3, 1)
		);
	}

	// Operators

	template<typename T>
	T& TVector2<T>::operator[](unsigned int i)
	{
		FM_ASSERT(i < 2);
		return elements[i];
	}

	template<typename T>
	const T& TVector2<T>::operator[](unsigned int i) const
	{
		FM_ASSERT(i < 2);
		return elements[i];
	}

	template <typename T>
	TVector2<T> TVector2<T>::operator- () const
	{
		return TVector2(-x, -y);
	}

	template <typename T>
	TVector2<T> operator* (T lhs, const TVector2<T>& rhs)
	{
		return TVector2(lhs * rhs.x, lhs * rhs.y);
	}

	template <typename T>
	TVector2<T> operator/ (T lhs, const TVector2<T>& rhs)
	{
		return TVector2(lhs / rhs.x, lhs / rhs.y);
	}

	// Arithmetic operators

	template <typename T>
	TVector2<T> TVector2<T>::operator+ (const TVector2& rhs) const
	{
		return TVector2(x + rhs.x, y + rhs.y);
	}

	template <typename T>
	TVector2<T> TVector2<T>::operator- (const TVector2& rhs) const
	{
		return TVector2(x - rhs.x, y - rhs.y);
	}

	template <typename T>
	TVector2<T> TVector2<T>::operator* (T rhs) const
	{
		return TVector2(x * rhs, y * rhs);
	}

	template <typename T>
	TVector2<T> TVector2<T>::operator/ (T rhs) const
	{
		return TVector2(x / rhs, y / rhs);
	}

	// Assignment operators

	template <typename T>
	TVector2<T>& TVector2<T>::operator+= (const TVector2& rhs)
	{
		return *this = *this + rhs;
	}

	template <typename T>
	TVector2<T>& TVector2<T>::operator-= (const TVector2& rhs)
	{
		return *this = *this - rhs;
	}

	template <typename T>
	TVector2<T>& TVector2<T>::operator*= (T rhs)
	{
		return *this = *this * rhs;
	}

	template <typename T>
	TVector2<T>& TVector2<T>::operator/= (T rhs)
	{
		return *this = *this / rhs;
	}

	// Relational operators

	template <typename T>
	bool TVector2<T>::operator< (const TVector2& rhs) const
	{
		return x < rhs.x && y < rhs.y;
	}

	template <typename T>
	bool TVector2<T>::operator<= (const TVector2& rhs) const
	{
		return x <= rhs.x && y <= rhs.y;
	}

	template <typename T>
	bool TVector2<T>::operator== (const TVector2& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	template <typename T>
	bool TVector2<T>::operator!= (const TVector2& rhs) const
	{
		return x != rhs.x || y != rhs.y;
	}

	template <typename T>
	bool TVector2<T>::operator>= (const TVector2& rhs) const
	{
		return x >= rhs.x && y >= rhs.y;
	}

	template <typename T>
	bool TVector2<T>::operator> (const TVector2& rhs) const
	{
		return x > rhs.x && y > rhs.y;
	}

	// Template instantiation

	template class TVector2<float>;
	template class TVector2<double>;
	template class TVector2<int>;
}

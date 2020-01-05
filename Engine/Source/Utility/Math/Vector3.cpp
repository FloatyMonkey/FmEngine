// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Vector3.h"

#include "Functions.h"
#include "Vector2.h"
#include "Matrix4.h"
#include "Quaternion.h"

#include "../Assert.h"

namespace FM
{
	// Constructors

	template <typename T>
	TVector3<T>::TVector3()
		: x(T(0)), y(T(0)), z(T(0)) {}
	
	template <typename T>
	TVector3<T>::TVector3(T xyz)
		: x(xyz), y(xyz), z(xyz) {}

	template <typename T>
	TVector3<T>::TVector3(T x, T y, T z)
		: x(x), y(y), z(z) {}

	template <typename T>
	TVector3<T>::TVector3(const TVector2<T>& vec, T z)
		: x(vec.x), y(vec.y), z(z) {}

	// Predefined vectors

	template <typename T>
	const TVector3<T> TVector3<T>::One(T(1), T(1), T(1));

	template <typename T>
	const TVector3<T> TVector3<T>::Zero(T(0), T(0), T(0));

	template <typename T>
	const TVector3<T> TVector3<T>::UnitX(T(1), T(0), T(0));

	template <typename T>
	const TVector3<T> TVector3<T>::UnitY(T(0), T(1), T(0));

	template <typename T>
	const TVector3<T> TVector3<T>::UnitZ(T(0), T(0), T(1));

	// Calculations

	template <typename T>
	T TVector3<T>::Length() const
	{
		return Math::Sqrt(x * x + y * y + z * z);
	}

	template <typename T>
	T TVector3<T>::LengthSquared() const
	{
		return x * x + y * y + z * z;
	}

	template <typename T>
	TVector3<T> TVector3<T>::Normalized() const
	{
		return *this / Length();
	}

	template <typename T>
	T TVector3<T>::Dot(const TVector3& lhs, const TVector3& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	template <typename T>
	TVector3<T> TVector3<T>::Cross(const TVector3& lhs, const TVector3& rhs)
	{
		return TVector3
		(
			lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x
		);
	}

	template <typename T>
	T TVector3<T>::Distance(const TVector3& lhs, const TVector3& rhs)
	{
		return (lhs - rhs).Length();
	}

	template <typename T>
	TVector3<T> TVector3<T>::Transform(const TVector3& vector, const TMatrix4<T>& matrix)
	{
		return TVector3
		(
			vector.x * matrix(0, 0) + vector.y * matrix(1, 0) + vector.z * matrix(2, 0) + matrix(3, 0),
			vector.x * matrix(0, 1) + vector.y * matrix(1, 1) + vector.z * matrix(2, 1) + matrix(3, 1),
			vector.x * matrix(0, 2) + vector.y * matrix(1, 2) + vector.z * matrix(2, 2) + matrix(3, 2)
		);
	}

	template <typename T>
	TVector3<T> TVector3<T>::Rotate(const TVector3& vector, const TQuaternion<T>& rotation)
	{
		TQuaternion<T> a = TQuaternion<T>(vector.x, vector.y, vector.z, T(0));
		TQuaternion<T> q = rotation.Conjugate();
		TQuaternion<T> r = q * a;
		r = r * rotation;
		return TVector3(r.x, r.y, r.z);
	}

	template <typename T>
	TVector3<T> TVector3<T>::InverseRotate(const TVector3& vector, const TQuaternion<T>& rotation)
	{
		TQuaternion<T> a = TQuaternion<T>(vector.x, vector.y, vector.z, T(0));
		TQuaternion<T> r = rotation * a;
		TQuaternion<T> q = rotation.Conjugate();
		r = r * q;
		return TVector3(r.x, r.y, r.z);
	}

	// Operators

	template<typename T>
	T& TVector3<T>::operator[](unsigned int i)
	{
		FM_ASSERT(i < 3);
		return elements[i];
	}

	template<typename T>
	const T& TVector3<T>::operator[](unsigned int i) const
	{
		FM_ASSERT(i < 3);
		return elements[i];
	}

	template <typename T>
	TVector3<T> TVector3<T>::operator- () const
	{
		return TVector3(-x, -y, -z);
	}

	template <typename T>
	TVector3<T> operator* (T lhs, const TVector3<T>& rhs)
	{
		return TVector3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
	}

	template <typename T>
	TVector3<T> operator/ (T lhs, const TVector3<T>& rhs)
	{
		return TVector3(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
	}

	// Arithmetic operators

	template <typename T>
	TVector3<T> TVector3<T>::operator+ (const TVector3& rhs) const
	{
		return TVector3(x + rhs.x, y + rhs.y, z + rhs.z);
	}

	template <typename T>
	TVector3<T> TVector3<T>::operator- (const TVector3& rhs) const
	{
		return TVector3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	template <typename T>
	TVector3<T> TVector3<T>::operator* (T rhs) const
	{
		return TVector3(x * rhs, y * rhs, z * rhs);
	}

	template <typename T>
	TVector3<T> TVector3<T>::operator/ (T rhs) const
	{
		return TVector3(x / rhs, y / rhs, z / rhs);
	}

	// Assignment operators

	template <typename T>
	TVector3<T>& TVector3<T>::operator+= (const TVector3& rhs)
	{
		return *this = *this + rhs;
	}

	template <typename T>
	TVector3<T>& TVector3<T>::operator-= (const TVector3& rhs)
	{
		return *this = *this - rhs;
	}

	template <typename T>
	TVector3<T>& TVector3<T>::operator*= (T rhs)
	{
		return *this = *this * rhs;
	}

	template <typename T>
	TVector3<T>& TVector3<T>::operator/= (T rhs)
	{
		return *this = *this / rhs;
	}

	// Relational operators

	template <typename T>
	bool TVector3<T>::operator< (const TVector3& rhs) const
	{
		return x < rhs.x && y < rhs.y && z < rhs.z;
	}

	template <typename T>
	bool TVector3<T>::operator<= (const TVector3& rhs) const
	{
		return x <= rhs.x && y <= rhs.y && z <= rhs.z;
	}

	template <typename T>
	bool TVector3<T>::operator== (const TVector3& rhs) const
	{
		return x == rhs.x && y == rhs.y && z == rhs.z;
	}

	template <typename T>
	bool TVector3<T>::operator!= (const TVector3& rhs) const
	{
		return x != rhs.x || y != rhs.y || z != rhs.z;
	}

	template <typename T>
	bool TVector3<T>::operator>= (const TVector3& rhs) const
	{
		return x >= rhs.x && y >= rhs.y && z >= rhs.z;
	}

	template <typename T>
	bool TVector3<T>::operator> (const TVector3& rhs) const
	{
		return x > rhs.x && y > rhs.y && z > rhs.z;
	}

	// Template instantiation

	template class TVector3<float>;
	template class TVector3<double>;
	template class TVector3<int>;
}

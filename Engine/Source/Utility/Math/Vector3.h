// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

namespace FM
{
	template <typename T> class TVector2;
	template <typename T> class TMatrix4;
	template <typename T> class TQuaternion;

	/// A three-dimensional vector.

	template <typename T>
	class TVector3
	{
	public:

		union
		{
			T elements[3];
			struct { T x, y, z; };
		};

	public:

		// Constructors

		TVector3();
		TVector3(T xyz);
		TVector3(T x, T y, T z = T(0));
		TVector3(const TVector2<T>& vec, T z = T(0));

		template <typename U>
		TVector3(const TVector3<U>& v);

		// Predefined vectors

		static const TVector3 One;
		static const TVector3 Zero;
		static const TVector3 UnitX;
		static const TVector3 UnitY;
		static const TVector3 UnitZ;

		// Calculations

		/// Returns the length (magnitude) of this vector.
		T Length() const;

		/// Returns the squared length (magnitude) of this vector.
		T LengthSquared() const;

		/// Returns the normalized vector.
		TVector3 Normalized() const;

		/// Returns the dot (scalar) product of 2 vectors.
		static T Dot(const TVector3& lhs, const TVector3& rhs);

		/// Returns the cross-product of 2 vectors.
		static TVector3 Cross(const TVector3& lhs, const TVector3& rhs);

		/// Returns the distance between 2 vectors.
		static T Distance(const TVector3& lhs, const TVector3& rhs);

		/// Transform a vector using a Matrix4.
		static TVector3 Transform(const TVector3& vector, const TMatrix4<T>& matrix);

		/// Rotate a vector using a quaternion.
		static TVector3 Rotate(const TVector3& vector, const TQuaternion<T>& rotation);

		/// Inverse rotate a vector using a quaternion.
		static TVector3 InverseRotate(const TVector3& vector, const TQuaternion<T>& rotation);

		// Operators

		T& operator[] (unsigned int i);
		const T& operator[] (unsigned int i) const;

		TVector3 operator- () const;

		friend TVector3 operator* (T lhs, const TVector3& rhs);
		friend TVector3 operator/ (T lhs, const TVector3& rhs);

		// Arithmetic operators

		TVector3 operator+ (const TVector3& rhs) const;
		TVector3 operator- (const TVector3& rhs) const;

		TVector3 operator* (T rhs) const;
		TVector3 operator/ (T rhs) const;

		// Assignment operators

		TVector3& operator+= (const TVector3& rhs);
		TVector3& operator-= (const TVector3& rhs);

		TVector3& operator*= (T rhs);
		TVector3& operator/= (T rhs);

		// Relational operators

		bool operator< (const TVector3& rhs) const;
		bool operator<= (const TVector3& rhs) const;
		bool operator== (const TVector3& rhs) const;
		bool operator!= (const TVector3& rhs) const;
		bool operator>= (const TVector3& rhs) const;
		bool operator> (const TVector3& rhs) const;
	};

	// Template implementations

	template <typename T>
	template <typename U>
	TVector3<T>::TVector3(const TVector3<U>& v)
		: x(T(v.x)), y(T(v.y)), z(T(v.z)){}

	// Type aliases

	using Vector3 = TVector3<float>;

	using Vector3F = TVector3<float>;
	using Vector3D = TVector3<double>;
	using Vector3I = TVector3<int>;
}

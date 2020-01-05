// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

namespace FM
{
	template <typename T> class TVector2;
	template <typename T> class TVector3;
	template <typename T> class TMatrix4;

	/// A four-dimensional vector.

	template <typename T>
	class TVector4
	{
	public:

		union
		{
			T elements[4];
			struct { T x, y, z, w; };
		};

	public:

		// Constructors

		TVector4();
		TVector4(T xyzw);
		TVector4(T x, T y, T z = T(0), T w = T(0));
		TVector4(const TVector2<T>& vec, T z = T(0), T w = T(0));
		TVector4(const TVector3<T>& vec, T w = T(0));

		template <typename U>
		TVector4(const TVector4<U>& v);

		// Predefined vectors

		static const TVector4 One;
		static const TVector4 Zero;
		static const TVector4 UnitX;
		static const TVector4 UnitY;
		static const TVector4 UnitZ;
		static const TVector4 UnitW;

		// Calculations

		/// Returns the length (magnitude) of this vector.
		T Length() const;

		/// Returns the squared length (magnitude) of this vector.
		T LengthSquared() const;

		/// Returns the normalized vector.
		TVector4 Normalized() const;

		/// Returns the dot (scalar) product of 2 vectors.
		static T Dot(const TVector4& lhs, const TVector4& rhs);

		/// Returns the distance between 2 vectors.
		static T Distance(const TVector4& lhs, const TVector4& rhs);

		/// Transform a vector using a Matrix4.
		static TVector4 Transform(const TVector4& vector, const TMatrix4<T>& matrix);

		// Operators

		T& operator[] (unsigned int i);
		const T& operator[] (unsigned int i) const;

		TVector4 operator- () const;

		friend TVector4 operator* (T lhs, const TVector4& rhs);
		friend TVector4 operator/ (T lhs, const TVector4& rhs);

		// Arithmetic operators

		TVector4 operator+ (const TVector4& rhs) const;
		TVector4 operator- (const TVector4& rhs) const;

		TVector4 operator* (T rhs) const;
		TVector4 operator/ (T rhs) const;

		// Assignment operators

		TVector4& operator+= (const TVector4& rhs);
		TVector4& operator-= (const TVector4& rhs);

		TVector4& operator*= (T rhs);
		TVector4& operator/= (T rhs);

		// Relational operators

		bool operator< (const TVector4& rhs) const;
		bool operator<= (const TVector4& rhs) const;
		bool operator== (const TVector4& rhs) const;
		bool operator!= (const TVector4& rhs) const;
		bool operator>= (const TVector4& rhs) const;
		bool operator> (const TVector4& rhs) const;
	};

	// Template implementations

	template <typename T>
	template <typename U>
	TVector4<T>::TVector4(const TVector4<U>& v)
		: x(T(v.x)), y(T(v.y)), z(T(v.z)), w(T(v.w)) {}

	// Type aliases

	using Vector4 = TVector4<float>;

	using Vector4F = TVector4<float>;
	using Vector4D = TVector4<double>;
	using Vector4I = TVector4<int>;
}

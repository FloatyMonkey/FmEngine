// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

namespace FM
{
	template <typename T> class TMatrix3;
	template <typename T> class TMatrix4;

	/// A two-dimensional vector.

	template <typename T>
	class TVector2
	{
	public:

		union
		{
			T elements[2];
			struct { T x, y; };
		};

	public:

		// Constructors

		TVector2();
		TVector2(T xy);
		TVector2(T x, T y);

		template <typename U>
		TVector2(const TVector2<U>& v);

		// Predefined vectors

		static const TVector2 One;
		static const TVector2 Zero;
		static const TVector2 UnitX;
		static const TVector2 UnitY;

		// Calculations

		/// Returns the length (magnitude) of this vector.
		T Length() const;

		/// Returns the squared length (magnitude) of this vector.
		T LengthSquared() const;

		/// Returns the normalized vector.
		TVector2 Normalized() const;

		/// Returns the dot (scalar) product of 2 vectors.
		static T Dot(const TVector2& lhs, const TVector2& rhs);

		/// Returns the distance between 2 vectors.
		static T Distance(const TVector2& lhs, const TVector2& rhs);

		/// Transform a vector using a Matrix3.
		static TVector2 Transform(const TVector2& vector, const TMatrix3<T>& matrix);

		/// Transform a vector using a Matrix4.
		static TVector2 Transform(const TVector2& vector, const TMatrix4<T>& matrix);

		// Operators

		T& operator[] (unsigned int i);
		const T& operator[] (unsigned int i) const;

		TVector2 operator- () const;

		friend TVector2 operator* (T lhs, const TVector2& rhs);
		friend TVector2 operator/ (T lhs, const TVector2& rhs);

		// Arithmetic operators

		TVector2 operator+ (const TVector2& rhs) const;
		TVector2 operator- (const TVector2& rhs) const;

		TVector2 operator* (T rhs) const;
		TVector2 operator/ (T rhs) const;

		// Assignment operators

		TVector2& operator+= (const TVector2& rhs);
		TVector2& operator-= (const TVector2& rhs);

		TVector2& operator*= (T rhs);
		TVector2& operator/= (T rhs);

		// Relational operators

		bool operator< (const TVector2& rhs) const;
		bool operator<= (const TVector2& rhs) const;
		bool operator== (const TVector2& rhs) const;
		bool operator!= (const TVector2& rhs) const;
		bool operator>= (const TVector2& rhs) const;
		bool operator> (const TVector2& rhs) const;
	};

	// Template implementations

	template <typename T>
	template <typename U>
	TVector2<T>::TVector2(const TVector2<U>& v)
		: x(T(v.x)), y(T(v.y)) {}

	// Type aliases

	using Vector2 = TVector2<float>;

	using Vector2F = TVector2<float>;
	using Vector2D = TVector2<double>;
	using Vector2I = TVector2<int>;
}

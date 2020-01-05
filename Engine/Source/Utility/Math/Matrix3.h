// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

namespace FM
{
	template <typename T> class TRadian;
	template <typename T> class TVector2;
	template <typename T> class TVector3;

	/// Class representing a 3x3 matrix in a row-major format.

	template <typename T>
	class TMatrix3
	{
	public:

		union
		{
			T elements[9];	///< Interpreted as [row * 3 + column]
			T m[3][3];		///< Interpreted as [row][column]
		};

	public:

		// Constructors

		TMatrix3();
		TMatrix3(T d);
		TMatrix3(const T* elements);

		TMatrix3
		(
			const TVector3<T>& r0,
			const TVector3<T>& r1,
			const TVector3<T>& r2
		);

		TMatrix3
		(
			T m00, T m01, T m02,
			T m10, T m11, T m12,
			T m20, T m21, T m22
		);

		// Predefined matrices

		static const TMatrix3 Zero;
		static const TMatrix3 Identity;

		// Calculations

		/// Calculates the determinant of this matrix.
		T Determinant() const;

		/// Calculates the inverse of this matrix.
		TMatrix3 Inverted() const;

		/// Calculates the transpose of this matrix.
		TMatrix3 Transposed() const;

		/// Creates a translation matrix from x and y positions.
		static TMatrix3 Translation(T x, T y);
		/// Creates a translation matrix from a vector.
		static TMatrix3 Translation(const TVector2<T>& v);

		/// Creates a rotation matrix.
		static TMatrix3 Rotation(const TRadian<T>& r);

		/// Creates a scaling matrix from x and y scale factors.
		static TMatrix3 Scaling(T x, T y);
		/// Creates a scaling matrix from a vector.
		static TMatrix3 Scaling(const TVector2<T>& v);
		/// Creates a uniform scaling matrix.
		static TMatrix3 Scaling(T u);

		/// Creates a skewing matrix from x and y interpolants.
		static TMatrix3 Skewing(T x, T y);
		/// Creates a skewing matrix from a vector.
		static TMatrix3 Skewing(const TVector2<T>& v);

		// Getters & Setters

		TVector3<T> GetRow(int i) const;
		TVector3<T> GetColumn(int i) const;

		void SetRow(int i, const TVector3<T>& v);
		void SetColumn(int i, const TVector3<T>& v);

		// Operators

		T& operator() (unsigned int row, unsigned int col);
		const T&  operator() (unsigned int row, unsigned int col) const;

		TMatrix3 operator- () const;
		friend TMatrix3 operator* (T lhs, const TMatrix3<T>& rhs);

		// Arithmetic operators

		TMatrix3 operator+ (const TMatrix3& rhs) const;
		TMatrix3 operator- (const TMatrix3& rhs) const;
		TMatrix3 operator* (const TMatrix3& rhs) const;

		TMatrix3 operator* (T rhs) const;
		TMatrix3 operator/ (T rhs) const;

		// Assignment operators

		TMatrix3& operator+= (const TMatrix3& rhs);
		TMatrix3& operator-= (const TMatrix3& rhs);
		TMatrix3& operator*= (const TMatrix3& rhs);

		TMatrix3& operator*= (T rhs);
		TMatrix3& operator/= (T rhs);

		// Relational operators

		bool operator== (const TMatrix3& rhs) const;
		bool operator!= (const TMatrix3& rhs) const;
	};

	// Type aliases

	using Matrix3 = TMatrix3<float>;

	using Matrix3F = TMatrix3<float>;
	using Matrix3D = TMatrix3<double>;
	using Matrix3I = TMatrix3<int>;
}

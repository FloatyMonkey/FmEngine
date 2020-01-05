// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

namespace FM
{
	template <typename T> class TRadian;
	template <typename T> class TVector3;
	template <typename T> class TVector4;
	template <typename T> class TMatrix3;
	template <typename T> class TQuaternion;

	/// Class representing a 4x4 matrix in a row-major format.

	template <typename T>
	class TMatrix4
	{
	public:

		union
		{
			T elements[16];	///< Interpreted as [row * 4 + column]
			T m[4][4];		///< Interpreted as [row][column]
		};

	public:

		// Constructors

		TMatrix4();
		TMatrix4(T d);
		TMatrix4(const T* elements);

		TMatrix4(const TMatrix3<T>& matrix);

		TMatrix4
		(
			const TVector4<T>& r0,
			const TVector4<T>& r1,
			const TVector4<T>& r2,
			const TVector4<T>& r3
		);

		TMatrix4
		(
			T m00, T m01, T m02, T m03,
			T m10, T m11, T m12, T m13,
			T m20, T m21, T m22, T m23,
			T m30, T m31, T m32, T m33
		);

		// Predefined matrices

		static const TMatrix4 Zero;
		static const TMatrix4 Identity;

		// Calculations

		/// Calculates the determinant of this matrix.
		T Determinant() const;

		/// Calculates the inverse of this matrix.
		TMatrix4 Inverted() const;

		/// Calculates the transpose of this matrix.
		TMatrix4 Transposed() const;

		/// Creates a translation matrix from x, y and z positions.
		static TMatrix4 Translation(T x, T y, T z);
		/// Creates a translation matrix from a vector.
		static TMatrix4 Translation(const TVector3<T>& v);

		/// Creates a rotation matrix around the X axis.
		static TMatrix4 RotationX(const TRadian<T>& r);
		/// Creates a rotation matrix around the Y axis.
		static TMatrix4 RotationY(const TRadian<T>& r);
		/// Creates a rotation matrix around the Z axis.
		static TMatrix4 RotationZ(const TRadian<T>& r);

		/// Creates a rotation matrix from a quaternion.
		static TMatrix4 RotationQuaternion(const TQuaternion<T>& q);
		/// Creates a rotation matrix from an axis and angle.
		static TMatrix4 RotationAxisAngle(const TVector3<T>& axis, const TRadian<T>& angle);
		/// Creates a rotation matrix from a yaw, pitch and roll angle.
		static TMatrix4 RotationYawPitchRoll(const TRadian<T>& yaw, const TRadian<T>& pitch, const TRadian<T>& roll);

		/// Creates a scaling matrix from x, y and z scale factors.
		static TMatrix4 Scaling(T x, T y, T z);
		/// Creates a scaling matrix from a vector.
		static TMatrix4 Scaling(const TVector3<T>& v);
		/// Creates a uniform scaling matrix.
		static TMatrix4 Scaling(T u);

		/// Creates a transformation matrix from translation, rotation and scale.
		static TMatrix4 Transformation(const TVector3<T>& translation, const TQuaternion<T>& rotation, const TVector3<T>& scale);

		/// Creates a left-handed Look At (view) matrix.
		/// @param position Camera position.
		/// @param target Position to look at.
		/// @param upward Upward vector.
		/// @return The look at matrix.
		static TMatrix4 LookAt(const TVector3<T>& position, const TVector3<T>& target, const TVector3<T>& upward);

		/// Creates a left-handed perspective projection matrix.
		/// This matrix mimics the human eye and real world camera's.
		/// This means that objects up close look bigger and objects further away smaller.
		/// @param fov Horizontal Field Of View.
		/// @param aspectRatio Aspect ratio. Determines the vertical field of view. Usally calculated using (width / height).
		/// @param nearClip Distance to the near clip plane. Geometry in front of this plane will not be rendered.
		/// @param farClip Distance to the far clip plane. Geometry behind this plane will not be rendered.
		/// @return The perspective projection matrix.
		static TMatrix4 Perspective(const TRadian<T>& fov, T aspectRatio, T nearClip, T farClip);

		static TMatrix4 Perspective(T left, T right, T bottom, T top, T near, T far);

		/// Creates a left-handed orthographic projection matrix.
		/// @param width Width of the view volume.
		/// @param height Height of the view volume.
		/// @param nearClip Distance to the near clip plane. Geometry in front of this plane will not be rendered.
		/// @param farClip Distance to the far clip plane. Geometry behind this plane will not be rendered.
		/// @return The orthographic projection matrix.
		static TMatrix4 Orthographic(T width, T height, T nearClip, T farClip);

		static TMatrix4 Orthographic(T left, T right, T bottom, T top, T near, T far);

		// Getters & Setters

		TVector4<T> GetRow(int i) const;
		TVector4<T> GetColumn(int i) const;

		void SetRow(int i, const TVector4<T>& v);
		void SetColumn(int i, const TVector4<T>& v);

		// Operators

		T& operator() (unsigned int row, unsigned int col);
		const T&  operator() (unsigned int row, unsigned int col) const;

		TMatrix4 operator- () const;
		friend TMatrix4 operator* (T lhs, const TMatrix4<T>& rhs);

		// Arithmetic operators

		TMatrix4 operator+ (const TMatrix4& rhs) const;
		TMatrix4 operator- (const TMatrix4& rhs) const;
		TMatrix4 operator* (const TMatrix4& rhs) const;

		TMatrix4 operator* (T rhs) const;
		TMatrix4 operator/ (T rhs) const;

		// Assignment operators

		TMatrix4& operator+= (const TMatrix4& rhs);
		TMatrix4& operator-= (const TMatrix4& rhs);
		TMatrix4& operator*= (const TMatrix4& rhs);

		TMatrix4& operator*= (T rhs);
		TMatrix4& operator/= (T rhs);

		// Relational operators

		bool operator== (const TMatrix4& rhs) const;
		bool operator!= (const TMatrix4& rhs) const;
	};

	// Type aliases

	using Matrix4 = TMatrix4<float>;

	using Matrix4F = TMatrix4<float>;
	using Matrix4D = TMatrix4<double>;
	using Matrix4I = TMatrix4<int>;
}

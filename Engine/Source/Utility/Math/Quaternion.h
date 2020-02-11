// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

namespace FM
{
	template <typename T> class TRadian;
	template <typename T> class TVector3;
	template <typename T> class TMatrix4;

	/// Class representing a quaternion used for 3D rotations.

	template <typename T>
	class TQuaternion
	{
	public:

		union
		{
			T elements[4];
			struct { T x, y, z, w; };
		};

	public:

		// Constructors

		TQuaternion();
		TQuaternion(T x, T y, T z, T w);
		TQuaternion(const TVector3<T>& v, T w = T(0));

		// Predefined quaternions

		static const TQuaternion Zero;
		static const TQuaternion Identity;

		// Calculations

		/// Calculate the length (magnitude) of the quaternion.
		T Length() const;

		/// Normalize the quaternion, this returns a quaternion of length 1.
		TQuaternion Normalize() const;

		/// Calculate the conjugate of the quaternion.
		TQuaternion Conjugate() const;

		/// Calculate the dot (scalar) product of 2 quaternions.
		static T Dot(const TQuaternion& lhs, const TQuaternion& rhs);

		/// Creates a quaternion form a rotation matrix.
		static TQuaternion RotationMatrix(const TMatrix4<T>& rotation);

		/// Creates a quaternion from an axis and angle.
		static TQuaternion AxisAngle(const TVector3<T>& axis, const TRadian<T>& angle);

		/// Creates a quaternion from a yaw, pitch and roll angle.
		static TQuaternion YawPitchRoll(const TRadian<T>& yaw, const TRadian<T>& pitch, const TRadian<T>& roll);

		// Operators

		TQuaternion operator- () const;
		friend TQuaternion operator* (T lhs, const TQuaternion& rhs);

		// Arithmetic operators

		TQuaternion operator+ (const TQuaternion& rhs) const;
		TQuaternion operator- (const TQuaternion& rhs) const;
		TQuaternion operator* (const TQuaternion& rhs) const;

		TQuaternion operator* (T rhs) const;
		TQuaternion operator/ (T rhs) const;

		// Assignment operators

		TQuaternion& operator+= (const TQuaternion& rhs);
		TQuaternion& operator-= (const TQuaternion& rhs);
		TQuaternion& operator*= (const TQuaternion& rhs);

		TQuaternion& operator*= (T rhs);
		TQuaternion& operator/= (T rhs);

		// Relational operators

		bool operator== (const TQuaternion& rhs) const;
		bool operator!= (const TQuaternion& rhs) const;
	};

	// Type aliases

	using Quaternion = TQuaternion<float>;

	using QuaternionF = TQuaternion<float>;
	using QuaternionD = TQuaternion<double>;
	using QuaternionI = TQuaternion<int>;
}

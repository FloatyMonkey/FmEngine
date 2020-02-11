// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Matrix4.h"

#include "Functions.h"
#include "Radian.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3.h"
#include "Quaternion.h"

#include "../Assert.h"
#include "../Memory.h"

namespace FM
{
	// Constructors

	template <typename T>
	TMatrix4<T>::TMatrix4()
		: elements {
			T(0), T(0), T(0), T(0),
			T(0), T(0), T(0), T(0),
			T(0), T(0), T(0), T(0),
			T(0), T(0), T(0), T(0)
		}
	{}

	template <typename T>
	TMatrix4<T>::TMatrix4(T d)
		: elements {
			T(d), T(0), T(0), T(0),
			T(0), T(d), T(0), T(0),
			T(0), T(0), T(d), T(0),
			T(0), T(0), T(0), T(d)
		}
	{}

	template <typename T>
	TMatrix4<T>::TMatrix4(const T* elements)
	{
		Memory::Memcpy(m, elements, 16 * sizeof(T));
	}

	template <typename T>
	TMatrix4<T>::TMatrix4(const TMatrix3<T>& matrix)
		: elements {
			matrix.m[0][0], matrix.m[0][1], matrix.m[0][2], T(0),
			matrix.m[1][0], matrix.m[1][1], matrix.m[1][2], T(0),
			matrix.m[2][0], matrix.m[2][1], matrix.m[2][2], T(0),
			T(0),           T(0),           T(0),           T(1)
		}
	{}

	template <typename T>
	TMatrix4<T>::TMatrix4
	(
		const TVector4<T>& r0,
		const TVector4<T>& r1,
		const TVector4<T>& r2,
		const TVector4<T>& r3
	)
		: elements {
			r0.x, r0.y, r0.z, r0.w,
			r1.x, r1.y, r1.z, r1.w,
			r2.x, r2.y, r2.z, r2.w,
			r3.x, r3.y, r3.z, r3.w
		}
	{}

	template <typename T>
	TMatrix4<T>::TMatrix4
	(
		T m00, T m01, T m02, T m03,
		T m10, T m11, T m12, T m13,
		T m20, T m21, T m22, T m23,
		T m30, T m31, T m32, T m33
	)
		: elements {
			m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33
		}
	{}

	// Predefined matrices

	template <typename T>
	const TMatrix4<T> TMatrix4<T>::Zero(T(0));

	template <typename T>
	const TMatrix4<T> TMatrix4<T>::Identity(T(1));

	// Calculations

	template <typename T>
	T TMatrix4<T>::Determinant() const
	{
		return
		(
			m[0][0] * m[1][1] * m[2][2] * m[3][3] + m[0][0] * m[1][2] * m[2][3] * m[3][1] +
			m[0][0] * m[1][3] * m[2][1] * m[3][2] + m[0][1] * m[1][0] * m[2][3] * m[3][2] +
			m[0][1] * m[1][2] * m[2][0] * m[3][3] + m[0][1] * m[1][3] * m[2][2] * m[3][0] +
			m[0][2] * m[1][0] * m[2][1] * m[3][3] + m[0][2] * m[1][1] * m[2][3] * m[3][0] +
			m[0][2] * m[1][3] * m[2][0] * m[3][1] + m[0][3] * m[1][0] * m[2][2] * m[3][1] +
			m[0][3] * m[1][1] * m[2][0] * m[3][2] + m[0][3] * m[1][2] * m[2][1] * m[3][0] -
			m[0][0] * m[1][1] * m[2][3] * m[3][2] - m[0][0] * m[1][2] * m[2][1] * m[3][3] -
			m[0][0] * m[1][3] * m[2][2] * m[3][1] - m[0][1] * m[1][0] * m[2][2] * m[3][3] -
			m[0][1] * m[1][2] * m[2][3] * m[3][0] - m[0][1] * m[1][3] * m[2][0] * m[3][2] -
			m[0][2] * m[1][0] * m[2][3] * m[3][1] - m[0][2] * m[1][1] * m[2][0] * m[3][3] -
			m[0][2] * m[1][3] * m[2][1] * m[3][0] - m[0][3] * m[1][0] * m[2][1] * m[3][2] -
			m[0][3] * m[1][1] * m[2][2] * m[3][0] - m[0][3] * m[1][2] * m[2][0] * m[3][1]
		);
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::Inverted() const
	{
		T det = Determinant();

		T m11 = m[1][1] * m[2][2] * m[3][3] + m[1][2] * m[2][3] * m[3][1] + m[1][3] * m[2][1] * m[3][2] - m[1][1] * m[2][3] * m[3][2] - m[1][2] * m[2][1] * m[3][3] - m[1][3] * m[2][2] * m[3][1];
		T m12 = m[0][1] * m[2][3] * m[3][2] + m[0][2] * m[2][1] * m[3][3] + m[0][3] * m[2][2] * m[3][1] - m[0][1] * m[2][2] * m[3][3] - m[0][2] * m[2][3] * m[3][1] - m[0][3] * m[2][1] * m[3][2];
		T m13 = m[0][1] * m[1][2] * m[3][3] + m[0][2] * m[1][3] * m[3][1] + m[0][3] * m[1][1] * m[3][2] - m[0][1] * m[1][3] * m[3][2] - m[0][2] * m[1][1] * m[3][3] - m[0][3] * m[1][2] * m[3][1];
		T m14 = m[0][1] * m[1][3] * m[2][2] + m[0][2] * m[1][1] * m[2][3] + m[0][3] * m[1][2] * m[2][1] - m[0][1] * m[1][2] * m[2][3] - m[0][2] * m[1][3] * m[2][1] - m[0][3] * m[1][1] * m[2][2];

		T m21 = m[1][0] * m[2][3] * m[3][2] + m[1][2] * m[2][0] * m[3][3] + m[1][3] * m[2][2] * m[3][0] - m[1][0] * m[2][2] * m[3][3] - m[1][2] * m[2][3] * m[3][0] - m[1][3] * m[2][0] * m[3][2];
		T m22 = m[0][0] * m[2][2] * m[3][3] + m[0][2] * m[2][3] * m[3][0] + m[0][3] * m[2][0] * m[3][2] - m[0][0] * m[2][3] * m[3][2] - m[0][2] * m[2][0] * m[3][3] - m[0][3] * m[2][2] * m[3][0];
		T m23 = m[0][0] * m[1][3] * m[3][2] + m[0][2] * m[1][0] * m[3][3] + m[0][3] * m[1][2] * m[3][0] - m[0][0] * m[1][2] * m[3][3] - m[0][2] * m[1][3] * m[3][0] - m[0][3] * m[1][0] * m[3][2];
		T m24 = m[0][0] * m[1][2] * m[2][3] + m[0][2] * m[1][3] * m[2][0] + m[0][3] * m[1][0] * m[2][2] - m[0][0] * m[1][3] * m[2][2] - m[0][2] * m[1][0] * m[2][3] - m[0][3] * m[1][2] * m[2][0];

		T m31 = m[1][0] * m[2][1] * m[3][3] + m[1][1] * m[2][3] * m[3][0] + m[1][3] * m[2][0] * m[3][1] - m[1][0] * m[2][3] * m[3][1] - m[1][1] * m[2][0] * m[3][3] - m[1][3] * m[2][1] * m[3][0];
		T m32 = m[0][0] * m[2][3] * m[3][1] + m[0][1] * m[2][0] * m[3][3] + m[0][3] * m[2][1] * m[3][0] - m[0][0] * m[2][1] * m[3][3] - m[0][1] * m[2][3] * m[3][0] - m[0][3] * m[2][0] * m[3][1];
		T m33 = m[0][0] * m[1][1] * m[3][3] + m[0][1] * m[1][3] * m[3][0] + m[0][3] * m[1][0] * m[3][1] - m[0][0] * m[1][3] * m[3][1] - m[0][1] * m[1][0] * m[3][3] - m[0][3] * m[1][1] * m[3][0];
		T m34 = m[0][0] * m[1][3] * m[2][1] + m[0][1] * m[1][0] * m[2][3] + m[0][3] * m[1][1] * m[2][0] - m[0][0] * m[1][1] * m[2][3] - m[0][1] * m[1][3] * m[2][0] - m[0][3] * m[1][0] * m[2][1];

		T m41 = m[1][0] * m[2][2] * m[3][1] + m[1][1] * m[2][0] * m[3][2] + m[1][2] * m[2][1] * m[3][0] - m[1][0] * m[2][1] * m[3][2] - m[1][1] * m[2][2] * m[3][0] - m[1][2] * m[2][0] * m[3][1];
		T m42 = m[0][0] * m[2][1] * m[3][2] + m[0][1] * m[2][2] * m[3][0] + m[0][2] * m[2][0] * m[3][1] - m[0][0] * m[2][2] * m[3][1] - m[0][1] * m[2][0] * m[3][2] - m[0][2] * m[2][1] * m[3][0];
		T m43 = m[0][0] * m[1][2] * m[3][1] + m[0][1] * m[1][0] * m[3][2] + m[0][2] * m[1][1] * m[3][0] - m[0][0] * m[1][1] * m[3][2] - m[0][1] * m[1][2] * m[3][0] - m[0][2] * m[1][0] * m[3][1];
		T m44 = m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] + m[0][2] * m[1][0] * m[2][1] - m[0][0] * m[1][2] * m[2][1] - m[0][1] * m[1][0] * m[2][2] - m[0][2] * m[1][1] * m[2][0];

		T invdet = T(1) / det;

		return TMatrix4
		(
			m11 * invdet, m12 * invdet, m13 * invdet, m14 * invdet,
			m21 * invdet, m22 * invdet, m23 * invdet, m24 * invdet,
			m31 * invdet, m32 * invdet, m33 * invdet, m34 * invdet,
			m41 * invdet, m42 * invdet, m43 * invdet, m44 * invdet
		);
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::Transposed() const
	{
		return TMatrix4
		(
			m[0][0], m[1][0], m[2][0], m[3][0],
			m[0][1], m[1][1], m[2][1], m[3][1],
			m[0][2], m[1][2], m[2][2], m[3][2],
			m[0][3], m[1][3], m[2][3], m[3][3]
		);
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::Translation(T x, T y, T z)
	{
		return TMatrix4
		(
			T(1), T(0), T(0), x,
			T(0), T(1), T(0), y,
			T(0), T(0), T(1), z,
			T(0), T(0), T(0), T(1)
		);
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::Translation(const TVector3<T>& v)
	{
		return Translation(v.x, v.y, v.z);
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::RotationX(const TRadian<T>& r)
	{
		T cos = Math::Cos(r);
		T sin = Math::Sin(r);

		return TMatrix4
		(
			T(1), T(0),  T(0), T(0),
			T(0), cos,  -sin,  T(0),
			T(0), sin,   cos,  T(0),
			T(0), T(0),  T(0), T(1)
		);
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::RotationY(const TRadian<T>& r)
	{
		T cos = Math::Cos(r);
		T sin = Math::Sin(r);

		return TMatrix4
		(
			 cos,  T(0), sin,  T(0),
			 T(0), T(1), T(0), T(0),
			-sin,  T(0), cos,  T(0),
			 T(0), T(0), T(0), T(1)
		);
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::RotationZ(const TRadian<T>& r)
	{
		T cos = Math::Cos(r);
		T sin = Math::Sin(r);

		return TMatrix4
		(
			cos,  -sin,  T(0), T(0),
			sin,   cos,  T(0), T(0),
			T(0),  T(0), T(1), T(0),
			T(0),  T(0), T(0), T(1)
		);
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::RotationQuaternion(const TQuaternion<T>& q)
	{
		T xx = q.x * q.x;
		T yy = q.y * q.y;
		T zz = q.z * q.z;
		T xy = q.x * q.y;
		T yw = q.y * q.w;
		T yz = q.y * q.z;
		T xw = q.x * q.w;
		T zx = q.z * q.x;
		T zw = q.z * q.w;

		return TMatrix4
		(
			T(1) - (T(2) * (yy + zz)), T(2) * (xy + zw), T(2) * (zx - yw), T(0),
			T(2) * (xy - zw), T(1) - (T(2) * (zz + xx)), T(2) * (yz + xw), T(0),
			T(2) * (zx + yw), T(2) * (yz - xw), T(1) - (T(2) * (yy + xx)), T(0),
			T(0), T(0), T(0), T(1)
		);
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::RotationAxisAngle(const TVector3<T>& axis, const TRadian<T>& angle)
	{
		T sin = Math::Sin(angle);
		T cos = Math::Cos(angle);
		T a = T(1) - cos;

		T ab = axis.x * axis.y * a;
		T bc = axis.y * axis.z * a;
		T ca = axis.z * axis.x * a;
		T tx = axis.x * axis.x;
		T ty = axis.y * axis.y;
		T tz = axis.z * axis.z;

		return TMatrix4
		(
			tx + cos * (T(1) - tx), ab + axis.z * sin, ca - axis.y * sin, T(0),
			ab - axis.z * sin, ty + cos * (T(1) - ty), bc + axis.x * sin, T(0),
			ca + axis.y * sin, bc - axis.x * sin, tz + cos * (T(1) - tz), T(0),
			T(0), T(0), T(0), T(1)
		);
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::RotationYawPitchRoll(const TRadian<T>& yaw, const TRadian<T>& pitch, const TRadian<T>& roll)
	{
		TQuaternion<T> value = TQuaternion<T>::YawPitchRoll(yaw, pitch, roll);
		return TMatrix4::RotationQuaternion(value);
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::Scaling(T x, T y, T z)
	{
		return TMatrix4
		(
			x,    T(0), T(0), T(0),
			T(0), y,    T(0), T(0),
			T(0), T(0), z,    T(0),
			T(0), T(0), T(0), T(1)
		);
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::Scaling(const TVector3<T>& v)
	{
		return Scaling(v.x, v.y, v.z);
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::Scaling(T u)
	{
		return Scaling(u, u, u);
	}

	template <typename T>
	TMatrix3<T> Rotation(const TQuaternion<T>& q)
	{
		T tx = q.x + q.x;
		T ty = q.y + q.y;
		T tz = q.z + q.z;
		T twx = tx * q.w;
		T twy = ty * q.w;
		T twz = tz * q.w;
		T txx = tx * q.x;
		T txy = ty * q.x;
		T txz = tz * q.x;
		T tyy = ty * q.y;
		T tyz = tz * q.y;
		T tzz = tz * q.z;

		return TMatrix3
		(
			T(1) - (tyy + tzz), txy - twz, txz + twy,
			txy + twz, T(1) - (txx + tzz), tyz - twx,
			txz - twy, tyz + twx, T(1) - (txx + tyy)
		);
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::Transformation(const TVector3<T>& translation, const TQuaternion<T>& rotation, const TVector3<T>& scale)
	{
		TMatrix3<T> rot = Rotation(rotation);

		return TMatrix4
		(
			scale.x * rot(0, 0), scale.y * rot(0, 1), scale.z * rot(0, 2), translation.x,
			scale.x * rot(1, 0), scale.y * rot(1, 1), scale.z * rot(1, 2), translation.y,
			scale.x * rot(2, 0), scale.y * rot(2, 1), scale.z * rot(2, 2), translation.z,
			T(0), T(0), T(0), T(1)
		);
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::LookAt(const TVector3<T>& from, const TVector3<T>& to, const TVector3<T>& up)
	{
		TVector3<T> z = (from - to).Normalized();
		TVector3<T> x = TVector3<T>::Cross(up, z).Normalized();
		TVector3<T> y = TVector3<T>::Cross(z, x).Normalized();

		return TMatrix4
		(
			x.x,  x.y,  x.z,  -TVector3<T>::Dot(x, from),
			y.x,  y.y,  y.z,  -TVector3<T>::Dot(y, from),
			z.x,  z.y,  z.z,  -TVector3<T>::Dot(z, from),
			T(0), T(0), T(0),  T(1)
		);
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::Perspective(const TRadian<T>& fov, T aspectRatio, T nearClip, T farClip)
	{
		T height = T(1) / Math::Tan(fov / T(2));
		T width = height / aspectRatio;
		T range = farClip / (nearClip - farClip);

		return TMatrix4
		(
			width, T(0),   T(0),  T(0),
			T(0),  height, T(0),  T(0),
			T(0),  T(0),   range, range * nearClip,
			T(0),  T(0),   T(-1), T(0)
		);
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::Perspective(T left, T right, T bottom, T top, T near, T far)
	{
		// TODO: Implement this.
		return TMatrix4();
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::Orthographic(T width, T height, T nearClip, T farClip)
	{
		T range = T(1) / (nearClip - farClip);

		return TMatrix4
		(
			T(2) / width, T(0),          T(0),  T(0),
			T(0),         T(2) / height, T(0),  T(0),
			T(0),         T(0),          range, range * nearClip,
			T(0),         T(0),          T(0),  T(1)
		);
	}

	template<typename T>
	TMatrix4<T> TMatrix4<T>::Orthographic(T left, T right, T bottom, T top, T near, T far)
	{
		// TODO: Implement this.
		return TMatrix4();
	}

	// Getters & Setters

	template <typename T>
	TVector4<T> TMatrix4<T>::GetRow(int i) const
	{
		FM_ASSERT(i < 4);
		return TVector4<T>(m[i][0], m[i][1], m[i][2], m[i][3]);
	}

	template <typename T>
	TVector4<T> TMatrix4<T>::GetColumn(int i) const
	{
		FM_ASSERT(i < 4);
		return TVector4<T>(m[0][i], m[1][i], m[2][i], m[3][i]);
	}

	template <typename T>
	void TMatrix4<T>::SetRow(int i, const TVector4<T>& v)
	{
		FM_ASSERT(i < 4);

		m[i][0] = v.x;
		m[i][1] = v.y;
		m[i][2] = v.z;
		m[i][3] = v.w;
	}

	template <typename T>
	void TMatrix4<T>::SetColumn(int i, const TVector4<T>& v)
	{
		FM_ASSERT(i < 4);

		m[0][i] = v.x;
		m[1][i] = v.y;
		m[2][i] = v.z;
		m[3][i] = v.w;
	}

	// Operators

	template <typename T>
	T& TMatrix4<T>::operator() (unsigned int row, unsigned int col)
	{
		FM_ASSERT(row < 4 && col < 4);
		return m[row][col];
	}

	template <typename T>
	const T& TMatrix4<T>::operator() (unsigned int row, unsigned int col) const
	{
		FM_ASSERT(row < 4 && col < 4);
		return m[row][col];
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::operator- () const
	{
		TMatrix4 r;

		for (int i = 0; i < 16; i++) r.elements[i] = -elements[i];

		return r;
	}

	template <typename T>
	TMatrix4<T> operator* (T lhs, const TMatrix4<T>& rhs)
	{
		TMatrix4 r;

		for (int i = 0; i < 16; i++) r.elements[i] = lhs * rhs.elements[i];

		return r;
	}

	// Arithmetic operators

	template <typename T>
	TMatrix4<T> TMatrix4<T>::operator+ (const TMatrix4& rhs) const
	{
		TMatrix4 r;

		for (int i = 0; i < 16; i++) r.elements[i] = elements[i] + rhs.elements[i];

		return r;
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::operator- (const TMatrix4& rhs) const
	{
		TMatrix4 r;

		for (int i = 0; i < 16; i++) r.elements[i] = elements[i] - rhs.elements[i];

		return r;
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::operator* (const TMatrix4& rhs) const
	{
		TMatrix4 r;

		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				T sum = T(0);

				for (int i = 0; i < 4; i++)
				{
					sum += m[row][i] * rhs(i, col);
				}

				r(row, col) = sum;
			}
		}

		return r;
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::operator* (T rhs) const
	{
		TMatrix4 r;

		for (int i = 0; i < 16; i++) r.elements[i] = elements[i] * rhs;

		return r;
	}

	template <typename T>
	TMatrix4<T> TMatrix4<T>::operator/ (T rhs) const
	{
		TMatrix4 r;

		for (int i = 0; i < 16; i++) r.elements[i] = elements[i] / rhs;

		return r;
	}

	// Assignment operators

	template <typename T>
	TMatrix4<T>& TMatrix4<T>::operator+= (const TMatrix4& rhs)
	{
		return *this = *this + rhs;
	}

	template <typename T>
	TMatrix4<T>& TMatrix4<T>::operator-= (const TMatrix4& rhs)
	{
		return *this = *this - rhs;
	}

	template <typename T>
	TMatrix4<T>& TMatrix4<T>::operator*= (const TMatrix4& rhs)
	{
		return *this = *this * rhs;
	}

	template <typename T>
	TMatrix4<T>& TMatrix4<T>::operator*= (T rhs)
	{
		return *this = *this * rhs;
	}

	template <typename T>
	TMatrix4<T>& TMatrix4<T>::operator/= (T rhs)
	{
		return *this = *this / rhs;
	}

	// Relational operators

	template <typename T>
	bool TMatrix4<T>::operator== (const TMatrix4& rhs) const
	{
		return (Memory::Memcmp(this, &rhs, sizeof(TMatrix4)) == 0);
	}

	template <typename T>
	bool TMatrix4<T>::operator!= (const TMatrix4& rhs) const
	{
		return (Memory::Memcmp(this, &rhs, sizeof(TMatrix4)) != 0);
	}

	// Template instantiation

	template class TMatrix4<float>;
	template class TMatrix4<double>;
	template class TMatrix4<int>;
}

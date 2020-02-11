// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Matrix3.h"

#include "Functions.h"
#include "Radian.h"
#include "Vector2.h"
#include "Vector3.h"

#include "../Assert.h"
#include "../Memory.h"

namespace FM
{
	// Constructors

	template <typename T>
	TMatrix3<T>::TMatrix3()
		: elements {
			T(0), T(0), T(0),
			T(0), T(0), T(0),
			T(0), T(0), T(0)
		}
	{}

	template <typename T>
	TMatrix3<T>::TMatrix3(T d)
		: elements {
			T(d), T(0), T(0),
			T(0), T(d), T(0),
			T(0), T(0), T(d)
		}
	{}

	template <typename T>
	TMatrix3<T>::TMatrix3(const T* elements)
	{
		Memory::Memcpy(m, elements, 9 * sizeof(T));
	}

	template <typename T>
	TMatrix3<T>::TMatrix3
	(
		const TVector3<T>& r0,
		const TVector3<T>& r1,
		const TVector3<T>& r2
	)
		: elements {
			r0.x, r0.y, r0.z,
			r1.x, r1.y, r1.z,
			r2.x, r2.y, r2.z
		}
	{}

	template <typename T>
	TMatrix3<T>::TMatrix3
	(
		T m00, T m01, T m02,
		T m10, T m11, T m12,
		T m20, T m21, T m22
	)
		: elements {
			m00, m01, m02,
			m10, m11, m12,
			m20, m21, m22
		}
	{}

	// Predefined matrices

	template <typename T>
	const TMatrix3<T> TMatrix3<T>::Zero(T(0));

	template <typename T>
	const TMatrix3<T> TMatrix3<T>::Identity(T(1));

	// Calculations

	template <typename T>
	T TMatrix3<T>::Determinant() const
	{
		return
		(
			m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) +
			m[0][1] * (m[1][2] * m[2][0] - m[1][0] * m[2][2]) +
			m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0])
		);
	}

	template <typename T>
	TMatrix3<T> TMatrix3<T>::Inverted() const
	{
		T det = Determinant();

		T m11 = m[1][1] * m[2][2] - m[1][2] * m[2][1];
		T m12 = m[0][2] * m[2][1] - m[0][1] * m[2][2];
		T m13 = m[0][1] * m[1][2] - m[0][2] * m[1][1];

		T m21 = m[1][2] * m[2][0] - m[1][0] * m[2][2];
		T m22 = m[0][0] * m[2][2] - m[0][2] * m[2][0];
		T m23 = m[0][2] * m[1][0] - m[0][0] * m[1][2];

		T m31 = m[1][0] * m[2][1] - m[1][1] * m[2][0];
		T m32 = m[0][1] * m[2][0] - m[0][0] * m[2][1];
		T m33 = m[0][0] * m[1][1] - m[0][1] * m[1][0];

		T invdet = T(1) / det;

		return TMatrix3
		(
			m11 * invdet, m12 * invdet, m13 * invdet,
			m21 * invdet, m22 * invdet, m23 * invdet,
			m31 * invdet, m32 * invdet, m33 * invdet
		);
	}

	template <typename T>
	TMatrix3<T> TMatrix3<T>::Transposed() const
	{
		return TMatrix3
		(
			m[0][0], m[1][0], m[2][0],
			m[0][1], m[1][1], m[2][1],
			m[0][2], m[1][2], m[2][2]
		);
	}

	template <typename T>
	TMatrix3<T> TMatrix3<T>::Translation(T x, T y)
	{
		return TMatrix3
		(
			T(1), T(0), x,
			T(0), T(1), y,
			T(0), T(0), T(1)
		);
	}

	template <typename T>
	TMatrix3<T> TMatrix3<T>::Translation(const TVector2<T>& v)
	{
		return Translation(v.x, v.y);
	}

	template <typename T>
	TMatrix3<T> TMatrix3<T>::Rotation(const TRadian<T>& r)
	{
		T cos = Math::Cos(r);
		T sin = Math::Sin(r);

		return TMatrix3
		(
			cos,  -sin,  T(0),
			sin,   cos,  T(0),
			T(0),  T(0), T(1)
		);
	}

	template <typename T>
	TMatrix3<T> TMatrix3<T>::Scaling(T x, T y)
	{
		return TMatrix3
		(
			x,    T(0), T(0),
			T(0), y,    T(0),
			T(0), T(0), T(1)
		);
	}

	template <typename T>
	TMatrix3<T> TMatrix3<T>::Scaling(const TVector2<T>& v)
	{
		return Scaling(v.x, v.y);
	}

	template <typename T>
	TMatrix3<T> TMatrix3<T>::Scaling(T u)
	{
		return Scaling(u, u);
	}

	template <typename T>
	TMatrix3<T> TMatrix3<T>::Skewing(T x, T y)
	{
		return TMatrix3
		(
			T(1), x,    T(0),
			y,    T(1), T(0),
			T(0), T(0), T(1)
		);
	}

	template <typename T>
	TMatrix3<T> TMatrix3<T>::Skewing(const TVector2<T>& v)
	{
		return Skewing(v.x, v.y);
	}

	// Getters & Setters

	template <typename T>
	TVector3<T> TMatrix3<T>::GetRow(int i) const
	{
		FM_ASSERT(i < 3);
		return TVector3<T>(m[i][0], m[i][1], m[i][2]);
	}

	template <typename T>
	TVector3<T> TMatrix3<T>::GetColumn(int i) const
	{
		FM_ASSERT(i < 3);
		return TVector3<T>(m[0][i], m[1][i], m[2][i]);
	}

	template <typename T>
	void TMatrix3<T>::SetRow(int i, const TVector3<T>& v)
	{
		FM_ASSERT(i < 3);

		m[i][0] = v.x;
		m[i][1] = v.y;
		m[i][2] = v.z;
	}

	template <typename T>
	void TMatrix3<T>::SetColumn(int i, const TVector3<T>& v)
	{
		FM_ASSERT(i < 3);

		m[0][i] = v.x;
		m[1][i] = v.y;
		m[2][i] = v.z;
	}

	// Operators

	template <typename T>
	T& TMatrix3<T>::operator() (unsigned int row, unsigned int col)
	{
		FM_ASSERT(row < 3 && col < 3);
		return m[row][col];
	}

	template <typename T>
	const T& TMatrix3<T>::operator() (unsigned int row, unsigned int col) const
	{
		FM_ASSERT(row < 3 && col < 3);
		return m[row][col];
	}

	template <typename T>
	TMatrix3<T> TMatrix3<T>::operator- () const
	{
		TMatrix3 r;

		for (int i = 0; i < 9; i++) r.elements[i] = -elements[i];

		return r;
	}
	
	template <typename T>
	TMatrix3<T> operator* (T lhs, const TMatrix3<T>& rhs)
	{
		TMatrix3 r;

		for (int i = 0; i < 9; i++) r.elements[i] = lhs * rhs.elements[i];

		return r;
	}

	// Arithmetic operators

	template <typename T>
	TMatrix3<T> TMatrix3<T>::operator+ (const TMatrix3& rhs) const
	{
		TMatrix3 r;

		for (int i = 0; i < 9; i++) r.elements[i] = elements[i] + rhs.elements[i];

		return r;
	}

	template <typename T>
	TMatrix3<T> TMatrix3<T>::operator- (const TMatrix3& rhs) const
	{
		TMatrix3 r;

		for (int i = 0; i < 9; i++) r.elements[i] = elements[i] - rhs.elements[i];

		return r;
	}

	template <typename T>
	TMatrix3<T> TMatrix3<T>::operator* (const TMatrix3& rhs) const
	{
		TMatrix3 r;

		for (int row = 0; row < 3; row++)
		{
			for (int col = 0; col < 3; col++)
			{
				T sum = T(0);

				for (int i = 0; i < 3; i++)
				{
					sum += m[row][i] * rhs(i, col);
				}

				r(row, col) = sum;
			}
		}

		return r;
	}

	template<typename T>
	TVector3<T> TMatrix3<T>::operator*(const TVector3<T>& rhs) const
	{
		return TVector3
		(
			rhs.x * m[0][0] + rhs.y * m[1][0] + rhs.z * m[2][0],
			rhs.x * m[0][1] + rhs.y * m[1][1] + rhs.z * m[2][1],
			rhs.x * m[0][2] + rhs.y * m[1][2] + rhs.z * m[2][2]
		);
	}

	template <typename T>
	TMatrix3<T> TMatrix3<T>::operator* (T rhs) const
	{
		TMatrix3 r;

		for (int i = 0; i < 9; i++) r.elements[i] = elements[i] * rhs;

		return r;
	}

	template <typename T>
	TMatrix3<T> TMatrix3<T>::operator/ (T rhs) const
	{
		TMatrix3 r;

		for (int i = 0; i < 9; i++) r.elements[i] = elements[i] / rhs;

		return r;
	}

	// Assignment operators

	template <typename T>
	TMatrix3<T>& TMatrix3<T>::operator+= (const TMatrix3& rhs)
	{
		return *this = *this + rhs;
	}

	template <typename T>
	TMatrix3<T>& TMatrix3<T>::operator-= (const TMatrix3& rhs)
	{
		return *this = *this - rhs;
	}

	template <typename T>
	TMatrix3<T>& TMatrix3<T>::operator*= (const TMatrix3& rhs)
	{
		return *this = *this * rhs;
	}

	template <typename T>
	TMatrix3<T>& TMatrix3<T>::operator*= (T rhs)
	{
		return *this = *this * rhs;
	}

	template <typename T>
	TMatrix3<T>& TMatrix3<T>::operator/= (T rhs)
	{
		return *this = *this / rhs;
	}

	// Relational operators

	template <typename T>
	bool TMatrix3<T>::operator== (const TMatrix3& rhs) const
	{
		return (Memory::Memcmp(this, &rhs, sizeof(TMatrix3)) == 0);
	}

	template <typename T>
	bool TMatrix3<T>::operator!= (const TMatrix3& rhs) const
	{
		return (Memory::Memcmp(this, &rhs, sizeof(TMatrix3)) != 0);
	}

	// Template instantiation

	template class TMatrix3<float>;
	template class TMatrix3<double>;
	template class TMatrix3<int>;
}

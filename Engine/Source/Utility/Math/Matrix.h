// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../CoreTypes.h"
#include "Vector.h"

namespace FM
{
	/// RxC Matrix in a row-major format.

	template <typename T, uint R, uint C>
	struct TMatrix
	{
		union {
			T data[R * C]{ 0 };	///< Interpreted as [row * C + column]
			T m[R][C];			///< Interpreted as [row][column]
		};

		constexpr TMatrix() = default;

		constexpr explicit TMatrix(const T& t)
		{
			for (uint r = 0; r < R; r++) {
				for (uint c = 0; c < C; c++) {
					m[r][c] = (r == c) ? t : T(0);
				}
			}
		}

		template <typename ...Ts>
		constexpr explicit TMatrix(const T& t, const Ts&... ts) : data{ t, ts... }
		{
			static_assert(sizeof...(ts) + 1 == R * C);
		}

		template <typename ...Vs>
		constexpr explicit TMatrix(const TVector<T, C> v, const Vs&... vs) : m{ v, vs... }
		{
			static_assert(sizeof...(vs) + 1 == R);
		}

		template <uint R2, uint C2>
		constexpr TMatrix(const TMatrix<T, R2, C2>& other)
		{
			for (int r = 0; r < R; r++) {
				for (int c = 0; c < C; c++) {
					m[r][c] = (r < R2 && c < C2) ? other(r, c) : (r == c ? T(1) : T(0));
				}
			}
		}

		static const TMatrix Zero;
		static const TMatrix Identity;

		inline constexpr T& operator() (usize row, usize col) { return m[row][col]; }
		inline constexpr const T& operator() (usize row, usize col) const { return m[row][col]; }

		inline constexpr T& operator[] (usize i) { return data[i]; }
		inline constexpr const T& operator[] (usize i) const { return data[i]; }

		inline constexpr usize Rows() const { return R; }
		inline constexpr usize Cols() const { return C; }
		inline constexpr usize Size() const { return Rows() * Cols(); }
	};

	// Standard matrices

	template <typename T, uint R, uint C>
	const TMatrix<T, R, C> TMatrix<T, R, C>::Zero(T(0));

	template <typename T, uint R, uint C>
	const TMatrix<T, R, C> TMatrix<T, R, C>::Identity(T(1));

	// Arithmetic operators

	template <typename T, uint R, uint C>
	inline constexpr TMatrix<T, R, C> operator+ (const TMatrix<T, R, C>& lhs, const TMatrix<T, R, C>& rhs)
	{
		TMatrix<T, R, C> r;
		for (int i = 0; i < R * C; i++) r[i] = lhs[i] + rhs[i];
		return r;
	}

	template <typename T, uint R, uint C>
	inline constexpr TMatrix<T, R, C> operator- (const TMatrix<T, R, C>& lhs, const TMatrix<T, R, C>& rhs)
	{
		TMatrix<T, R, C> r;
		for (int i = 0; i < R * C; i++) r[i] = lhs[i] - rhs[i];
		return r;
	}

	template <typename T, uint R, uint C, uint CR>
	inline constexpr TMatrix<T, R, C> operator* (const TMatrix<T, R, CR>& lhs, const TMatrix<T, CR, C>& rhs)
	{
		TMatrix<T, R, C> r;

		for (int row = 0; row < R; row++)
		{
			for (int col = 0; col < C; col++)
			{
				for (int i = 0; i < CR; i++)
				{
					r(row, col) += lhs(row, i) * rhs(i, col);
				}
			}
		}

		return r;
	}

	template <typename T, uint R, uint C>
	inline constexpr TMatrix<T, R, C> operator* (const TMatrix<T, R, C>& lhs, const T& rhs)
	{
		TMatrix<T, R, C> r;
		for (int i = 0; i < R * C; i++) r[i] = lhs[i] * rhs;
		return r;
	}

	template <typename T, uint R, uint C>
	inline constexpr TMatrix<T, R, C> operator/ (const TMatrix<T, R, C>& lhs, const T& rhs)
	{
		TMatrix<T, R, C> r;
		for (int i = 0; i < R * C; i++) r[i] = lhs[i] / rhs;
		return r;
	}

	// Assignment operators

	template <typename T, uint R, uint C>
	inline constexpr TMatrix<T, R, C> operator+= (TMatrix<T, R, C>& lhs, const TMatrix<T, R, C>& rhs) {
		return lhs = lhs + rhs;
	}

	template <typename T, uint R, uint C>
	inline constexpr TMatrix<T, R, C> operator-= (TMatrix<T, R, C>& lhs, const TMatrix<T, R, C>& rhs) {
		return lhs = lhs - rhs;
	}

	template <typename T, uint R, uint C>
	inline constexpr TMatrix<T, R, C> operator*= (TMatrix<T, R, C>& lhs, const TMatrix<T, R, C>& rhs) {
		return lhs = lhs * rhs;
	}

	template <typename T, uint R, uint C>
	inline constexpr TMatrix<T, R, C> operator*= (TMatrix<T, R, C>& lhs, const T& rhs) {
		return lhs = lhs * rhs;
	}

	template <typename T, uint R, uint C>
	inline constexpr TMatrix<T, R, C> operator/= (TMatrix<T, R, C>& lhs, const T& rhs) {
		return lhs = lhs / rhs;
	}

	// Relational operators

	template <typename T, uint R, uint C>
	inline constexpr TMatrix<T, R, C> operator== (const TMatrix<T, R, C>& lhs, const TMatrix<T, R, C>& rhs)
	{
		for (int i = 0; i < R * C; i++) if (lhs[i] != rhs[i]) return false;
		return true;
	}

	// Type aliases

	template <typename T> using TMatrix2 = TMatrix<T, 2, 2>;
	template <typename T> using TMatrix3 = TMatrix<T, 3, 3>;
	template <typename T> using TMatrix4 = TMatrix<T, 4, 4>;

	using Matrix2 = TMatrix2<float>;
	using Matrix3 = TMatrix3<float>;
	using Matrix4 = TMatrix4<float>;

	// Calculations

	namespace Math
	{
		template <typename T, uint R, uint C>
		TVector<T, C> Row(const TMatrix<T, R, C>& matrix, int i)
		{
			TVector<T, C> row;
			for (int c = 0; c < C; c++) row[c] = matrix(i, c);
			return row;
		}

		template <typename T, uint R, uint C>
		void Row(TMatrix<T, R, C>& matrix, int i, const TVector<T, C>& row)
		{
			for (int c = 0; c < C; c++) matrix(i, c) = row[c];
		}

		template <typename T, uint R, uint C>
		TVector<T, R> Column(const TMatrix<T, R, C>& matrix, int i)
		{
			TVector<T, R> column;
			for (int r = 0; r < R; r++) column[r] = matrix(r, i);
			return column;
		}

		template <typename T, uint R, uint C>
		void Column(TMatrix<T, R, C>& matrix, int i, const TVector<T, R>& column)
		{
			for (int r = 0; r < R; r++) matrix(r, i) = column[r];
		}

		template <typename T, uint R, uint C>
		inline constexpr TMatrix<T, C, R> Transpose(const TMatrix<T, R, C>& m)
		{
			TMatrix<T, C, R> transposed;

			for (int r = 0; r < R; r++)
			{
				for (int c = 0; c < C; c++)
				{
					transposed(c, r) = m(r, c);
				}
			}

			return transposed;
		}

		template<typename T>
		constexpr T Determinant(const TMatrix3<T>& m)
		{
			return
			(
				m(0, 0) * (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1)) +
				m(0, 1) * (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2)) +
				m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0))
			);
		}

		template<typename T>
		constexpr T Determinant(const TMatrix4<T>& m)
		{
			return
			(
				m(0, 0) * m(1, 1) * m(2, 2) * m(3, 3) + m(0, 0) * m(1, 2) * m(2, 3) * m(3, 1) +
				m(0, 0) * m(1, 3) * m(2, 1) * m(3, 2) + m(0, 1) * m(1, 0) * m(2, 3) * m(3, 2) +
				m(0, 1) * m(1, 2) * m(2, 0) * m(3, 3) + m(0, 1) * m(1, 3) * m(2, 2) * m(3, 0) +
				m(0, 2) * m(1, 0) * m(2, 1) * m(3, 3) + m(0, 2) * m(1, 1) * m(2, 3) * m(3, 0) +
				m(0, 2) * m(1, 3) * m(2, 0) * m(3, 1) + m(0, 3) * m(1, 0) * m(2, 2) * m(3, 1) +
				m(0, 3) * m(1, 1) * m(2, 0) * m(3, 2) + m(0, 3) * m(1, 2) * m(2, 1) * m(3, 0) -
				m(0, 0) * m(1, 1) * m(2, 3) * m(3, 2) - m(0, 0) * m(1, 2) * m(2, 1) * m(3, 3) -
				m(0, 0) * m(1, 3) * m(2, 2) * m(3, 1) - m(0, 1) * m(1, 0) * m(2, 2) * m(3, 3) -
				m(0, 1) * m(1, 2) * m(2, 3) * m(3, 0) - m(0, 1) * m(1, 3) * m(2, 0) * m(3, 2) -
				m(0, 2) * m(1, 0) * m(2, 3) * m(3, 1) - m(0, 2) * m(1, 1) * m(2, 0) * m(3, 3) -
				m(0, 2) * m(1, 3) * m(2, 1) * m(3, 0) - m(0, 3) * m(1, 0) * m(2, 1) * m(3, 2) -
				m(0, 3) * m(1, 1) * m(2, 2) * m(3, 0) - m(0, 3) * m(1, 2) * m(2, 0) * m(3, 1)
			);
		}

		template<typename T>
		constexpr TMatrix3<T> Inverted(const TMatrix3<T>& m)
		{
			T invDet = T(1) / Determinant(m);

			T m11 = m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1);
			T m12 = m(0, 2) * m(2, 1) - m(0, 1) * m(2, 2);
			T m13 = m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1);

			T m21 = m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2);
			T m22 = m(0, 0) * m(2, 2) - m(0, 2) * m(2, 0);
			T m23 = m(0, 2) * m(1, 0) - m(0, 0) * m(1, 2);

			T m31 = m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0);
			T m32 = m(0, 1) * m(2, 0) - m(0, 0) * m(2, 1);
			T m33 = m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);

			return TMatrix3<T>
			(
				m11 * invDet, m12 * invDet, m13 * invDet,
				m21 * invDet, m22 * invDet, m23 * invDet,
				m31 * invDet, m32 * invDet, m33 * invDet
			);
		}

		template<typename T>
		constexpr TMatrix4<T> Inverted(const TMatrix4<T>& m)
		{
			T invDet = T(1) / Determinant(m);

			T m11 = m(1, 1) * m(2, 2) * m(3, 3) + m(1, 2) * m(2, 3) * m(3, 1) + m(1, 3) * m(2, 1) * m(3, 2) - m(1, 1) * m(2, 3) * m(3, 2) - m(1, 2) * m(2, 1) * m(3, 3) - m(1, 3) * m(2, 2) * m(3, 1);
			T m12 = m(0, 1) * m(2, 3) * m(3, 2) + m(0, 2) * m(2, 1) * m(3, 3) + m(0, 3) * m(2, 2) * m(3, 1) - m(0, 1) * m(2, 2) * m(3, 3) - m(0, 2) * m(2, 3) * m(3, 1) - m(0, 3) * m(2, 1) * m(3, 2);
			T m13 = m(0, 1) * m(1, 2) * m(3, 3) + m(0, 2) * m(1, 3) * m(3, 1) + m(0, 3) * m(1, 1) * m(3, 2) - m(0, 1) * m(1, 3) * m(3, 2) - m(0, 2) * m(1, 1) * m(3, 3) - m(0, 3) * m(1, 2) * m(3, 1);
			T m14 = m(0, 1) * m(1, 3) * m(2, 2) + m(0, 2) * m(1, 1) * m(2, 3) + m(0, 3) * m(1, 2) * m(2, 1) - m(0, 1) * m(1, 2) * m(2, 3) - m(0, 2) * m(1, 3) * m(2, 1) - m(0, 3) * m(1, 1) * m(2, 2);
			
			T m21 = m(1, 0) * m(2, 3) * m(3, 2) + m(1, 2) * m(2, 0) * m(3, 3) + m(1, 3) * m(2, 2) * m(3, 0) - m(1, 0) * m(2, 2) * m(3, 3) - m(1, 2) * m(2, 3) * m(3, 0) - m(1, 3) * m(2, 0) * m(3, 2);
			T m22 = m(0, 0) * m(2, 2) * m(3, 3) + m(0, 2) * m(2, 3) * m(3, 0) + m(0, 3) * m(2, 0) * m(3, 2) - m(0, 0) * m(2, 3) * m(3, 2) - m(0, 2) * m(2, 0) * m(3, 3) - m(0, 3) * m(2, 2) * m(3, 0);
			T m23 = m(0, 0) * m(1, 3) * m(3, 2) + m(0, 2) * m(1, 0) * m(3, 3) + m(0, 3) * m(1, 2) * m(3, 0) - m(0, 0) * m(1, 2) * m(3, 3) - m(0, 2) * m(1, 3) * m(3, 0) - m(0, 3) * m(1, 0) * m(3, 2);
			T m24 = m(0, 0) * m(1, 2) * m(2, 3) + m(0, 2) * m(1, 3) * m(2, 0) + m(0, 3) * m(1, 0) * m(2, 2) - m(0, 0) * m(1, 3) * m(2, 2) - m(0, 2) * m(1, 0) * m(2, 3) - m(0, 3) * m(1, 2) * m(2, 0);
			
			T m31 = m(1, 0) * m(2, 1) * m(3, 3) + m(1, 1) * m(2, 3) * m(3, 0) + m(1, 3) * m(2, 0) * m(3, 1) - m(1, 0) * m(2, 3) * m(3, 1) - m(1, 1) * m(2, 0) * m(3, 3) - m(1, 3) * m(2, 1) * m(3, 0);
			T m32 = m(0, 0) * m(2, 3) * m(3, 1) + m(0, 1) * m(2, 0) * m(3, 3) + m(0, 3) * m(2, 1) * m(3, 0) - m(0, 0) * m(2, 1) * m(3, 3) - m(0, 1) * m(2, 3) * m(3, 0) - m(0, 3) * m(2, 0) * m(3, 1);
			T m33 = m(0, 0) * m(1, 1) * m(3, 3) + m(0, 1) * m(1, 3) * m(3, 0) + m(0, 3) * m(1, 0) * m(3, 1) - m(0, 0) * m(1, 3) * m(3, 1) - m(0, 1) * m(1, 0) * m(3, 3) - m(0, 3) * m(1, 1) * m(3, 0);
			T m34 = m(0, 0) * m(1, 3) * m(2, 1) + m(0, 1) * m(1, 0) * m(2, 3) + m(0, 3) * m(1, 1) * m(2, 0) - m(0, 0) * m(1, 1) * m(2, 3) - m(0, 1) * m(1, 3) * m(2, 0) - m(0, 3) * m(1, 0) * m(2, 1);
			
			T m41 = m(1, 0) * m(2, 2) * m(3, 1) + m(1, 1) * m(2, 0) * m(3, 2) + m(1, 2) * m(2, 1) * m(3, 0) - m(1, 0) * m(2, 1) * m(3, 2) - m(1, 1) * m(2, 2) * m(3, 0) - m(1, 2) * m(2, 0) * m(3, 1);
			T m42 = m(0, 0) * m(2, 1) * m(3, 2) + m(0, 1) * m(2, 2) * m(3, 0) + m(0, 2) * m(2, 0) * m(3, 1) - m(0, 0) * m(2, 2) * m(3, 1) - m(0, 1) * m(2, 0) * m(3, 2) - m(0, 2) * m(2, 1) * m(3, 0);
			T m43 = m(0, 0) * m(1, 2) * m(3, 1) + m(0, 1) * m(1, 0) * m(3, 2) + m(0, 2) * m(1, 1) * m(3, 0) - m(0, 0) * m(1, 1) * m(3, 2) - m(0, 1) * m(1, 2) * m(3, 0) - m(0, 2) * m(1, 0) * m(3, 1);
			T m44 = m(0, 0) * m(1, 1) * m(2, 2) + m(0, 1) * m(1, 2) * m(2, 0) + m(0, 2) * m(1, 0) * m(2, 1) - m(0, 0) * m(1, 2) * m(2, 1) - m(0, 1) * m(1, 0) * m(2, 2) - m(0, 2) * m(1, 1) * m(2, 0);

			return TMatrix4<T>
			(
				m11 * invDet, m12 * invDet, m13 * invDet, m14 * invDet,
				m21 * invDet, m22 * invDet, m23 * invDet, m24 * invDet,
				m31 * invDet, m32 * invDet, m33 * invDet, m34 * invDet,
				m41 * invDet, m42 * invDet, m43 * invDet, m44 * invDet
			);
		}
	}
}

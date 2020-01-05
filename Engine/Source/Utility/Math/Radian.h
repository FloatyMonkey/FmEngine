// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

namespace FM
{
	template <typename T> class TDegree;

	/// Wrapper class which indicates a given angle is in radians.
	/// @note TRadian values are interchangeable with Degree values, and conversions will be done automatically between them.

	template <typename T>
	class TRadian
	{
	private:

		T mRad;

	public:

		// Constructors

		explicit TRadian(T r = T(0));
		TRadian(const TDegree<T>& d);

		// Assignments

		TRadian& operator= (const T& x);
		TRadian& operator= (const TRadian& r);
		TRadian& operator= (const TDegree<T>& d);

		// Getters

		/// Get the value of the angle in radians.
		T Rad() const;

		/// Get the value of the angle in degrees.
		T Deg() const;

		// Calculations

		/// Map an angle to the [-pi, pi] range.
		TRadian NormalizePi() const;

		/// Map an angle to the [0, 2pi] range.
		TRadian Normalize2Pi() const;

		/// Calculate the complement (1/2 pi - a).
		TRadian Complement() const;

		/// Calculate the supplement (pi - a).
		TRadian Supplement() const;

		/// Calculate the antisupplement (pi + a).
		TRadian Antisupplement() const;

		// Arithmetic operators

		TRadian operator+ (const TRadian& rhs) const;
		TRadian operator- (const TRadian& rhs) const;
		TRadian operator* (const TRadian& rhs) const;
		TRadian operator/ (const TRadian& rhs) const;

		TRadian operator+ (const TDegree<T>& rhs) const;
		TRadian operator- (const TDegree<T>& rhs) const;
		TRadian operator* (const TDegree<T>& rhs) const;
		TRadian operator/ (const TDegree<T>& rhs) const;

		TRadian operator* (T rhs) const;
		TRadian operator/ (T rhs) const;

		// Assignment operators

		TRadian& operator+= (const TRadian& rhs);
		TRadian& operator-= (const TRadian& rhs);
		TRadian& operator*= (const TRadian& rhs);
		TRadian& operator/= (const TRadian& rhs);

		TRadian& operator+= (const TDegree<T>& rhs);
		TRadian& operator-= (const TDegree<T>& rhs);
		TRadian& operator*= (const TDegree<T>& rhs);
		TRadian& operator/= (const TDegree<T>& rhs);

		TRadian& operator*= (T rhs);
		TRadian& operator/= (T rhs);

		// Relational operators

		bool operator< (const TRadian& rhs) const;
		bool operator<= (const TRadian& rhs) const;
		bool operator== (const TRadian& rhs) const;
		bool operator!= (const TRadian& rhs) const;
		bool operator>= (const TRadian& rhs) const;
		bool operator> (const TRadian& rhs) const;
	};

	// Type aliases

	using Radian = TRadian<float>;

	using RadianF = TRadian<float>;
	using RadianD = TRadian<double>;
	using RadianI = TRadian<int>;
}

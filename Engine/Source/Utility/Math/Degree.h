// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

namespace FM
{
	template <typename T> class TRadian;

	/// Wrapper class which indicates a given angle is in degrees.
	/// @note TDegree values are interchangeable with Radian values, and conversions will be done automatically between them.

	template <typename T>
	class TDegree
	{
	private:

		T mDeg;

	public:

		// Constructors

		explicit TDegree(T d = T(0));
		TDegree(const TRadian<T>& d);

		// Assignments

		TDegree& operator= (const T& x);
		TDegree& operator= (const TDegree& d);
		TDegree& operator= (const TRadian<T>& r);

		// Getters

		/// Get the value of the angle in degrees.
		T Deg() const;

		/// Get the value of the angle in radians.
		T Rad() const;

		// Calculations

		/// Map an angle to the [-180, 180] range.
		TDegree Normalize180() const;

		/// Map an angle to the [0, 360] range.
		TDegree Normalize360() const;

		/// Calculate the complement (90 - a).
		TDegree Complement() const;

		/// Calculate the supplement (180 - a).
		TDegree Supplement() const;

		/// Calculate the antisupplement (180 + a).
		TDegree AntiSupplement() const;

		// Arithmetic operators

		TDegree operator+ (const TDegree& rhs) const;
		TDegree operator- (const TDegree& rhs) const;
		TDegree operator* (const TDegree& rhs) const;
		TDegree operator/ (const TDegree& rhs) const;

		TDegree operator+ (const TRadian<T>& rhs) const;
		TDegree operator- (const TRadian<T>& rhs) const;
		TDegree operator* (const TRadian<T>& rhs) const;
		TDegree operator/ (const TRadian<T>& rhs) const;

		TDegree operator* (T rhs) const;
		TDegree operator/ (T rhs) const;

		// Assignment operators

		TDegree& operator+= (const TDegree& rhs);
		TDegree& operator-= (const TDegree& rhs);
		TDegree& operator*= (const TDegree& rhs);
		TDegree& operator/= (const TDegree& rhs);

		TDegree& operator+= (const TRadian<T>& rhs);
		TDegree& operator-= (const TRadian<T>& rhs);
		TDegree& operator*= (const TRadian<T>& rhs);
		TDegree& operator/= (const TRadian<T>& rhs);

		TDegree& operator*= (T rhs);
		TDegree& operator/= (T rhs);

		// Relational operators

		bool operator< (const TDegree& rhs) const;
		bool operator<= (const TDegree& rhs) const;
		bool operator== (const TDegree& rhs) const;
		bool operator!= (const TDegree& rhs) const;
		bool operator>= (const TDegree& rhs) const;
		bool operator> (const TDegree& rhs) const;
	};

	// Type aliases

	using Degree = TDegree<float>;

	using DegreeF = TDegree<float>;
	using DegreeD = TDegree<double>;
	using DegreeI = TDegree<int>;
}

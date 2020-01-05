// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Degree.h"

#include "Functions.h"
#include "Radian.h"

namespace FM
{
	// Constructors

	template <typename T>
	TDegree<T>::TDegree(T d)
	{
		mDeg = d;
	}

	template <typename T>
	TDegree<T>::TDegree(const TRadian<T>& r)
	{
		mDeg = r.Deg();
	}

	// Assignments

	template <typename T>
	TDegree<T>& TDegree<T>::operator=(const T& x)
	{
		mDeg = x;
		return *this;
	}

	template <typename T>
	TDegree<T>& TDegree<T>::operator=(const TDegree& d)
	{
		mDeg = d.mDeg;
		return *this;
	}

	template <typename T>
	TDegree<T>& TDegree<T>::operator=(const TRadian<T>& d)
	{
		mDeg = d.Deg();
		return *this;
	}

	// Getters

	template <typename T>
	T TDegree<T>::Deg() const
	{
		return mDeg;
	}

	template <typename T>
	T TDegree<T>::Rad() const
	{
		return mDeg * Math::Deg2Rad<T>;
	}

	// Calculations

	template <typename T>
	TDegree<T> TDegree<T>::Normalize180() const
	{
		T x = Math::Mod(mDeg + T(180), T(360));
		if (x < T(0)) x += T(360);

		return TDegree(x - T(180));
	}

	template <typename T>
	TDegree<T> TDegree<T>::Normalize360() const
	{
		T x = Math::Mod(mDeg, T(360));
		if (x < T(0)) x += T(360);

		return TDegree(x);
	}

	template <typename T>
	TDegree<T> TDegree<T>::Complement() const
	{
		return TDegree(T(90) - mDeg);
	}

	template <typename T>
	TDegree<T> TDegree<T>::Supplement() const
	{
		return TDegree(T(180) - mDeg);
	}

	template <typename T>
	TDegree<T> TDegree<T>::AntiSupplement() const
	{
		return TDegree(T(180) + mDeg);
	}

	// Arithmetic operators

	template <typename T>
	TDegree<T> TDegree<T>::operator+ (const TDegree& rhs) const
	{
		return TDegree(mDeg + rhs.mDeg);
	}

	template <typename T>
	TDegree<T> TDegree<T>::operator- (const TDegree& rhs) const
	{
		return TDegree(mDeg - rhs.mDeg);
	}

	template <typename T>
	TDegree<T> TDegree<T>::operator* (const TDegree& rhs) const
	{
		return TDegree(mDeg * rhs.mDeg);
	}

	template <typename T>
	TDegree<T> TDegree<T>::operator/ (const TDegree& rhs) const
	{
		return TDegree(mDeg / rhs.mDeg);
	}

	template <typename T>
	TDegree<T> TDegree<T>::operator+ (const TRadian<T>& rhs) const
	{
		return TDegree(mDeg + rhs.Deg());
	}

	template <typename T>
	TDegree<T> TDegree<T>::operator- (const TRadian<T>& rhs) const
	{
		return TDegree(mDeg - rhs.Deg());
	}

	template <typename T>
	TDegree<T> TDegree<T>::operator* (const TRadian<T>& rhs) const
	{
		return TDegree(mDeg * rhs.Deg());
	}

	template <typename T>
	TDegree<T> TDegree<T>::operator/ (const TRadian<T>& rhs) const
	{
		return TDegree(mDeg / rhs.Deg());
	}

	template <typename T>
	TDegree<T> TDegree<T>::operator* (T rhs) const
	{
		return TDegree(mDeg * rhs);
	}

	template <typename T>
	TDegree<T> TDegree<T>::operator/ (T rhs) const
	{
		return TDegree(mDeg / rhs);
	}

	// Assignment operators

	template <typename T>
	TDegree<T>& TDegree<T>::operator+= (const TDegree& rhs)
	{
		mDeg += rhs.mDeg; return *this;
	}

	template <typename T>
	TDegree<T>& TDegree<T>::operator-= (const TDegree& rhs)
	{
		mDeg -= rhs.mDeg; return *this;
	}

	template <typename T>
	TDegree<T>& TDegree<T>::operator*= (const TDegree& rhs)
	{
		mDeg *= rhs.mDeg; return *this;
	}

	template <typename T>
	TDegree<T>& TDegree<T>::operator/= (const TDegree& rhs)
	{
		mDeg /= rhs.mDeg; return *this;
	}

	template <typename T>
	TDegree<T>& TDegree<T>::operator+= (const TRadian<T>& rhs)
	{
		mDeg += rhs.Deg(); return *this;
	}

	template <typename T>
	TDegree<T>& TDegree<T>::operator-= (const TRadian<T>& rhs)
	{
		mDeg -= rhs.Deg(); return *this;
	}

	template <typename T>
	TDegree<T>& TDegree<T>::operator*= (const TRadian<T>& rhs)
	{
		mDeg *= rhs.Deg(); return *this;
	}

	template <typename T>
	TDegree<T>& TDegree<T>::operator/= (const TRadian<T>& rhs)
	{
		mDeg /= rhs.Deg(); return *this;
	}

	template <typename T>
	TDegree<T>& TDegree<T>::operator*= (T rhs)
	{
		mDeg *= rhs; return *this;
	}

	template <typename T>
	TDegree<T>& TDegree<T>::operator/= (T rhs)
	{
		mDeg /= rhs; return *this;
	}

	// Relational operators

	template <typename T>
	bool TDegree<T>::operator< (const TDegree& rhs) const
	{
		return mDeg < rhs.mDeg;
	}

	template <typename T>
	bool TDegree<T>::operator<= (const TDegree& rhs) const
	{
		return mDeg <= rhs.mDeg;
	}

	template <typename T>
	bool TDegree<T>::operator== (const TDegree& rhs) const
	{
		return mDeg == rhs.mDeg;
	}

	template <typename T>
	bool TDegree<T>::operator!= (const TDegree& rhs) const
	{
		return mDeg != rhs.mDeg;
	}

	template <typename T>
	bool TDegree<T>::operator>= (const TDegree& rhs) const
	{
		return mDeg >= rhs.mDeg;
	}

	template <typename T>
	bool TDegree<T>::operator> (const TDegree& rhs) const
	{
		return mDeg > rhs.mDeg;
	}

	// Template instantiation

	template class TDegree<float>;
	template class TDegree<double>;
	template class TDegree<int>;
}

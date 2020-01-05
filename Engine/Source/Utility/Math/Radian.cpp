// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Radian.h"

#include "Functions.h"
#include "Degree.h"

namespace FM
{
	// Constructors

	template <typename T>
	TRadian<T>::TRadian(T r)
	{
		mRad = r;
	}

	template <typename T>
	TRadian<T>::TRadian(const TDegree<T>& d)
	{
		mRad = d.Rad();
	}

	// Assignments

	template <typename T>
	TRadian<T>& TRadian<T>::operator= (const T& x)
	{
		mRad = x;
		return *this;
	}

	template <typename T>
	TRadian<T>& TRadian<T>::operator= (const TRadian& r)
	{
		mRad = r.mRad;
		return *this;
	}

	template <typename T>
	TRadian<T>& TRadian<T>::operator= (const TDegree<T>& d)
	{
		mRad = d.Rad();
		return *this;
	}

	// Getters

	template <typename T>
	T TRadian<T>::Rad() const
	{
		return mRad;
	}

	template <typename T>
	T TRadian<T>::Deg() const
	{
		return mRad * Math::Rad2Deg<T>;
	}

	// Calculations

	template <typename T>
	TRadian<T> TRadian<T>::NormalizePi() const
	{
		T x = Math::Mod(mRad + Math::Pi<T>, Math::TwoPi<T>);
		if (x < 0) x += Math::TwoPi<T>;

		return TRadian(x - Math::Pi<T>);
	}

	template <typename T>
	TRadian<T> TRadian<T>::Normalize2Pi() const
	{
		T x = Math::Mod(mRad, Math::TwoPi<T>);
		if (x < 0) x += Math::TwoPi<T>;

		return TRadian(x);
	}

	template <typename T>
	TRadian<T> TRadian<T>::Complement() const
	{
		return TRadian(Math::HalfPi<T> - mRad);
	}

	template <typename T>
	TRadian<T> TRadian<T>::Supplement() const
	{
		return TRadian(Math::Pi<T> - mRad);
	}

	template <typename T>
	TRadian<T> TRadian<T>::Antisupplement() const
	{
		return TRadian(Math::Pi<T> + mRad);
	}

	// Arithmetic operators

	template <typename T>
	TRadian<T> TRadian<T>::operator+ (const TRadian& rhs) const
	{
		return TRadian(mRad + rhs.mRad);
	}

	template <typename T>
	TRadian<T> TRadian<T>::operator- (const TRadian& rhs) const
	{
		return TRadian(mRad - rhs.mRad);
	}

	template <typename T>
	TRadian<T> TRadian<T>::operator* (const TRadian& rhs) const
	{
		return TRadian(mRad * rhs.mRad);
	}

	template <typename T>
	TRadian<T> TRadian<T>::operator/ (const TRadian& rhs) const
	{
		return TRadian(mRad / rhs.mRad);
	}

	template <typename T>
	TRadian<T> TRadian<T>::operator+ (const TDegree<T>& rhs) const
	{ 
		return TRadian(mRad + rhs.Rad());
	}

	template <typename T>
	TRadian<T> TRadian<T>::operator- (const TDegree<T>& rhs) const
	{
		return TRadian(mRad - rhs.Rad());
	}

	template <typename T>
	TRadian<T> TRadian<T>::operator* (const TDegree<T>& rhs) const
	{
		return TRadian(mRad * rhs.Rad());
	}

	template <typename T>
	TRadian<T> TRadian<T>::operator/ (const TDegree<T>& rhs) const
	{
		return TRadian(mRad / rhs.Rad());
	}

	template <typename T>
	TRadian<T> TRadian<T>::operator* (T rhs) const
	{
		return TRadian(mRad * rhs);
	}

	template <typename T>
	TRadian<T> TRadian<T>::operator/ (T rhs) const
	{
		return TRadian(mRad / rhs);
	}

	// Assignment operators

	template <typename T>
	TRadian<T>& TRadian<T>::operator+= (const TRadian& rhs)
	{
		mRad += rhs.mRad; return *this;
	}

	template <typename T>
	TRadian<T>& TRadian<T>::operator-= (const TRadian& rhs)
	{
		mRad -= rhs.mRad; return *this;
	}

	template <typename T>
	TRadian<T>& TRadian<T>::operator*= (const TRadian& rhs)
	{
		mRad *= rhs.mRad; return *this;
	}

	template <typename T>
	TRadian<T>& TRadian<T>::operator/= (const TRadian& rhs)
	{
		mRad /= rhs.mRad; return *this;
	}

	template <typename T>
	TRadian<T>& TRadian<T>::operator+= (const TDegree<T>& rhs)
	{
		mRad += rhs.Rad(); return *this;
	}

	template <typename T>
	TRadian<T>& TRadian<T>::operator-= (const TDegree<T>& rhs)
	{
		mRad -= rhs.Rad(); return *this;
	}

	template <typename T>
	TRadian<T>& TRadian<T>::operator*= (const TDegree<T>& rhs)
	{
		mRad *= rhs.Rad(); return *this;
	}

	template <typename T>
	TRadian<T>& TRadian<T>::operator/= (const TDegree<T>& rhs)
	{
		mRad /= rhs.Rad(); return *this;
	}

	template <typename T>
	TRadian<T>& TRadian<T>::operator*= (T rhs)
	{
		mRad *= rhs; return *this;
	}

	template <typename T>
	TRadian<T>& TRadian<T>::operator/= (T rhs)
	{
		mRad /= rhs; return *this;
	}

	// Relational operators

	template <typename T>
	bool TRadian<T>::operator< (const TRadian& rhs) const
	{
		return mRad < rhs.mRad;
	}

	template <typename T>
	bool TRadian<T>::operator<= (const TRadian& rhs) const
	{
		return mRad <= rhs.mRad;
	}

	template <typename T>
	bool TRadian<T>::operator== (const TRadian& rhs) const
	{
		return mRad == rhs.mRad;
	}

	template <typename T>
	bool TRadian<T>::operator!= (const TRadian& rhs) const
	{
		return mRad != rhs.mRad;
	}

	template <typename T>
	bool TRadian<T>::operator>= (const TRadian& rhs) const
	{
		return mRad >= rhs.mRad;
	}

	template <typename T>
	bool TRadian<T>::operator> (const TRadian& rhs) const
	{
		return mRad > rhs.mRad;
	}

	// Template instantiation

	template class TRadian<float>;
	template class TRadian<double>;
	template class TRadian<int>;
}

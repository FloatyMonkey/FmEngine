// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Rectangle.h"

#include "Vector.h"
#include "Functions.h"

namespace FM
{
	// Constructors

	template <typename T>
	TRectangle<T>::TRectangle()
		: x(T(0)), y(T(0)), w(T(0)), h(T(0)) {}

	template <typename T>
	TRectangle<T>::TRectangle(T w, T h)
		: x(T(0)), y(T(0)), w(w), h(h) {}

	template <typename T>
	TRectangle<T>::TRectangle(T x, T y, T w, T h)
		: x(x), y(y), w(w), h(h) {}

	template <typename T>
	TRectangle<T>::TRectangle(const TVector2<T>& size)
		: x(T(0)), y(T(0)), w(size.x), h(size.y) {}

	template <typename T>
	TRectangle<T>::TRectangle(const TVector2<T>& position, const TVector2<T>& size)
		: x(position.x), y(position.y), w(size.x), h(size.y) {}

	// Predefined rectangles

	template <typename T>
	const TRectangle<T> TRectangle<T>::Zero(T(0), T(0), T(0), T(0));

	// Calculations

	template <typename T>
	TRectangle<T> TRectangle<T>::Normalized() const
	{
		TRectangle<T> r(x, y, w, h);

		if (w < 0)
		{
			r.x = x + w;
			r.w = -w;
		}

		if (h < 0)
		{
			r.y = y + h;
			r.h = -h;
		}

		return r;
	}

	template <typename T>
	TVector2<T> TRectangle<T>::Center() const
	{
		return TVector2<T>(x + w / T(2), y + h / T(2));
	}

	template <typename T>
	bool TRectangle<T>::Contains(const TVector2<T>& point) const
	{
		return point.x >= x && point.x <= x + w && point.y >= y && point.y <= y + h;
	}

	template <typename T>
	bool TRectangle<T>::Intersects(const TRectangle<T>& lhs, const TRectangle<T>& rhs)
	{
		T xMin = Math::Max(lhs.x, rhs.x);
		T yMin = Math::Max(lhs.y, rhs.y);

		T xMax = Math::Min(lhs.x + lhs.w, rhs.x + rhs.w);
		T yMax = Math::Min(lhs.y + lhs.h, rhs.y + rhs.h);

		return xMin < xMax && yMin < yMax;
	}

	template <typename T>
	TRectangle<T> TRectangle<T>::Intersected(const TRectangle<T>& lhs, const TRectangle<T>& rhs)
	{
		TRectangle<T> r;

		r.x = Math::Max(lhs.x, rhs.x);
		r.y = Math::Max(lhs.y, rhs.y);

		r.w = Math::Min(lhs.x + lhs.w, rhs.x + rhs.w) - r.x;
		r.h = Math::Min(lhs.y + lhs.h, rhs.y + rhs.h) - r.y;

		return r;
	}

	// Relational operators

	template <typename T>
	bool TRectangle<T>::operator== (const TRectangle& rhs) const
	{
		return x == rhs.x && y == rhs.y && w == rhs.w && h == rhs.h;
	}

	template <typename T>
	bool TRectangle<T>::operator!= (const TRectangle& rhs) const
	{
		return x != rhs.x || y != rhs.y || w != rhs.w || h != rhs.h;
	}

	// Template instantiation

	template class TRectangle<float>;
	template class TRectangle<double>;
	template class TRectangle<int>;
}

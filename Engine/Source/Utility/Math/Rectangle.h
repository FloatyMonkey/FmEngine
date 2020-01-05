// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "Vector2.h"

namespace FM
{
	/// A rectangle.

	template <typename T>
	class TRectangle
	{
	public:

		union
		{
			TVector2<T> position;
			struct { T x, y; };
		};

		union
		{
			TVector2<T> size;
			struct { T w, h; };
		};

	public:

		// Constructors

		TRectangle();
		TRectangle(T w, T h);
		TRectangle(T x, T y, T w, T h);
		TRectangle(const TVector2<T>& size);
		TRectangle(const TVector2<T>& position, const TVector2<T>& size);

		template <typename U>
		TRectangle(const TRectangle<U>& r);

		// Predefined rectangles

		static const TRectangle Zero;

		// Calculations

		/// Returns the rectangle with a non-negative width and height.
		TRectangle<T> Normalized() const;

		/// Returns the center of this rectangle.
		TVector2<T> Center() const;

		/// Returns true if the point is inside or on the edge of this rectangle.
		bool Contains(const TVector2<T>& point) const;

		/// Returns true if the two rectangles intersect.
		static bool Intersects(const TRectangle<T>& lhs, const TRectangle<T>& rhs);

		/// Returns the rectangle that is formed by intersecting two rectangles.
		static TRectangle<T> Intersected(const TRectangle<T>& lhs, const TRectangle<T>& rhs);

		// Relational operators

		bool operator== (const TRectangle& rhs) const;
		bool operator!= (const TRectangle& rhs) const;
	};

	// Template implementations

	template <typename T>
	template <typename U>
	TRectangle<T>::TRectangle(const TRectangle<U>& r)
		: x(T(r.x)), y(T(r.y)), w(T(r.w)), h(T(r.h)) {}

	// Type aliases

	using Rectangle = TRectangle<float>;

	using RectangleF = TRectangle<float>;
	using RectangleD = TRectangle<double>;
	using RectangleI = TRectangle<int>;
}

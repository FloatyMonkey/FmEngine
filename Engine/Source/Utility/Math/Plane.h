// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "Vector.h"

namespace FM
{
	/// A three-dimensional plane.

	template <typename T>
	class TPlane
	{
	public:

		TVector3<T> normal;	///< Normalized normal vector of the plane.
		T distance = T(0);	///< Distance from the plane to the origin.

	public:

		TPlane() = default;

		template <typename T>
		TPlane(T a, T b, T c, T d)
			: normal(a, b, c), distance(d) {}

		template <typename T>
		TPlane(const TVector3<T>& normal, T distance)
			: normal(normal), distance(distance) {}

		template <typename T>
		TPlane(const TVector3<T>& normal, const TVector3<T>& point)
			: normal(normal), distance(Math::Dot(normal, point)) {}

		template <typename T>
		TPlane(const TVector3<T>& p0, const TVector3<T>& p1, const TVector3<T>& p2)
		{
			normal = Math::Normalize(Math::Cross(p1 - p0, p2 - p0));
			distance = Math::Dot(normal, p0);
		}
	};

	// Type aliases

	using Plane = TPlane<float>;
}

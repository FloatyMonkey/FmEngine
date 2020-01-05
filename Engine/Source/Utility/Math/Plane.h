// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "Vector3.h"

// TODO: Implement the Plane.

namespace FM
{
	template <typename T> class TVector4;

	/// A three-dimensional plane.

	template <typename T>
	class TPlane
	{
	public:

		TVector3<T> normal;	///< Normalized normal vector of the plane.
		T distance;			///< Distance from the plane to the origin.

	public:

		// Constructors

		TPlane();
		TPlane(T a, T b, T c, T d);
		TPlane(const TVector4<T>& equation);
		TPlane(const TVector3<T>& normal, T distance);
		TPlane(const TVector3<T>& normal, const TVector3<T>& point);
		TPlane(const TVector3<T>& p0, const TVector3<T>& p1, const TVector3<T>& p2);


	};

	// Type aliases

	using Plane = TPlane<float>;

	using PlaneF = TPlane<float>;
	using PlaneD = TPlane<double>;
	using PlaneI = TPlane<int>;
}

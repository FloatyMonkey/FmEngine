// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Plane.h"

namespace FM
{
	template<typename T>
	TPlane<T>::TPlane()
	{
	}
	template <typename T>
	TPlane<T>::TPlane(T a, T b, T c, T d)
		: normal(a, b, c), distance(d) {}

	template<typename T>
	TPlane<T>::TPlane(const TVector4<T>& equation)
	{
	}

	template <typename T>
	TPlane<T>::TPlane(const TVector3<T>& normal, T distance)
	{
	}

	template <typename T>
	TPlane<T>::TPlane(const TVector3<T>& normal, const TVector3<T>& point)
	{
	}

	template <typename T>
	TPlane<T>::TPlane(const TVector3<T>& p0, const TVector3<T>& p1, const TVector3<T>& p2)
	{
		normal = TVector3<T>::Cross(p1 - p0, p2 - p0).Normalized();
		distance = TVector3<T>::Dot(normal, p0);
	}

	// Template instantiation

	template class TPlane<float>;
	template class TPlane<double>;
	template class TPlane<int>;
}

// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"

namespace FM
{
	/// Stores a 3 dimensional transformation.

	template <typename T>
	struct TTransform
	{
		TVector3<T> translation = T(0);
		TQuaternion<T> rotation;
		TVector3<T> scale = T(1);

		constexpr TTransform() = default;

		TTransform(const TVector3<T>& t, const TQuaternion<T>& r, const TVector3<T>& s = T(1))
			: translation(t), rotation(r), scale(s) {}
	};

	namespace Math
	{
		template <typename T>
		TTransform<T> Inverse(const TTransform<T>& x)
		{
			TVector3<T> s = T(1) / x.scale;
			TQuaternion<T> r = Inverse(x.rotation);
			TVector3<T> t = r * (-x.translation * s);

			return TTransform<T>(t, r, s);
		}
	}

	// Arithmetic Operators

	template <typename T>
	inline constexpr TTransform<T> operator* (const TTransform<T>& lhs, const TTransform<T>& rhs)
	{
		TVector3<T> s = lhs.scale * rhs.scale;
		TQuaternion<T> r = lhs.rotation * rhs.rotation;
		TVector3<T> t = lhs.rotation * (rhs.translation * lhs.scale) + lhs.translation;

		return TTransform<T>(t, r, s);
	}

	// Assignment operators

	template <typename T>
	inline constexpr TTransform<T> operator*= (const TTransform<T>& lhs, const TTransform<T>& rhs) {
		return lhs = lhs * rhs;
	}

	// Relational operators

	template <typename T>
	inline constexpr bool operator== (const TTransform<T>& lhs, const TTransform<T>& rhs)
	{
		return lhs.translation == rhs.translation && lhs.rotation == rhs.rotation && lhs.scale == rhs.scale;
	}

	// Type aliases

	using Transform = TTransform<float>;
}

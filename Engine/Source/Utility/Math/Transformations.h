// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"
#include "Transform.h"

namespace FM
{
	namespace Math
	{
		// Translation

		template <typename T>
		constexpr TMatrix3<T> Translation(T x, T y)
		{
			return TMatrix3<T>
			(
				T(1), T(0), x,
				T(0), T(1), y,
				T(0), T(0), T(1)
			);
		}

		template <typename T>
		inline constexpr TMatrix3<T> Translation(const TVector2<T>& v)
		{
			return Translation(v.x, v.y);
		}

		template <typename T>
		constexpr TMatrix4<T> Translation(T x, T y, T z)
		{
			return TMatrix4<T>
			(
				T(1), T(0), T(0), x,
				T(0), T(1), T(0), y,
				T(0), T(0), T(1), z,
				T(0), T(0), T(0), T(1)
			);
		}

		template <typename T>
		inline constexpr TMatrix4<T> Translation(const TVector3<T>& v)
		{
			return Translation(v.x, v.y, v.z);
		}

		// Rotation

		template <typename T>
		constexpr TMatrix3<T> Rotation(const T& r)
		{
			T cos = Math::Cos(r);
			T sin = Math::Sin(r);

			return TMatrix3<T>
			(
				cos, -sin,  T(0),
				sin,  cos,  T(0),
				T(0), T(0), T(1)
			);
		}

		template <typename T>
		constexpr TMatrix4<T> RotationX(const T& r)
		{
			T cos = Math::Cos(r);
			T sin = Math::Sin(r);

			return TMatrix4<T>
			(
				T(1), T(0),  T(0), T(0),
				T(0), cos,  -sin,  T(0),
				T(0), sin,   cos,  T(0),
				T(0), T(0),  T(0), T(1)
			);
		}

		template <typename T>
		constexpr TMatrix4<T> RotationY(const T& r)
		{
			T cos = Math::Cos(r);
			T sin = Math::Sin(r);

			return TMatrix4<T>
			(
				 cos,  T(0), sin,  T(0),
				 T(0), T(1), T(0), T(0),
				-sin,  T(0), cos,  T(0),
				 T(0), T(0), T(0), T(1)
			);
		}

		template <typename T>
		constexpr TMatrix4<T> RotationZ(const T& r)
		{
			T cos = Math::Cos(r);
			T sin = Math::Sin(r);

			return TMatrix4<T>
			(
				cos,  -sin,  T(0), T(0),
				sin,   cos,  T(0), T(0),
				T(0),  T(0), T(1), T(0),
				T(0),  T(0), T(0), T(1)
			);
		}

		template <typename T>
		constexpr TMatrix3<T> Rotation(const TQuaternion<T>& q)
		{
			T x2 = q.x + q.x;
			T y2 = q.y + q.y;
			T z2 = q.z + q.z;
			T x2w = x2 * q.w;
			T y2w = y2 * q.w;
			T z2w = z2 * q.w;
			T x2x = x2 * q.x;
			T y2x = y2 * q.x;
			T z2x = z2 * q.x;
			T y2y = y2 * q.y;
			T z2y = z2 * q.y;
			T z2z = z2 * q.z;

			return TMatrix3<T>
			(
				T(1) - (y2y + z2z), y2x - z2w, z2x + y2w,
				y2x + z2w, T(1) - (x2x + z2z), z2y - x2w,
				z2x - y2w, z2y + x2w, T(1) - (x2x + y2y)
			);
		}

		// Scaling

		template <typename T>
		constexpr TMatrix3<T> Scaling(T x, T y)
		{
			return TMatrix3<T>
			(
				x,    T(0), T(0),
				T(0), y,    T(0),
				T(0), T(0), T(1)
			);
		}

		template <typename T>
		inline constexpr TMatrix3<T> Scaling(const TVector2<T>& v)
		{
			return Scaling(v.x, v.y);
		}

		template <typename T>
		constexpr TMatrix4<T> Scaling(T x, T y, T z)
		{
			return TMatrix4<T>
			(
				x,    T(0), T(0), T(0),
				T(0), y,    T(0), T(0),
				T(0), T(0), z,    T(0),
				T(0), T(0), T(0), T(1)
			);
		}

		template <typename T>
		inline constexpr TMatrix4<T> Scaling(const TVector3<T>& v)
		{
			return Scaling(v.x, v.y, v.z);
		}

		// Skewing

		template <typename T>
		constexpr TMatrix3<T> Skewing(T x, T y)
		{
			return TMatrix3<T>
			(
				T(1), x,    T(0),
				y,    T(1), T(0),
				T(0), T(0), T(1)
			);
		}

		template <typename T>
		inline constexpr TMatrix3<T> Skewing(const TVector2<T>& v)
		{
			return Skewing(v.x, v.y);
		}

		template <typename T>
		constexpr TMatrix4<T> Skewing(T x, T y, T z)
		{
			return TMatrix3<T>
			(
				T(1), T(0), x,    T(0),
				T(0), y,    T(0), T(0),
				z,    T(0), T(1), T(0),
				T(0), T(0), T(0), T(1)
			);
		}

		template <typename T>
		inline constexpr TMatrix4<T> Skewing(const TVector3<T>& v)
		{
			return Skewing(v.x, v.y, v.z);
		}

		// Transformation

		template <typename T>
		constexpr TMatrix4<T> Transformation(const TVector3<T>& translation, const TQuaternion<T>& rotation, const TVector3<T>& scale)
		{
			TMatrix3<T> rot = Rotation(rotation);

			return TMatrix4<T>
			(
				rot(0, 0) * scale.x, rot(0, 1) * scale.y, rot(0, 2) * scale.z, translation.x,
				rot(1, 0) * scale.x, rot(1, 1) * scale.y, rot(1, 2) * scale.z, translation.y,
				rot(2, 0) * scale.x, rot(2, 1) * scale.y, rot(2, 2) * scale.z, translation.z,
				T(0), T(0), T(0), T(1)
			);
		}

		template <typename T>
		inline constexpr TMatrix4<T> Transformation(const TTransform<T>& t)
		{
			return Transformation(t.translation, t.rotation, t.scale);
		}

		// Projection

		template <typename T>
		constexpr TMatrix4<T> LookAt(const TVector3<T>& from, const TVector3<T>& to, const TVector3<T>& up)
		{
			TVector3<T> z = Math::Normalize(from - to);
			TVector3<T> x = Math::Normalize(Math::Cross(up, z));
			TVector3<T> y = Math::Normalize(Math::Cross(z, x));

			return TMatrix4<T>
			(
				x.x,  x.y,  x.z,  -Math::Dot(x, from),
				y.x,  y.y,  y.z,  -Math::Dot(y, from),
				z.x,  z.y,  z.z,  -Math::Dot(z, from),
				T(0), T(0), T(0),  T(1)
			);
		}

		template <typename T>
		constexpr TMatrix4<T> Perspective(T fov, T aspectRatio, T nearClip, T farClip)
		{
			T height = T(1) / Math::Tan(fov / T(2));
			T width = height / aspectRatio;
			T range = farClip / (nearClip - farClip);

			return TMatrix4<T>
			(
				width, T(0),   T(0),  T(0),
				T(0),  height, T(0),  T(0),
				T(0),  T(0),   range, range * nearClip,
				T(0),  T(0),   T(-1), T(0)
			);
		}

		template <typename T>
		constexpr TMatrix4<T> Orthographic(T width, T height, T nearClip, T farClip)
		{
			T range = T(1) / (nearClip - farClip);

			return TMatrix4<T>
			(
				T(2) / width, T(0),          T(0),  T(0),
				T(0),         T(2) / height, T(0),  T(0),
				T(0),         T(0),          range, range * nearClip,
				T(0),         T(0),          T(0),  T(1)
			);
		}
	}
}

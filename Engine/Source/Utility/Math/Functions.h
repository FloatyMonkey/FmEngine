// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

// TODO: Remove this.
#include <cmath>

namespace FM
{
	template <typename T> class TRadian;

	/// A collection of common math functions and constants.

	namespace Math
	{
		// Constants

		template <typename T>
		static constexpr T Pi = T(3.14159265358979323846);

		template <typename T>
		static constexpr T TwoPi = Pi<T> * T(2);

		template <typename T>
		static constexpr T HalfPi = Pi<T> / T(2);

		template <typename T>
		static constexpr T Sqrt2 = T(1.41421356237309504880);

		template <typename T>
		static constexpr T Deg2Rad = Pi<T> / T(180);

		template <typename T>
		static constexpr T Rad2Deg = T(180) / Pi<T>;

		// Functions

		/// Square root.
		/// @return The square root of x.
		template <typename T>
		static T Sqrt(T x)
		{
			return T(std::sqrt(float(x)));
		}

		/// Modulus.
		/// @return The remainder of (numerator / denominator).
		template <typename T>
		static T Mod(T numerator, T denominator)
		{
			return T(std::fmod(float(numerator), float(denominator)));
		}

		/// Power.
		/// @return base raised to the power exponent.
		template <typename T>
		static T Pow(T base, T exponent)
		{
			return T(std::pow(float(base), float(exponent)));
		}

		/// Rounds a value up.
		/// @return The smallest integral value that is not less than x.
		template <typename T>
		static T Ceil(T x)
		{
			return T(std::ceil(float(x)));
		}

		/// Rounds a value down.
		/// @return The largest integral value that is not greater than x.
		template <typename T>
		static T Floor(T x)
		{
			return T(std::floor(float(x)));
		}

		// Trigonometric functions

		/// Sine
		template <typename T>
		static T Sin(const TRadian<T>& r)
		{
			return T(std::sin(float(r.Rad())));
		}

		/// Cosine
		template <typename T>
		static T Cos(const TRadian<T>& r)
		{
			return T(std::cos(float(r.Rad())));
		}

		/// Tangent
		template <typename T>
		static T Tan(const TRadian<T>& r)
		{
			return T(std::tan(float(r.Rad())));
		}

		/// Inverse sine
		template <typename T>
		static TRadian<T> Asin(T s)
		{
			return TRadian<T>(std::asin(float(s)));
		}

		/// Inverse cosine
		template <typename T>
		static TRadian<T> Acos(T c)
		{
			return TRadian<T>(std::acos(float(c)));
		}

		/// Inverse tangent
		template <typename T>
		static TRadian<T> Atan(T t)
		{
			return TRadian<T>(std::acos(float(t)));
		}

		// Function templates

		/// Returns the absolute value of x.
		template <typename T>
		static inline constexpr T Abs(const T& x)
		{
			return (x >= T(0)) ? x : -x;
		}

		/// Returns the smallest of two values.
		template <typename LT, typename RT>
		static inline constexpr auto Min(const LT& lhs, const RT& rhs)
		{
			using T = decltype(lhs + rhs);
			return lhs > rhs ? T(rhs) : T(lhs);
		}

		/// Returns the smallest of all values.
		template <typename T1, typename ...Types>
		static inline constexpr auto Min(const T1& arg0, const Types& ...args)
		{
			return Min(arg0, Min(args...));
		}

		/// Returns the largest of two values.
		template <typename LT, typename RT>
		static inline constexpr auto Max(const LT& lhs, const RT& rhs)
		{
			using T = decltype(lhs + rhs);
			return lhs > rhs ? T(lhs) : T(rhs);
		}

		/// Returns the largest of all values.
		template <typename T1, typename ...Types>
		static inline constexpr auto Max(const T1& arg0, const Types& ...args)
		{
			return Max(arg0, Max(args...));
		}

		/// Clamps a value within the [min, max] range.
		/// @param x The value to be clamped.
		/// @param min The minimum of the range.
		/// @param max The maximum of the range.
		/// @return Returns the value in the [min, max] range.
		template <typename T>
		static inline constexpr T Clamp(const T& x, const T& min, const T& max)
		{
			return Max(min, Min(max, x));
		}

		/// Remaps a number from one range to another.
		/// The minimum of either range may be larger or smaller than the maximum.
		/// This allows negative numbers and reversing a range of numbers.
		/// @param x The value to remap.
		/// @param inMin The minimum of the value's current range.
		/// @param inMax The maximum of the value's current range.
		/// @param outMin The minimum of the value's target range.
		/// @param outMax The maximum of the value's target range.
		/// @return The mapped value.
		template <typename T>
		static inline constexpr T Map(const T& x, const T& inMin, const T& inMax, const T& outMin, const T& outMax)
		{
			return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
		}

		/// Interpolates between two values.
		/// @param min,max Input value.
		/// @param t Interpolant specified in the [0, 1] range.
		/// @return Returns the result of linear interpolation.
		template <typename T>
		static inline constexpr T Lerp(const T& min, const T& max, const T& t)
		{
			return min + t * (max - min);
		}

		/// Returns the sign of x.
		/// @param x The value to get the sign from.
		/// @return Returns 1 if x is positive, -1 if x is negative and 0 if x is 0.
		template <typename T>
		static inline constexpr T Sign(const T& x)
		{
			return (T(0) < x) - (x < T(0));
		}

		/// Solves a quadtratic equation. Ax² + Bx + C = 0.
		/// @param a,b,c The equation parameters.
		/// @param root1, root2 The root that was found.
		/// @return The number of roots that were found.
		template <typename T>
		static inline constexpr int SolveQuadratic(const T& a, const T& b, const T& c, T& root1, T& root2)
		{
			if (a == T(0)) return 0;

			float discriminant = b * b - T(4) * a * c;

			if (discriminant < T(0)) return 0;

			float sqrt = Sqrt(discriminant);

			root1 = (-b + sqrt) / (T(2) * a);
			root2 = (-b - sqrt) / (T(2) * a);

			return (root1 == root2) ? 1 : 2;
		}
	}
}

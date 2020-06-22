// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

// TODO: Remove this.
#include <cmath>

namespace FM
{
	namespace Math
	{
		// Constants

		template <typename T>
		inline constexpr T E =  T(2.71828182845904523536);

		template <typename T>
		inline constexpr T Pi = T(3.14159265358979323846);

		template <typename T>
		inline constexpr T Tau = Pi<T> * T(2);

		template <typename T>
		inline constexpr T HalfPi = Pi<T> / T(2);

		template <typename T>
		inline constexpr T Sqrt2 = T(1.41421356237309504880);

		// Functions

		/// Converts degrees to radians.
		template <typename T>
		T ToRadians(T degrees)
		{
			return degrees * (Pi<T> / T(180));
		}

		/// Converts radians to degrees.
		template <typename T>
		T ToDegrees(T radians)
		{
			return radians * (T(180) / Pi<T>);
		}

		/// Unwinds an angle in radians to the [-PI, PI] range.
		template <typename T>
		T UnwindRadians(T radians)
		{
			while (radians > Pi<T>) radians -= TwoPi<T>;
			while (radians < -Pi<T>) radians += TwoPi<T>;
			return radians;
		}

		/// Unwinds an angle in degrees to the [-180, 180] range.
		template <typename T>
		T UnwindDegrees(T degrees)
		{
			while (degrees > T(180)) degrees -= T(360);
			while (degrees < T(-180)) degrees += T(360);
			return degrees;
		}

		/// Square root.
		/// @return The square root of x.
		template <typename T>
		static T Sqrt(T x)
		{
			return T(std::sqrt(float(x)));
		}

		/// Modulus, returns the remainder of (numerator / denominator).
		template <typename T>
		static T Mod(T numerator, T denominator)
		{
			return T(std::fmod(float(numerator), float(denominator)));
		}

		/// Power, returns base raised to the power exponent.
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
		static T Sin(const T& r)
		{
			return T(std::sin(float(r)));
		}

		/// Cosine
		template <typename T>
		static T Cos(const T& r)
		{
			return T(std::cos(float(r)));
		}

		/// Tangent
		template <typename T>
		static T Tan(const T& r)
		{
			return T(std::tan(float(r)));
		}

		/// Inverse sine
		template <typename T>
		static T Asin(T s)
		{
			return T(std::asin(float(s)));
		}

		/// Inverse cosine
		template <typename T>
		static T Acos(T c)
		{
			return T(std::acos(float(c)));
		}

		/// Inverse tangent
		template <typename T>
		static T Atan(T t)
		{
			return T(std::atan(float(t)));
		}

		// Function templates

		/// Returns the absolute value of x.
		template <typename T>
		static inline constexpr T Abs(const T& x)
		{
			return x >= T(0) ? x : -x;
		}

		/// Returns the sign of x.
		template <typename T>
		static inline constexpr T Sign(const T& x)
		{
			return x >= T(0) ? T(1) : T(-1);
		}

		/// Returns the smallest of two values.
		template <typename L, typename R>
		static inline constexpr auto Min(const L& lhs, const R& rhs)
		{
			using T = decltype(lhs + rhs);
			return lhs > rhs ? T(rhs) : T(lhs);
		}

		/// Returns the smallest of all values.
		template <typename Arg, typename ...Args>
		static inline constexpr auto Min(const Arg& arg, const Args& ...args)
		{
			return Min(arg, Min(args...));
		}

		/// Returns the largest of two values.
		template <typename L, typename R>
		static inline constexpr auto Max(const L& lhs, const R& rhs)
		{
			using T = decltype(lhs + rhs);
			return lhs > rhs ? T(lhs) : T(rhs);
		}

		/// Returns the largest of all values.
		template <typename Arg, typename ...Args>
		static inline constexpr auto Max(const Arg& arg, const Args& ...args)
		{
			return Max(arg, Max(args...));
		}

		/// Clamps a value within the [min, max] range.
		template <typename T>
		static inline constexpr T Clamp(const T& x, const T& min, const T& max)
		{
			return Max(min, Min(max, x));
		}

		/// Clamps a value within the [0, 1] range.
		template <typename T>
		static inline constexpr T Saturate(const T& x)
		{
			return Clamp(x, T(0), T(1));
		}

		/// Remaps a value from one range to another.
		/// The minimum of either range may be larger or smaller than the maximum.
		template <typename T>
		static inline constexpr T Map(const T& x, const T& inMin, const T& inMax, const T& outMin, const T& outMax)
		{
			return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
		}

		/// Linearly interpolates between two values.
		template <typename T, typename L>
		static inline constexpr T Lerp(const T& min, const T& max, const L& t)
		{
			return min + (max - min) * t;
		}

		/// Linearly interpolates between two values and normalizes the result.
		template <typename T, typename L>
		static inline constexpr T NLerp(const T& min, const T& max, const L& t)
		{
			return Normalize(Lerp(min, max, t));
		}

		/// Solves a quadtratic equation. Ax² + Bx + C = 0.
		template <typename T>
		static inline constexpr int SolveQuadratic(const T& a, const T& b, const T& c, T& root0, T& root1)
		{
			if (a == T(0)) return 0;

			float D = b * b - T(4) * a * c;

			if (D < T(0)) return 0;

			float sqrt = Sqrt(D);

			root0 = (-b + sqrt) / (T(2) * a);
			root1 = (-b - sqrt) / (T(2) * a);

			return (root0 == root1) ? 1 : 2;
		}
	}
}

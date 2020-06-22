// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../CoreTypes.h"

// TODO: Move this to Windows specific file.
#undef RGB

namespace FM
{
	/// Represents a color with 4 components.
	/// The components are red, green, blue and alpha.
	/// They are floating point values in the [0, 1] range.
	/// When outside this range, the color class can represent HDR values.

	class Color
	{
	public:

		union {
			float rgba[4]{ 0 };
			struct { float r, g, b, a; };
		};

	public:

		// Constructors

		Color() = default;

		constexpr Color(float bw, float a = 1.0f)
			: r(bw), g(bw), b(bw), a(a) {}

		constexpr Color(float r, float g, float b, float a = 1.0f)
			: r(r), g(g), b(b), a(a) {}

		/// Returns a color specified by red, green, blue and alpha components.
		/// All values are in the [0, 255] range.
		static Color RGB(uint8 r, uint8 g, uint8 b, uint8 a = 255);

		/// Returns a color specified by hue, saturation, value and alpha components.
		/// HSV values are in the [0, 1] range, alpha value is in the [0, 255] range.
		static Color HSV(float h, float s, float v, uint8 a = 255);

		/// Returns a color value specified by a hexadecimal value.
		/// The color is formatted as 0xRRGGBBAA, the alpha value is mandatory.
		static Color HEX(uint32 color);

		// Predefined colors

		static const Color Black;
		static const Color White;
		static const Color Transparent;
		static const Color Red;
		static const Color Green;
		static const Color Blue;

		// Calculations

		/// Returns a premultiplied version of the color.
		/// Multiplies the RGB channels with the alpha channel.
		/// The alpha channel itself will remain unmodified.
		Color Premultiplied() const;

		// Operators

		friend Color operator* (float lhs, const Color& rhs);

		// Arithmetic operators

		Color operator+ (const Color& rhs) const;
		Color operator- (const Color& rhs) const;

		Color operator* (float rhs) const;
		Color operator/ (float rhs) const;

		// Assignment operators

		Color& operator+= (const Color& rhs);
		Color& operator-= (const Color& rhs);

		Color& operator*= (float rhs);
		Color& operator/= (float rhs);

		// Relational operators

		bool operator== (const Color& rhs) const;
	};
}

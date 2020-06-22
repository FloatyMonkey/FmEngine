// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Color.h"

#include "Functions.h"

namespace FM
{
	// Constructors

	Color Color::RGB(uint8 r, uint8 g, uint8 b, uint8 a)
	{
		return Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
	}

	Color Color::HSV(float h, float s, float v, uint8 a)
	{
		float alpha = a / 255.0f;

		if (v == 0) return Color(0, alpha);
		if (s == 0) return Color(v, alpha);

		float hf = h * 6.0f;
		int i = (int)Math::Floor(hf);
		float f = hf - (float)i;

		float f1 = v * (1 - s);
		float f2 = v * (1 - s * f);
		float f3 = v * (1 - s * (1 - f));

		switch (i)
		{
		case 0: return Color(v,  f3, f1, alpha); // Red
		case 1: return Color(f2, v,  f1, alpha); // Yellow
		case 2: return Color(f1, v,  f3, alpha); // Green
		case 3: return Color(f1, f2, v,  alpha); // Cyan
		case 4: return Color(f3, f1, v,  alpha); // Blue
		case 5: return Color(v,  f1, f2, alpha); // Magenta

		case 6: return Color(v,  f3, f1, alpha);
		case -1: return Color(v, f1, f2, alpha);

		default: return Color::Black;
		}
	}

	Color Color::HEX(uint32 color)
	{
		Color c;

		c.r = ((color >> 24) & 0xFF) / 255.0f;
		c.g = ((color >> 16) & 0xFF) / 255.0f;
		c.b = ((color >> 8 ) & 0xFF) / 255.0f;
		c.a = ((color >> 0 ) & 0xFF) / 255.0f;

		return c;
	}

	// Predefined colors

	const Color Color::Black(0, 0, 0);
	const Color Color::White(1, 1, 1);
	const Color Color::Transparent(0, 0, 0, 0);
	const Color Color::Red(1, 0, 0);
	const Color Color::Green(0, 1, 0);
	const Color Color::Blue(0, 0, 1);

	// Calculations

	Color Color::Premultiplied() const
	{
		return Color(r * a, g * a, b * a, a);
	}

	// Operators

	Color operator* (float lhs, const Color& rhs) {
		return Color(lhs * rhs.r, lhs * rhs.g, lhs * rhs.b, lhs * rhs.a);
	}

	// Arithmetic operators

	Color Color::operator+ (const Color& rhs) const {
		return Color(r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a);
	}

	Color Color::operator- (const Color& rhs) const {
		return Color(r - rhs.r, g - rhs.g, b - rhs.b, a - rhs.a);
	}

	Color Color::operator* (float rhs) const {
		return Color(r * rhs, g * rhs, b * rhs, a * rhs);
	}

	Color Color::operator/ (float rhs) const {
		return Color(r / rhs, g / rhs, b / rhs, a / rhs);
	}

	// Assignment operators

	Color& Color::operator+= (const Color& rhs) {
		return *this = *this + rhs;
	}

	Color& Color::operator-= (const Color& rhs) {
		return *this = *this - rhs;
	}

	Color& Color::operator*= (float rhs) {
		return *this = *this * rhs;
	}

	Color& Color::operator/= (float rhs) {
		return *this = *this / rhs;
	}

	// Relational operators

	bool Color::operator== (const Color& rhs) const
	{
		return r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a;
	}
}

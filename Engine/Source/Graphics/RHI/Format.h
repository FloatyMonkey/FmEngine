// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../../Utility/CoreTypes.h"

namespace FM
{
	/// Defines resource formats.
	///
	/// Each format has one or more components.
	/// The number after every component indicates how many bits it occupies.
	///
	/// R: Red
	/// G: Green
	/// B: Blue
	/// D: Depth
	/// S: Stencil
	/// X: Unused
	///
	/// Each format also has a type specifier at the end.
	///
	/// UNorm: Unsigned normalized integer.
	/// SNorm: Signed normalized integer.
	/// UInt:  Unsigned integer.
	/// SInt:  Signed integer.
	/// Float: Floating-point value.

	enum class EFormat
	{
		Unknown,

		// R Color Formats

		R8UNorm,
		R8SNorm,
		R8UInt,
		R8SInt,

		R16UNorm,
		R16SNorm,
		R16UInt,
		R16SInt,
		R16Float,

		R32UInt,
		R32SInt,
		R32Float,

		// RG Color Formats

		RG8UNorm,
		RG8SNorm,
		RG8UInt,
		RG8SInt,

		RG16UNorm,
		RG16SNorm,
		RG16UInt,
		RG16SInt,
		RG16Float,

		RG32UInt,
		RG32SInt,
		RG32Float,

		// RGB Color Formats

		RGB8UNorm,
		RGB8SNorm,
		RGB8UInt,
		RGB8SInt,

		RGB16UNorm,
		RGB16SNorm,
		RGB16UInt,
		RGB16SInt,
		RGB16Float,

		RGB32UInt,
		RGB32SInt,
		RGB32Float,

		// RGBA Color Formats

		RGBA8UNorm,
		RGBA8SNorm,
		RGBA8UInt,
		RGBA8SInt,

		RGBA16UNorm,
		RGBA16SNorm,
		RGBA16UInt,
		RGBA16SInt,
		RGBA16Float,

		RGBA32UInt,
		RGBA32SInt,
		RGBA32Float,

		// Depth-Stencil Formats

		D16UNorm,
		D24UNormS8UInt,
		D32Float,
		D32FloatS8UIntX24,
	};

	/// Metadata for an EFormat.

	struct FormatInfo
	{
		uint8 size;

		uint8 components : 4;
		uint8 blockWidth : 4;
		uint8 blockHeight : 4;

		bool isDepth : 1;
		bool isStencil : 1;
		bool isNormalized : 1;
		bool isCompressed : 1;
	};

	/// Returns a FormatInfo structure for the given EFormat.
	FormatInfo GetFormatInfo(EFormat format);
}

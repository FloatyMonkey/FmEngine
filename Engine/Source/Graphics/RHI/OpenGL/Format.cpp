// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Format.h"

namespace FM::OpenGL
{
	GLFormatInfo Map(EFormat format)
	{
		switch (format)
		{
		// R Color Formats

		case EFormat::R8UNorm:				return { GL_R8, GL_RED, GL_UNSIGNED_BYTE };
		case EFormat::R8SNorm:				return { GL_R8_SNORM, GL_RED, GL_BYTE };
		case EFormat::R8UInt:				return { GL_R8UI, GL_RED_INTEGER, GL_UNSIGNED_BYTE };
		case EFormat::R8SInt:				return { GL_R8I, GL_RED_INTEGER, GL_BYTE };

		case EFormat::R16UNorm:				return { GL_R16, GL_RED, GL_UNSIGNED_SHORT };
		case EFormat::R16SNorm:				return { GL_R16_SNORM, GL_RED, GL_SHORT };
		case EFormat::R16UInt:				return { GL_R16UI, GL_RED_INTEGER, GL_UNSIGNED_SHORT };
		case EFormat::R16SInt:				return { GL_R16I, GL_RED_INTEGER, GL_SHORT };
		case EFormat::R16Float:				return { GL_R16F, GL_RED, GL_HALF_FLOAT };

		case EFormat::R32UInt:				return { GL_R32UI, GL_RED_INTEGER, GL_UNSIGNED_INT };
		case EFormat::R32SInt:				return { GL_R32I, GL_RED_INTEGER, GL_INT };
		case EFormat::R32Float:				return { GL_R32F, GL_RED, GL_FLOAT };

		// RG Color Formats

		case EFormat::RG8UNorm:				return { GL_RG8, GL_RG, GL_UNSIGNED_BYTE };
		case EFormat::RG8SNorm:				return { GL_RG8_SNORM, GL_RG, GL_BYTE };
		case EFormat::RG8UInt:				return { GL_RG8UI, GL_RG_INTEGER, GL_UNSIGNED_BYTE };
		case EFormat::RG8SInt:				return { GL_RG8I, GL_RG_INTEGER, GL_BYTE };

		case EFormat::RG16UNorm:			return { GL_RG16, GL_RG, GL_UNSIGNED_SHORT };
		case EFormat::RG16SNorm:			return { GL_RG16_SNORM, GL_RG, GL_SHORT };
		case EFormat::RG16UInt:				return { GL_RG16UI, GL_RG_INTEGER, GL_UNSIGNED_SHORT };
		case EFormat::RG16SInt:				return { GL_RG16I, GL_RG_INTEGER, GL_SHORT };
		case EFormat::RG16Float:			return { GL_RG16F, GL_RG, GL_HALF_FLOAT };

		case EFormat::RG32UInt:				return { GL_RG32UI, GL_RG_INTEGER, GL_UNSIGNED_INT };
		case EFormat::RG32SInt:				return { GL_RG32I, GL_RG_INTEGER, GL_INT };
		case EFormat::RG32Float:			return { GL_RG32F, GL_RG, GL_FLOAT };

		// RGB Color Formats

		case EFormat::RGB8UNorm:			return { GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE };
		case EFormat::RGB8SNorm:			return { GL_RGB8_SNORM, GL_RGB, GL_BYTE };
		case EFormat::RGB8UInt:				return { GL_RGB8UI, GL_RGB_INTEGER, GL_UNSIGNED_BYTE };
		case EFormat::RGB8SInt:				return { GL_RGB8I, GL_RGB_INTEGER, GL_BYTE };

		case EFormat::RGB16UNorm:			return { GL_RGB16, GL_RGB, GL_UNSIGNED_SHORT };
		case EFormat::RGB16SNorm:			return { GL_RGB16_SNORM, GL_RGB, GL_SHORT };
		case EFormat::RGB16UInt:			return { GL_RGB16UI, GL_RGB_INTEGER, GL_UNSIGNED_SHORT };
		case EFormat::RGB16SInt:			return { GL_RGB16I, GL_RGB_INTEGER, GL_SHORT };
		case EFormat::RGB16Float:			return { GL_RGB16F, GL_RGB, GL_HALF_FLOAT };

		case EFormat::RGB32UInt:			return { GL_RGB32UI, GL_RGB_INTEGER, GL_UNSIGNED_INT };
		case EFormat::RGB32SInt:			return { GL_RGB32I, GL_RGB_INTEGER, GL_INT };
		case EFormat::RGB32Float:			return { GL_RGB32F, GL_RGB, GL_FLOAT };

		// RGBA Color Formats

		case EFormat::RGBA8UNorm:			return { GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE };
		case EFormat::RGBA8SNorm:			return { GL_RGBA8_SNORM, GL_RGBA, GL_BYTE };
		case EFormat::RGBA8UInt:			return { GL_RGBA8UI, GL_RGBA_INTEGER, GL_UNSIGNED_BYTE };
		case EFormat::RGBA8SInt:			return { GL_RGBA8I, GL_RGBA_INTEGER, GL_BYTE };

		case EFormat::RGBA16UNorm:			return { GL_RGBA16, GL_RGBA, GL_UNSIGNED_SHORT };
		case EFormat::RGBA16SNorm:			return { GL_RGBA16_SNORM, GL_RGBA, GL_SHORT };
		case EFormat::RGBA16UInt:			return { GL_RGBA16UI, GL_RGBA_INTEGER, GL_UNSIGNED_SHORT };
		case EFormat::RGBA16SInt:			return { GL_RGBA16I, GL_RGBA_INTEGER, GL_SHORT };
		case EFormat::RGBA16Float:			return { GL_RGBA16F, GL_RGBA, GL_HALF_FLOAT };

		case EFormat::RGBA32UInt:			return { GL_RGBA32UI, GL_RGBA_INTEGER, GL_UNSIGNED_INT };
		case EFormat::RGBA32SInt:			return { GL_RGBA32I, GL_RGBA_INTEGER, GL_INT };
		case EFormat::RGBA32Float:			return { GL_RGBA32F, GL_RGBA, GL_FLOAT };

		// Depth-Stencil Formats

		case EFormat::D16UNorm:				return { GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT };
		case EFormat::D24UNormS8UInt:		return { GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8 };
		case EFormat::D32Float:				return { GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT };
		case EFormat::D32FloatS8UIntX24:	return { GL_DEPTH32F_STENCIL8, GL_DEPTH_STENCIL, GL_FLOAT_32_UNSIGNED_INT_24_8_REV };

		// Unknown

		default:							return { 0, 0, 0 };
		}
	}
}

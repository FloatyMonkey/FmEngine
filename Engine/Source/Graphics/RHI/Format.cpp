// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Format.h"

namespace FM
{
	FormatInfo GetFormatInfo(EFormat format)
	{
		switch (format)
		{
		// R Color Formats                          size  c  w  h  depth  stncl  norm   compr  

		case EFormat::R8UNorm:				return {   1, 1, 1, 1, false, false, true,  false };
		case EFormat::R8SNorm:				return {   1, 1, 1, 1, false, false, true,  false };
		case EFormat::R8UInt:				return {   1, 1, 1, 1, false, false, false, false };
		case EFormat::R8SInt:				return {   1, 1, 1, 1, false, false, false, false };

		case EFormat::R16UNorm:				return {   2, 1, 1, 1, false, false, true,  false };
		case EFormat::R16SNorm:				return {   2, 1, 1, 1, false, false, true,  false };
		case EFormat::R16UInt:				return {   2, 1, 1, 1, false, false, false, false };
		case EFormat::R16SInt:				return {   2, 1, 1, 1, false, false, false, false };
		case EFormat::R16Float:				return {   2, 1, 1, 1, false, false, false, false };

		case EFormat::R32UInt:				return {   4, 1, 1, 1, false, false, false, false };
		case EFormat::R32SInt:				return {   4, 1, 1, 1, false, false, false, false };
		case EFormat::R32Float:				return {   4, 1, 1, 1, false, false, false, false };

		// RG Color Formats                         size  c  w  h  depth  stncl  norm   compr  

		case EFormat::RG8UNorm:				return {   2, 2, 1, 1, false, false, true,  false };
		case EFormat::RG8SNorm:				return {   2, 2, 1, 1, false, false, true,  false };
		case EFormat::RG8UInt:				return {   2, 2, 1, 1, false, false, false, false };
		case EFormat::RG8SInt:				return {   2, 2, 1, 1, false, false, false, false };

		case EFormat::RG16UNorm:			return {   4, 2, 1, 1, false, false, true,  false };
		case EFormat::RG16SNorm:			return {   4, 2, 1, 1, false, false, true,  false };
		case EFormat::RG16UInt:				return {   4, 2, 1, 1, false, false, false, false };
		case EFormat::RG16SInt:				return {   4, 2, 1, 1, false, false, false, false };
		case EFormat::RG16Float:			return {   4, 2, 1, 1, false, false, false, false };

		case EFormat::RG32UInt:				return {   8, 2, 1, 1, false, false, false, false };
		case EFormat::RG32SInt:				return {   8, 2, 1, 1, false, false, false, false };
		case EFormat::RG32Float:			return {   8, 2, 1, 1, false, false, false, false };

		// RGB Color Formats                        size  c  w  h  depth  stncl  norm   compr  

		case EFormat::RGB8UNorm:			return {   3, 3, 1, 1, false, false, true,  false };
		case EFormat::RGB8SNorm:			return {   3, 3, 1, 1, false, false, true,  false };
		case EFormat::RGB8UInt:				return {   3, 3, 1, 1, false, false, false, false };
		case EFormat::RGB8SInt:				return {   3, 3, 1, 1, false, false, false, false };

		case EFormat::RGB16UNorm:			return {   6, 3, 1, 1, false, false, true,  false };
		case EFormat::RGB16SNorm:			return {   6, 3, 1, 1, false, false, true,  false };
		case EFormat::RGB16UInt:			return {   6, 3, 1, 1, false, false, false, false };
		case EFormat::RGB16SInt:			return {   6, 3, 1, 1, false, false, false, false };
		case EFormat::RGB16Float:			return {   6, 3, 1, 1, false, false, false, false };

		case EFormat::RGB32UInt:			return {  12, 3, 1, 1, false, false, false, false };
		case EFormat::RGB32SInt:			return {  12, 3, 1, 1, false, false, false, false };
		case EFormat::RGB32Float:			return {  12, 3, 1, 1, false, false, false, false };

		// RGBA Color Formats                       size  c  w  h  depth  stncl  norm   compr  

		case EFormat::RGBA8UNorm:			return {   4, 4, 1, 1, false, false, true,  false };
		case EFormat::RGBA8SNorm:			return {   4, 4, 1, 1, false, false, true,  false };
		case EFormat::RGBA8UInt:			return {   4, 4, 1, 1, false, false, false, false };
		case EFormat::RGBA8SInt:			return {   4, 4, 1, 1, false, false, false, false };

		case EFormat::RGBA16UNorm:			return {   8, 4, 1, 1, false, false, true,  false };
		case EFormat::RGBA16SNorm:			return {   8, 4, 1, 1, false, false, true,  false };
		case EFormat::RGBA16UInt:			return {   8, 4, 1, 1, false, false, false, false };
		case EFormat::RGBA16SInt:			return {   8, 4, 1, 1, false, false, false, false };
		case EFormat::RGBA16Float:			return {   8, 4, 1, 1, false, false, false, false };

		case EFormat::RGBA32UInt:			return {  16, 4, 1, 1, false, false, false, false };
		case EFormat::RGBA32SInt:			return {  16, 4, 1, 1, false, false, false, false };
		case EFormat::RGBA32Float:			return {  16, 4, 1, 1, false, false, false, false };

		// RGBA Color Formats                       size  c  w  h  depth  stncl  norm   compr  

		case EFormat::D16UNorm:				return {   2, 1, 1, 1, true,  false, false, false };
		case EFormat::D24UNormS8UInt:		return {   4, 2, 1, 1, true,  true,  false, false };
		case EFormat::D32Float:				return {   4, 1, 1, 1, true,  false, false, false };
		case EFormat::D32FloatS8UIntX24:	return {   8, 2, 1, 1, true,  true,  false, false };
		
		// Unknown                                  size  c  w  h  depth  stncl  norm   compr  

		default:							return {   0, 0, 0, 0, false, false, false, false };
		}
	}
}

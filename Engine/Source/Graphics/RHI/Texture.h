// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../../Utility/CoreTypes.h"

#include "Format.h"

namespace FM
{
	struct TextureDesc
	{
		uint32 width = 1;
		uint32 height = 1;
		uint32 depth = 1;

		uint32 arraySize = 1;
		uint32 sampleCount = 1;
		uint32 mipLevels = 1;

		// OpenGL always assumes 2D
		// TODO: 1D, 2D, 3D, CubeMap

		EFormat format = EFormat::Unknown;

		void* data = nullptr;
	};
}

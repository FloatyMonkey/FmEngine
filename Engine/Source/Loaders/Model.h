// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../Utility/CoreTypes.h"
#include "../Utility/Math/Math.h"
#include "../Utility/Memory.h"

#include <vector>

namespace FM
{
	struct Vertex
	{
		Vector3 position;
		Vector3 normal;
		Vector2 texcoord;
	};

	struct SubMesh
	{
		uint32 offset;
		uint32 count;
	};

	class ModelLoader
	{
	public:

		static void Load(const char* path, std::vector<Vertex>& vertices, std::vector<unsigned long>& indices);
	};
}

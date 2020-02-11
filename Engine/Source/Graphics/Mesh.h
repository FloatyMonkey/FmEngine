// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../Utility/Math/Math.h"

#include <vector>

namespace FM
{
	class Mesh
	{
	public:

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

		~Mesh();

		void Load(const char* filepath);

	public:

		uint32 vertexBuffer = 0;
		uint32 indexBuffer = 0;

		std::vector<SubMesh> mSubMeshes;
		std::vector<Vertex> mVertices;
		std::vector<uint32> mIndices;
	};
}

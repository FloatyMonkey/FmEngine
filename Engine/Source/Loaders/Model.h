// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

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

		bool operator<(const Vertex that) const {
			return Memory::Memcmp((void*)this, (void*)&that, sizeof(Vertex)) > 0;
		};
	};

	class ModelLoader
	{
	public:

		static bool LoadOBJ(const char *path, std::vector<Vertex>& vertices);

		static void IndexOBJ(std::vector<Vertex>& vertices, std::vector<unsigned long>& newIndices, std::vector<Vertex>& newVertices);
	};
}

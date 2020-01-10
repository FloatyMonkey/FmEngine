// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Model.h"

#include "../Utility/Logger/Log.h"

#include <fstream>

namespace FM
{
	void ModelLoader::Load(const char* path, std::vector<Vertex>& vertices, std::vector<unsigned long>& indices)
	{
		std::ifstream file(path, std::ios::binary);

		if (!file)
		{
			FM_LOG(Error) << "Failed to load binary mesh: " << path;
		}

		uint32 subMeshCount;
		uint32 vertexCount;
		uint32 indexCount;

		file.read(reinterpret_cast<char*>(&subMeshCount), sizeof(subMeshCount));
		file.read(reinterpret_cast<char*>(&vertexCount), sizeof(vertexCount));
		file.read(reinterpret_cast<char*>(&indexCount), sizeof(indexCount));

		vertices.resize(vertexCount);
		indices.resize(indexCount);

		file.ignore(sizeof(SubMesh) * subMeshCount);
		file.read(reinterpret_cast<char*>(&vertices[0]), sizeof(Vertex)* vertexCount);
		file.read(reinterpret_cast<char*>(&indices[0]), sizeof(uint32)* indexCount);
	}
}

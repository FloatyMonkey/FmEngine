// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Mesh.h"

#include "../ThirdParty/Glad/glad.h"

#include <fstream>

namespace FM
{
	void Mesh::Load(const char* filepath)
	{
		std::ifstream file(filepath, std::ios::binary);

		uint32 subMeshCount;
		uint32 vertexCount;
		uint32 indexCount;

		file.read(reinterpret_cast<char*>(&subMeshCount), sizeof(subMeshCount));
		file.read(reinterpret_cast<char*>(&vertexCount), sizeof(vertexCount));
		file.read(reinterpret_cast<char*>(&indexCount), sizeof(indexCount));

		mSubMeshes.resize(subMeshCount);
		mVertices.resize(vertexCount);
		mIndices.resize(indexCount);

		file.read(reinterpret_cast<char*>(&mSubMeshes[0]), sizeof(SubMesh) * subMeshCount);
		file.read(reinterpret_cast<char*>(&mVertices[0]), sizeof(Vertex) * vertexCount);
		file.read(reinterpret_cast<char*>(&mIndices[0]), sizeof(uint32) * indexCount);

		// TODO: Move GL code somewhere else.

		glGenBuffers(1, &vertexBuffer);
		glGenBuffers(1, &indexBuffer);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(uint32), &mIndices[0], GL_STATIC_DRAW);
	}

	Mesh::~Mesh()
	{
		glDeleteBuffers(1, &vertexBuffer);
		glDeleteBuffers(1, &indexBuffer);
	}
}

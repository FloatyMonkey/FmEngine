// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Model.h"

#include "../Utility/CoreTypes.h"
#include "../Utility/Logger/Log.h"

#include <map>
#include <fstream>
#include <iostream>

// TODO: Don't use old c-style file access.
// _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

namespace FM
{
	bool ModelLoader::LoadOBJ(const char * path, std::vector<Vertex>& vertices)
	{
		std::vector<unsigned int> vertexIndices, normalIndices, uvIndices;

		std::vector<Vector3> positions;
		std::vector<Vector3> normals;
		std::vector<Vector2> uvs;

		FILE * file = fopen(path, "r");
		if (file == NULL)
		{
			std::cout << "Could not find OBJ file: " << path << std::endl;
			return 0;
		}

		while (true)
		{
			char lineHeader[128];

			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF) break;

			if (strcmp(lineHeader, "v") == 0)
			{
				Vector3 position;
				fscanf(file, "%f %f %f\n", &position.x, &position.y, &position.z);
				positions.push_back(position);
			}
			else if (strcmp(lineHeader, "vt") == 0)
			{
				Vector2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				uvs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0)
			{
				Vector3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				normals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0)
			{
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

				if (matches != 9)
				{
					std::cout << "Could not parse OBJ file: " << path << std::endl;
					return false;
				}

				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);

				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);

				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}

		for (unsigned int i = 0; i < vertexIndices.size(); i++)
		{
			unsigned int vertexIndex = vertexIndices[i];
			unsigned int normalIndex = normalIndices[i];
			unsigned int uvIndex = uvIndices[i];

			Vertex vertex;

			vertex.position = positions[vertexIndex - 1];
			vertex.normal = normals[normalIndex - 1];
			vertex.texcoord = uvs[uvIndex - 1];

			vertices.push_back(vertex);
		}

		return true;
	}

	void ModelLoader::IndexOBJ(std::vector<Vertex>& vertices, std::vector<unsigned long>& newIndices, std::vector<Vertex>& newVertices)
	{
		std::map<Vertex, unsigned int> vertexToOutIndex;

		for (unsigned int i = 0; i < vertices.size(); i++)
		{
			Vertex vertex = vertices[i];

			std::map<Vertex, unsigned int>::iterator it = vertexToOutIndex.find(vertex);

			// If vertex already exists, only add index, else add index and nex vertex.
			if (it == vertexToOutIndex.end())
			{
				unsigned int index = (unsigned int)newVertices.size();

				newVertices.push_back(vertices[i]);
				newIndices.push_back(index);

				vertexToOutIndex[vertex] = index;
			}
			else
			{
				newIndices.push_back(it->second);
			}
		}
	}
}

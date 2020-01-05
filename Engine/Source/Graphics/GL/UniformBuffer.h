// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../../ThirdParty/Glad/glad.h"

// TODO: Move implementation to CPP file.

namespace FM
{
	class UniformBuffer
	{
	public:

		unsigned int ID;
		unsigned int size;

		UniformBuffer() = default;

		UniformBuffer(int size)
		{
			this->size = size;
			glGenBuffers(1, &ID);
			glBindBuffer(GL_UNIFORM_BUFFER, ID);
			glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

		void Update(void* data)
		{
			glBindBuffer(GL_UNIFORM_BUFFER, ID);
			GLvoid* p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
			memcpy(p, data, size);
			glUnmapBuffer(GL_UNIFORM_BUFFER);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

		void Bind(int index)
		{
			glBindBufferBase(GL_UNIFORM_BUFFER, index, ID);
		}
	};
}

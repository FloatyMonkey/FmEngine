// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../Format.h"

// TODO: Don't include this here.
#include "../../../ThirdParty/Glad/glad.h"

namespace FM::OpenGL
{
	struct GLFormatInfo
	{
		GLenum internalFormat;
		GLenum format;
		GLenum type;
	};

	GLFormatInfo Map(EFormat format);
}

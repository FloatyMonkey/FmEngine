// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Image.h"

#include <iostream>

#include "../ThirdParty/stb/stb_image.h"

namespace FM
{
	Image::Image()
		: mWidth(0)
		, mHeight(0)
		, mChannels(0)
		, mPixels(nullptr)
	{}

	Image::Image(const char* filename, int channels)
	{
		mPixels = stbi_load(filename, &mWidth, &mHeight, &mChannels, channels);

		if (channels > 0)
		{
			mChannels = channels;
		}

		if (!mPixels)
		{
			std::cout << "Failed to load image file: " << filename << std::endl;
		}
	}

	Image::~Image()
	{
		if (mPixels) delete mPixels;
	}
}

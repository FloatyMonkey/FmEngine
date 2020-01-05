// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

namespace FM
{
	class Image
	{
	public:

		Image();
		Image(const char* filename, int channels = 4);

		~Image();

		int Width() const { return mWidth; }
		int Height() const { return mHeight; }
		int Channels() const { return mChannels; }
		int BytesPerPixel() const { return mChannels * sizeof(unsigned char); }
		int RowPitch() const { return mWidth * BytesPerPixel(); }

		unsigned char* GetPixels() const { return mPixels; }

	private:

		int mWidth;
		int mHeight;
		int mChannels;

		// TODO: Raw pointer, not managed correct when Image gets copied!
		unsigned char* mPixels;
	};
}

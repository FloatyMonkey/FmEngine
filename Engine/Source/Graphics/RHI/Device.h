// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

namespace FM
{
	struct TextureDesc;
	struct SamplerDesc;

	struct HTexture
	{
		HTexture() : id(0) {}
		HTexture(unsigned int id) : id(id) {}

		unsigned int id;
	};

	struct HSampler
	{
		HSampler() : id(0) {}
		HSampler(unsigned int id) : id(id) {}

		unsigned int id;
	};

	class IDevice
	{
	public:

		virtual HTexture CreateTexture(const TextureDesc& desc) = 0;
		virtual HSampler CreateSampler(const SamplerDesc& desc) = 0;

		virtual void DestroyTexture(HTexture texture) = 0;
		virtual void DestroySampler(HSampler sampler) = 0;
	};
}

// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../Device.h"

namespace FM::OpenGL
{
	class Device : public IDevice
	{
	public:

		virtual HTexture CreateTexture(const TextureDesc& desc) override;
		virtual HSampler CreateSampler(const SamplerDesc& desc) override;

		virtual void DestroyTexture(HTexture texture) override;
		virtual void DestroySampler(HSampler sampler) override;

		// Pipeline
		// Texture
		// Buffer

		// TODO: Destroy functions
	};
}

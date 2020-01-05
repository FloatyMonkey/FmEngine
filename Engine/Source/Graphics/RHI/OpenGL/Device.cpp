// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "Device.h"

#include "../../../ThirdParty/Glad/glad.h"

#include "Format.h"

#include "../Texture.h"
#include "../Sampler.h"

namespace FM::OpenGL
{
	// --------- TEXTURE --------

	HTexture Device::CreateTexture(const TextureDesc& desc)
	{
		GLuint id;

		GLFormatInfo info = Map(desc.format);

		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, info.internalFormat, desc.width, desc.height, 0, info.format, info.type, desc.data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		return HTexture(id);
	}

	void Device::DestroyTexture(HTexture texture)
	{
		glDeleteTextures(1, &texture.id);
	}

	// --------- SAMPLER --------

	GLenum NativeCast(EComparisonFunc comparisonFunc)
	{
		switch (comparisonFunc)
		{
		case EComparisonFunc::Never:		return GL_NEVER;
		case EComparisonFunc::Always:		return GL_ALWAYS;
		case EComparisonFunc::Equal:		return GL_EQUAL;
		case EComparisonFunc::NotEqual:		return GL_NOTEQUAL;
		case EComparisonFunc::Less:			return GL_LESS;
		case EComparisonFunc::LessEqual:	return GL_LEQUAL;
		case EComparisonFunc::Greater:		return GL_GREATER;
		case EComparisonFunc::GreaterEqual:	return GL_GEQUAL;
		}
	}

	GLenum NativeCast(ETextureAddressMode textureAddressMode)
	{
		switch (textureAddressMode)
		{
		case ETextureAddressMode::Repeat:		return GL_REPEAT;
		case ETextureAddressMode::Mirror:		return GL_MIRRORED_REPEAT;
		case ETextureAddressMode::MirrorOnce:	return GL_MIRROR_CLAMP_TO_EDGE;
		case ETextureAddressMode::Clamp:		return GL_CLAMP_TO_EDGE;
		case ETextureAddressMode::Border:		return GL_CLAMP_TO_BORDER;
		}
	}

	GLenum NativeCast(ETextureFilter textureFilter)
	{
		switch (textureFilter)
		{
		case ETextureFilter::Point:		return GL_NEAREST;
		case ETextureFilter::Linear:	return GL_LINEAR;
		}
	}

	GLenum NativeCast(ETextureFilter minFilter, ETextureFilter mipFilter)
	{
		if (minFilter == ETextureFilter::Point)
		{
			if (mipFilter == ETextureFilter::Point)		return GL_NEAREST_MIPMAP_NEAREST;
			if (mipFilter == ETextureFilter::Linear)	return GL_NEAREST_MIPMAP_LINEAR;
		}

		if (minFilter == ETextureFilter::Linear)
		{
			if (mipFilter == ETextureFilter::Point)		return GL_LINEAR_MIPMAP_NEAREST;
			if (mipFilter == ETextureFilter::Linear)	return GL_LINEAR_MIPMAP_LINEAR;
		}
	}

	HSampler Device::CreateSampler(const SamplerDesc& desc)
	{
		GLuint id;

		glGenSamplers(1, &id);

		glSamplerParameteri(id, GL_TEXTURE_MIN_FILTER, NativeCast(desc.minFilter, desc.mipFilter));
		glSamplerParameteri(id, GL_TEXTURE_MAG_FILTER, NativeCast(desc.magFilter));

		glSamplerParameteri(id, GL_TEXTURE_WRAP_S, NativeCast(desc.addressU));
		glSamplerParameteri(id, GL_TEXTURE_WRAP_T, NativeCast(desc.addressV));
		glSamplerParameteri(id, GL_TEXTURE_WRAP_R, NativeCast(desc.addressW));

		glSamplerParameterf(id, GL_TEXTURE_MIN_LOD, desc.minLod);
		glSamplerParameterf(id, GL_TEXTURE_MAX_LOD, desc.maxLod);
		glSamplerParameterf(id, GL_TEXTURE_LOD_BIAS, desc.mipLodBias);

		glSamplerParameterf(id, GL_TEXTURE_MAX_ANISOTROPY, static_cast<float>(desc.maxAnisotropy));

		glSamplerParameteri(id, GL_TEXTURE_COMPARE_MODE, (desc.comparisonFunc == EComparisonFunc::Disabled) ? GL_NONE : GL_COMPARE_REF_TO_TEXTURE);
		glSamplerParameteri(id, GL_TEXTURE_COMPARE_FUNC, NativeCast(desc.comparisonFunc));

		glSamplerParameterfv(id, GL_TEXTURE_BORDER_COLOR, &desc.borderColor.rgba[0]);

		return HSampler(id);
	}
	
	void Device::DestroySampler(HSampler sampler)
	{
		glDeleteSamplers(1, &sampler.id);
	}
}

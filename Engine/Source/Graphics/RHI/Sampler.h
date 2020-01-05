// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../../Utility/CoreTypes.h"
#include "../../Utility/Math/Color.h"

#include "Pipeline.h" // TODO: Don't include the entire pipeline.

namespace FM
{
	/// Defines the filtering options for texture sampling.
	enum class ETextureFilter
	{
		Point,	///< Take the nearest texture sample.
		Linear	///< Interpolate between multiple texture samples.
	};

	/// Defines the addressing mode for texture coordinates outside of the [0, 1] range.
	enum class ETextureAddressMode
	{
		Repeat,		///< Repeat the texture at every integer junction.
		Mirror,		///< Repeat the texture and mirror at every integer junction.
		MirrorOnce,	///< Repeat the texture and mirror only once around the origin.
		Border,		///< Use the sampler's border color.
		Clamp		///< Use the texture color at [0, 1].
	};

	/// Describes a sampler state.
	struct SamplerDesc
	{
		/// The minification filter.
		ETextureFilter minFilter = ETextureFilter::Point;

		/// The magnification filter.
		ETextureFilter magFilter = ETextureFilter::Point;

		/// The mip-mapping filter.
		ETextureFilter mipFilter = ETextureFilter::Point;

		/// The texture addressing mode in the U direction (X axis).
		ETextureAddressMode addressU = ETextureAddressMode::Repeat;

		/// The texture addressing mode in the V direction (Y axis).
		ETextureAddressMode addressV = ETextureAddressMode::Repeat;

		/// The texture addressing mode in the W direction (Z axis).
		ETextureAddressMode addressW = ETextureAddressMode::Repeat;

		/// Lower end of the mipmap range.
		/// The largest and most detailed mipmap level is 0. Any level higher than 0 is less detailed.
		float minLod = 0;

		/// Upper end of the mipmap range
		/// The largest and most detailed mipmap level is 0. Any level higher than 0 is less detailed.
		/// This value must be greater than or equal to minLod.
		/// Set this member to a large value to have no upper LOD limit.
		float maxLod = 1024;

		/// Offset from the calculated mipmap level.
		/// For example, when the mipLodBias is 2 a texture won't get sampled at mipmap level 3 but at level 5.
		float mipLodBias = 0;

		/// Clamping value for the comparison.
		/// Values should be in the [1, 16] range.
		uint32 maxAnisotropy = 1;

		/// The function that compares sampled data against existing sampled data.
		EComparisonFunc comparisonFunc = EComparisonFunc::Never;

		/// Border color to use when TextureAddressMode::Border is set for addressU, addressV or addressW.
		Color borderColor = Color::Black;
	};
}

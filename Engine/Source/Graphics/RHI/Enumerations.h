// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

namespace FM
{
	/// Defines how to modulate values for the pixel shader and render target.
	/// Src is the pixel shaders output color.
	/// Dst is the render targets color.
	enum class EBlend
	{
		Zero,			///< f(src, dst) = 0
		One,			///< f(src, dst) = 1
		SrcColor,		///< f(src, dst) = src
		InvSrcColor,	///< f(src, dst) = 1 - src
		SrcAlpha,		///< f(src, dst) = src.a
		InvSrcAlpha,	///< f(src, dst) = 1 - src.a
		DstColor,		///< f(src, dst) = dst
		InvDstColor,	///< f(src, dst) = 1 - dst
		DstAlpha,		///< f(src, dst) = dst.a
		InvDstAlpha,	///< f(src, dst) = 1 - dst.a
		Src1Color,		///< f(src, dst) = 
		InvSrc1Color,	///< f(src, dst) = 
		Src1Alpha,		///< f(src, dst) = 
		InvSrc1Alpha,	///< f(src, dst) = 
		SrcAlphaSat		///< f(src, dst) = (1,1,1) * min(src.a, 1 - dst.a), 1
	};

	/// Defines how to combine the blend inputs.
	enum class EBlendOp
	{
		Add,			///< Add source 1 and source 2.
		Subtract,		///< Subtract source 1 from source 2.
		RevSubtract,	///< Subtract source 2 from source 1.
		Min,			///< Find the minimum of the two sources (per channel).
		Max				///< Find the maximum of the two sources (per channel).
	};

	/// Defines comparison functions.
	enum class EComparisonFunc
	{
		Disabled,		///< No comparison, regular filtering.
		Never,			///< Passes never.
		Always,			///< Passes always.
		Equal,			///< Passes if source data is equal to destination data.
		NotEqual,		///< Passes if source data is not equal to destination data.
		Less,			///< Passes if source data is less than destination data.
		LessEqual,		///< Passes if source data is less than or equal to destination data.
		Greater,		///< Passes if source data is greater than destination data.
		GreaterEqual	///< Passes if source data is greater than or equal to destination data.
	};

	/// Defines which direction polygons should face in order to be drawn.
	enum class ECullMode
	{
		None,	///< Draw all polygons.
		Front,	///< Don't draw front-facing polygons.
		Back	///< Don't draw back-facing polygons.
	};

	/// Defines how to fill polygons.
	enum class EFillMode
	{
		Wireframe,	///< Draw lines connecting the vertices.
		Solid		///< Fill the polygons formed by the vertices.
	};

	/// Defines logical operations for render targets.
	enum class ELogicOp
	{
		Disabled,	///< No operation is performed.
		Clear,		///< Operation: 0.
		Set,		///< Operation: 1.
		Copy,		///< Operation: Src.
		CopyInv,	///< Operation: ~Src.
		Inv,		///< Operation: ~Dst.
		And,		///< Operation: Src & Dst.
		Nand,		///< Operation: ~(Src & Dst).
		Or,			///< Operation: Src | Dst.
		Nor,		///< Operation: ~(Src | Dst).
		Xor,		///< Operation: Src ^ Dst.
		Equiv,		///< Operation: ~(Src ^ Dst).
		AndRev,		///< Operation: Src & ~Dst.
		AndInv,		///< Operation: ~Src & Dst.
		OrRev,		///< Operation: Src | ~Dst.
		OrInv		///< Operation: ~Src | Dst.
	};

	/// Defines stencil operations that can be performed during stencil testing.
	enum class EStencilOp
	{
		Keep,		///< Keep the existing stencil data.
		Zero,		///< Set the stencil data to 0.
		Replace,	///< Replace the stencil data with the reference value.
		Incr,		///< Increment the stencil value by 1, wrap if necessary.
		IncrSat,	///< Increment the stencil value by 1, clamp if necessary.
		Decr,		///< Decrement the stencil value by 1, wrap if necessary.
		DecrSat,	///< Decrement the stencil value by 1, clamp if necessary.
		Inv			///< Invert the stencil data.
	};
}

// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#pragma once

#include "../../Utility/CoreTypes.h"

#include "Format.h"
#include "Enumerations.h"

namespace FM
{
	/// Defines the primitive topology and ordering of the primitive data.
	enum class EPrimitiveTopology
	{
		PointList,			///< Every vertex represents a single point.
		LineList,			///< Every pair of vertices represents a single line.
		LineStrip,			///< Every vertex creates a new line while the previous vertex is used as starting point.
		LineListAdj,		///< Similar to LineList but each end point has a corresponding adjacent vertex that is accessible in a geometry shader.
		LineStripAdj,		///< Similar to LineStrip but each end point has a corresponding adjacent vertex that is accessible in a geometry shader.
		TriangleList,		///< Every trio of vertices represent a single triangle.
		TriangleStrip,		///< Every vertex creates a new triangle with an alternating winding.
		TriangleListAdj,	///< Similar to TriangleList but each edge has a corresponding adjacent vertex that is accessible in a geometry shader.
		TriangleStripAdj,	///< Similar to TriangleStrip but each edge has a corresponding adjacent vertex that is accessible in a geometry shader.
		PatchList			///< Patches with n control points that are accessible in a tessellation shader.
	};

	// ----------------------------------------------------------------
	// SHADER BINARY
	// ----------------------------------------------------------------

	struct ShaderBinary
	{
		/// A pointer to a memory block that contains the shader bytecode.
		const void* byteCode = nullptr;

		/// The size in bytes of the bytecode that byteCode points to.
		uint32 byteCodeSize = 0;
	};

	// ----------------------------------------------------------------
	// INPUT LAYOUT
	// ----------------------------------------------------------------

	/// Defines the type of data contained in an input slot.
	enum class EInputClassification
	{
		PerVertex,	///< Input data is per-vertex.
		PerInstance	///< Input data is per-instance.
	};

	// TODO: Finish this and add documentation

	struct InputElementDesc
	{
		const char* name = nullptr;
		uint8 index = 0;
		EFormat format = EFormat::Unknown;
		uint8 slot = 0;
	};

	// TODO: Add documentation

	struct InputLayoutDesc
	{

		/// An array of InputElementDesc structures.
		const InputElementDesc* inputElementDescs = nullptr;

		/// The number of elements in the inputElementDescs array.
		uint32 numElements = 0;
	};

	// ----------------------------------------------------------------
	// VIEWPORT
	// ----------------------------------------------------------------

	/// Describes the dimensions of a viewport.
	struct Viewport
	{
		/// Top left X coordinate of the viewport.
		float x = 0.0f;

		/// Top left Y coordinate of the viewport.
		float y = 0.0f;

		/// Width of the viewport.
		float width = 0.0f;

		/// Height of the viewport.
		float height = 0.0f;

		/// Minimum depth of the viewport in the [0, 1] range.
		/// Reverse mappings are also valid eg. minDepth = 1 and maxDepth = 0.
		float minDepth = 0.0f;

		/// Maximum depth of the viewport in the [0, 1] range.
		/// Reverse mappings are also valid eg. minDepth = 1 and maxDepth = 0.
		float maxDepth = 1.0f;
	};

	// ----------------------------------------------------------------
	// SCISSOR
	// ----------------------------------------------------------------

	/// Describes the dimensions of a scissor rectangle.
	struct Scissor
	{
		/// Top left X coordinate of the scissor rectangle.
		float x = 0.0f;

		/// Top left Y coordinate of the scissor rectangle.
		float y = 0.0f;

		/// Width of the scissor rectangle.
		float width = 0.0f;

		/// Height of the scissor rectangle.
		float height = 0.0f;
	};

	// ----------------------------------------------------------------
	// BLEND DESC
	// ----------------------------------------------------------------

	/// Describes the blend state for a single render target.
	struct RenderTargetBlendDesc
	{
		/// Whether to enable blending.
		bool enabled = false;

		/// The operation to perform on the RGB value that the pixel shader outputs.
		EBlend srcColor = EBlend::One;

		/// The operation to perform on the current RGB value in the render target.
		EBlend dstColor = EBlend::Zero;

		/// Specifies how to combine the srcColor and dstColor operations.
		EBlendOp colorOp = EBlendOp::Add;

		/// The operation to perform on the alpha value that the pixel shader outputs.
		/// Blend functions that end with ...Color are not allowed.
		EBlend srcAlpha = EBlend::One;

		/// The operation to perform on the current alpha value in the render target.
		/// Blend functions that end with ...Color are not allowed.
		EBlend dstAlpha = EBlend::Zero;

		/// Specifies how to combine the srcAlpha and dstBlend operations.
		EBlendOp alphaOp = EBlendOp::Add;

		/// The color components which are enabled for writing.
		uint8 writeMask;
	};

	/// Describes the blend state.
	struct BlendDesc
	{
		/// Whether to enable independent blending in simultaneous render targets.
		/// If false, only the renderTarget[0] members are used.
		bool independentBlendEnabled = false;

		/// The logical operation for the render targets.
		ELogicOp logicOp = ELogicOp::Disabled;

		/// The blend state for each render target.
		/// These represent the 8 render targets that can be bound to the output-merger state.
		RenderTargetBlendDesc renderTarget[8];
	};

	// ----------------------------------------------------------------
	// DEPTH DESC
	// ----------------------------------------------------------------

	/// Describes the depth state.
	struct DepthDesc
	{
		/// Whether to enable depth testing.
		bool enabled = true;

		/// Whether to write depth values into the depth buffer.
		bool writeEnabled = true;

		/// Function that compares depth data against existing depth data.
		EComparisonFunc comparisonFunc = EComparisonFunc::Less;
	};

	// ----------------------------------------------------------------
	// STENCIL DESC
	// ----------------------------------------------------------------

	/// Describes stencil operations for front- or back facing polygons.
	struct StencilFaceDesc
	{
		/// Stencil operation when stencil test fails.
		EStencilOp stencilFailOp = EStencilOp::Keep;

		/// Stencil operation when stencil test passes but depth test fails.
		EStencilOp stencilDepthFailOp = EStencilOp::Keep;

		/// Stencil operation when stencil and depth tests pass.
		EStencilOp stencilPassOp = EStencilOp::Keep;

		/// Function that compares stencil data against existing stencil data.
		EComparisonFunc comparisonFunc = EComparisonFunc::Always;
	};

	/// Describes the stencil state.
	struct StencilDesc
	{
		/// Whether to enable stencil testing.
		bool enabled = false;

		/// Specifies a part of the depth-stencil buffer for reading stencil data.
		uint8 readMask = 0xFF;

		/// Specifies a part of the depth-stencil buffer for writing stencil data.
		uint8 writeMask = 0xFF;

		/// Specifies stencil settings for front facing polygons.
		StencilFaceDesc frontFace;

		/// Specifies stencil settings for back facing polygons.
		StencilFaceDesc backFace;
	};

	// ----------------------------------------------------------------
	// RASTERIZER DESC
	// ----------------------------------------------------------------

	/// Describes how to bias pixel depth values.
	struct DepthBiasDesc
	{
		/// The depth value added to a pixel.
		float constant = 0.0f;

		/// The scalar factor applied to a pixel's slope.
		float slope = 0.0f;

		/// The maximum depth bias of a pixel.
		float clamp = 0.0f;
	};

	/// Describes how to multisample pixels.
	struct MultiSamplingDesc
	{
		/// The number of multisamples per pixel.
		/// This value must be a power of 2 in the [1, 32] range.
		/// When set to 1, multisampling is disabled.
		uint32 sampleCount = 1;

		/// Whether to use alpha-to-coverage as a multisampling technique.
		bool alphaToCoverageEnabled = false;
	};

	/// Describes the rasterizer state.
	struct RasterizerDesc
	{
		/// Specifies how to fill polygons.
		EFillMode fillMode = EFillMode::Solid;

		/// Specifies which direction polygons should face in order to be drawn.
		ECullMode cullMode = ECullMode::Back;

		/// Specifies if a polygon is front- or back facing.
		/// If true, front facing polygons are in counterclockwise winding, else in clockwise winding.
		bool frontCCW = false;

		/// Specifies how to bias pixel depth values.
		DepthBiasDesc depthBias;

		/// Specifies how to multisample pixels.
		MultiSamplingDesc multiSampling;

		/// Whether to clip or cull vertices based on depth.
		/// If true, there are no near and far clipping planes.
		bool depthClipEnabled = false;

		/// Whether to enable line antialiasing.
		bool antiAliasedLineEnabled = false;

		/// Whether to enable conservative rasterization.
		bool conservativeRasterizerEnabled = false;
	};

	// ----------------------------------------------------------------
	// TESSELATION DESC
	// ----------------------------------------------------------------

	/// Describes the tesselation state.
	struct TessellationDesc
	{
		/// Tessellation control point count in the [1, 32] range.
		/// This gets used when the primitiveTopology is set to PatchList.
		uint32 patchControlCount = 1;
	};

	// ----------------------------------------------------------------
	// GRAPHICS PIPELINE DESC
	// ----------------------------------------------------------------

	struct GraphicsPipelineDesc
	{
		EPrimitiveTopology	primitiveTopology = EPrimitiveTopology::TriangleList;

		ShaderBinary		vertexShader;
		ShaderBinary		geometryShader;
		ShaderBinary		domainShader;
		ShaderBinary		hullShader;
		ShaderBinary		pixelShader;

		BlendDesc			blend;
		DepthDesc			depth;
		StencilDesc			stencil;
		RasterizerDesc		rasterizer;
		TessellationDesc	tesselation;
		MultiSamplingDesc	multiSample;
	};

	// ----------------------------------------------------------------
	// INTERFACES
	// ----------------------------------------------------------------

	class IPipelineState
	{

	};
}

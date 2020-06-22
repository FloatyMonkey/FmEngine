// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

struct VS_INPUT
{
    float3 position : POSITION;
	float3 normal : NORMAL;
    float2 texCoord: TEXCOORD;
};

struct PS_INPUT
{
    float4 pxPosition : SV_POSITION;
    float3 position : POSITION;
	float3 normal : NORMAL;
    float2 texCoord : TEXCOORD;
};

struct BufferVertex
{
    float4x4 model;
    float4x4 view;
    float4x4 projection;
};

ConstantBuffer<BufferVertex> data : register(b0);

void main(in VS_INPUT input, out PS_INPUT output)
{
    output.position = mul(data.model, float4(input.position, 1.0)).xyz;
    output.normal = mul((float3x3)data.model, input.normal);
	output.texCoord = float2(input.texCoord.x, -input.texCoord.y); // Inverse Y for OpenGL

    output.pxPosition = mul(data.projection, mul(data.view, float4(output.position, 1.0)));
}

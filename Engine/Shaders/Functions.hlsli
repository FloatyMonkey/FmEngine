// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#ifndef INC_FUNCTIONS
#define INC_FUNCTIONS

uint PackColor(float4 fColor)
{
	uint uColor = 0;

	uColor |= (uint)(fColor.r * 255.0) << 24;
	uColor |= (uint)(fColor.g * 255.0) << 16;
	uColor |= (uint)(fColor.b * 255.0) << 8;
	uColor |= (uint)(fColor.a * 255.0) << 0;

	return uColor;
}

float4 UnpackColor(uint uColor)
{
	float4 fColor;

	fColor.r = (float)((uColor >> 24) & 0xFF);
	fColor.g = (float)((uColor >> 16) & 0xFF);
	fColor.b = (float)((uColor >> 8 ) & 0xFF);
	fColor.a = (float)((uColor >> 0 ) & 0xFF);

	return fColor / 255.0;
}

// Computes a flat shaded normal for a surface using screen-space derivatives.
float3 FlatNormal(float3 position)
{
	return normalize(cross(ddx(position), ddy(position)));
}

// Computes a tangent-basis matrix for a surface using screen-space derivatives.
float3x3 ComputeTBN(float3 position, float3 normal, float2 texCoord)
{
	float3 dP1 = ddx(position);
	float3 dP2 = ddy(position);
	float2 dUv1 = ddx(texCoord);
	float2 dUv2 = ddy(texCoord);

	float3x3 M = float3x3(dP1, dP2, cross(dP1, dP2));
	float2x3 invM = float2x3(cross(M[1], M[2]), cross(M[2], M[0]));

	float3 T = normalize(mul(float2(dUv1.x, dUv2.x), invM));
	float3 B = normalize(mul(float2(dUv1.y, dUv2.y), invM));
	float3 N = normalize(normal);

	//float3 N = normalize(normal);
	//float3 T = normalize(dP1 * dUv2.y - dP2 * dUv1.y);
	//float3 B = normalize(cross(T, N));

	return float3x3(T, B, N);
}

#endif // INC_FUNCTIONS

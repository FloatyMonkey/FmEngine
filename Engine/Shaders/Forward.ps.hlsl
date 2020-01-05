// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#include "BRDF.hlsli"
#include "Functions.hlsli"

struct PS_INPUT
{
    float4 pxPosition : SV_POSITION;
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD;
};

struct BufferPixel
{
    float3 viewPos;
    float3 lightPos;
};

ConstantBuffer<BufferPixel> data : register(b1);

Texture2D baseColorMap : register(t0);
Texture2D roughnessMap : register(t1);
Texture2D metallicMap : register(t2);
Texture2D normalMap : register(t3);

SamplerState s1 : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	float3 baseColor = pow(baseColorMap.Sample(s1, input.texCoord).rgb, 2.2);
	float roughness = roughnessMap.Sample(s1, input.texCoord).r;
	float metallic = metallicMap.Sample(s1, input.texCoord).r;

	float3x3 TBN = ComputeTBN(input.position, input.normal, input.texCoord);
	float3 normal = normalMap.Sample(s1, input.texCoord).rgb * 2.0 - 1.0;
	normal = normalize(mul(normal, TBN));

	// TODO: Check if Wi is calculated correctly!

	float3 N = normal;
	float3 V = normalize(data.viewPos - input.position);

	float3 L = normalize(data.lightPos - input.position);
    float3 H = normalize(V + L);

    float NoV = abs(dot(N, V)) + 1e-5;
    float NoL = saturate(dot(N, L));
    float NoH = saturate(dot(N, H));
    float LoH = saturate(dot(L, H));

    float3 lightColor = float3(1, 1, 1);

	float reflectance = 0.5;

	// roughness [0:smooth -> 1 1:rough] (perceptually linear)
	float a = roughness * roughness;
	float a2 = a * a;

	float3 albedo = (1.0 - metallic) * baseColor;
	float3 f0 = 0.16 * reflectance * reflectance * (1.0 - metallic) + baseColor * metallic;

	float3 Fd = Fd_Disney(albedo, roughness, NoV, NoL, LoH);
	float3 Fr = Fr_CookTorrance(NoV, NoL, LoH, NoH, f0, a2);

	// Point Light

	float dst = length(data.lightPos - input.position);
    float attenuation = 1.0 / (dst * dst);
    float3 radiance = 50 * lightColor * attenuation;

	float3 color = (Fd + Fr) * radiance * NoL;

	// HDR tonemapping
	color = color / (color + 1.0);

	// Gamma correct
	color = pow(color, 1.0 / 2.2);

	return float4(color, 1.0);
}

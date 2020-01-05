// Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
// Licensed under the MIT license. See LICENSE.md for full terms. This notice is not to be removed.

#ifndef INC_BRDF
#define INC_BRDF

#include "Math.hlsli"

// Normal Distribution Function (Fr D)

float D_GGX(float a2, float NoH)
{
	float t = (NoH * a2 - NoH) * NoH + 1.0;

	return a2 / (PI * t * t);
}

// Fresnel Function (Fr F)

float3 F_Schlick(float VoH, float3 f0, float f90)
{
    return f0 + (f90 - f0) * pow(1.0 - VoH, 5.0);
}

float F_Schlick(float VoH, float f0, float f90)
{
    return f0 + (f90 - f0) * pow(1.0 - VoH, 5.0);
}

// Visibility Function (Fr V)

float V_SmithGGXCorrelated(float NoV, float NoL, float a2)
{
	float GGXV = NoL * sqrt((NoV - NoV * a2) * NoV + a2);
	float GGXL = NoV * sqrt((NoL - NoL * a2) * NoL + a2);

	return 0.5 / (GGXV + GGXL);
}

float V_Kelemen(float LoH)
{
    return rcp(4.0 * LoH * LoH + 1e-5);
}

float V_Neubelt(float NoV, float NoL)
{
	return rcp(4.0 * (NoL + NoV - NoL * NoV) + 1e-5);
}

// BRDF Diffuse (Fd)

float3 Fd_Lambert(float3 albedo)
{
    return albedo / PI;
}

float3 Fd_Burley(float3 albedo, float roughness, float NoV, float NoL, float LoH)
{
	float f90 = 0.5 + 2.0 * LoH * LoH * roughness;

    float FdV = F_Schlick(NoV, 1.0, f90);
    float FdL = F_Schlick(NoL, 1.0, f90);

    return albedo * (FdV * FdL) / PI;
}

float3 Fd_Disney(float3 albedo, float roughness, float NoV, float NoL, float LoH)
{
	float energyBias = lerp(0, 0.5, roughness);
	float energyFactor = lerp(1.0, 1.0 / 1.51, roughness);

	float f90 = energyBias + 2.0 * LoH * LoH * roughness;

	float FdV = F_Schlick(NoV, 1.0, f90);
	float FdL = F_Schlick(NoL, 1.0, f90);

	return albedo * (FdV * FdL * energyFactor) / PI;
}

// BRDF Specular term

float3 Fr_CookTorrance(float NoV, float NoL, float LoH, float NoH, float3 f0, float a2)
{
	float f90 = saturate(50.0 * dot(f0, 0.33));

	float D = D_GGX(a2, NoH);
	float3 F = F_Schlick(LoH, f0, f90);
	float V = V_SmithGGXCorrelated(NoV, NoL, a2);

	return D * F * V;
}

#endif // INC_BRDF

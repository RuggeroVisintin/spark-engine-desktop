layout(std140) uniform MATERIAL
{
	vec3	kd;	                // the diffuse color of the surface
	float	roughness;			// roughness of the material

	float	reflectance;	   	// reflectance of the material;
    float   metalness;
} uMaterial;

float G1V(float NdotV, float k)
{
    	return 1.0f / (NdotV*(1.0f - k) + k);
}

float GGX_Distribution(in float alpha, in float NdotH)
{
	float alphaSqr = alpha * alpha;
	float denom = NdotH * NdotH * (alphaSqr - 1.0f) + 1.0f;
	 
	return alphaSqr / (PI * denom * denom);
}

float Shlick_Fresnel(in float F0, in float LdotH)
{
	float LdotH5 = pow(1.0f - LdotH, 5.0f) * F0;

	return F0 + (1.0f - F0) * (LdotH5);
}

float Smith_Shlick_GGX(in float alpha, in float NdotL, in float NdotV)
{
    float k = alpha / 2.0f;
	return G1V(NdotL, k) * G1V(NdotV, k);
}

float GGX_Brdf(in vec3 N, in vec3 V, in vec3 L, in float roughness, in float F0)
{
	float alpha = roughness * roughness;
	vec3 H = normalize(V + L);

	float NdotL = clamp(dot(N, L), 0.0f, 1.0f);
	float NdotV = clamp(dot(N, V), 0.0f, 1.0f);
	float NdotH = clamp(dot(N, H), 0.0f, 1.0f);
    float LdotH = clamp(dot(L, H), 0.0f, 1.0f);

	float D = GGX_Distribution(alpha, NdotH);
	float F = Shlick_Fresnel(F0, LdotH);
	float Vis = Smith_Shlick_GGX(alpha, NdotL, NdotV);

	return NdotL * D * F * Vis;
}

float LambertDiffuse(in float NdotL)
{
	return clamp(NdotL, 0.0, 1.0);
}

float HalfLambert(in float NdotL)
{
	return clamp(pow(NdotL * 0.5 + 0.5, 2), 0.0, 1.0);
}

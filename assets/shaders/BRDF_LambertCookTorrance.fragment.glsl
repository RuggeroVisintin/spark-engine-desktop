#version 410 core

#define PI 3.14159265
#define saturate(x) clamp(x, 0.0, 1.0);

layout(std140) uniform MATERIAL
{
	vec3	kd;				// the diffuse color of the surface
	float	roughness;		// roughness of the material

	float	reflectance;	// reflectance of the material;
} uMaterial;

layout(std140) uniform LIGHT
{
	vec3  color;			// the color of the light
	float power;			// the power of the light;

	vec3  position;			// the position of the light
	float ambientPower;		// the power of the ambient term;

	vec3 direction;			// the direction of the light;
} uLight;

in V2f
{
	vec3 normal; 			// normal in model space
	vec3 eyeNormal;			// normal in eye space
	
	vec3 position;			// position in model space
	vec3 eyePosition;		// position in eye space

	vec2 texCoord;			// texCoord in model space	
} v2f;

// outAttributes
out vec4 FS_fragColor;

float BrdfGgx_D(in float NdotH, in float roughness)
{
	float alpha = (roughness * roughness);
	float alpha2 = alpha * alpha;

	float denom = (NdotH * alpha2 - NdotH) * NdotH + 1;
	float D = alpha2 / (denom * denom);

	return D;
}

float BrdfSmithShlickGGX_G(in float LdotN, in float VdotN, in float roughness)
{
	float k = 2 / sqrt(PI * (roughness * roughness + 2));	

	float Vis_SmithV = VdotN / (VdotN * (1.0 - k) + k);
	float Vis_SmithL = LdotN / (LdotN * (1.0 - k) + k);
	return Vis_SmithV * Vis_SmithL;
}

float F_Shlick(in float F0, in float VdotH)
{
	return F0 + (1 - F0) * pow((1 - VdotH), 5);
}

float F_Fresnel(in float F0, in float VdotH)
{
	float base = 1.0 - VdotH;
	float exponential = pow( base, 5.0 );
	return exponential + F0 * ( 1.0 - exponential ); 
}

float LambertDiffuse(in float NdotL)
{
	return clamp(NdotL, 0.0, 1.0);
}

float HalfLambert(in float NdotL)
{
	return clamp(pow(NdotL * 0.5 + 0.5, 2), 0.0, 1.0);
}

float G1V(float dotNV, float k)
{
    return 1.0f/(dotNV*(1.0f-k)+k);
}

float LightingFuncGGX_REF(vec3 N, vec3 V, vec3 L, float roughness, float F0)
{
    float alpha = roughness*roughness;

    vec3 H = normalize(V+L);

    float dotNL = saturate(dot(N,L));
    float dotNV = saturate(dot(N,V));
    float dotNH = saturate(dot(N,H));
    float dotLH = saturate(dot(L,H));

    float F, D, vis;

    // D
    float alphaSqr = alpha*alpha;
    float pi = 3.14159f;
    float denom = dotNH * dotNH * (alphaSqr-1.0) + 1.0f;
    D = alphaSqr/(PI * denom * denom);

    // F
    float dotLH5 = pow(1.0f-dotLH,5);
    F = F0 + (1.0-F0)*(dotLH5);

    // V
    float k = alpha/2.0f;
    vis = G1V(dotNL,k)*G1V(dotNV,k);

    float specular = dotNL * D * F * vis;
    return specular;
}


void main()
{
	vec3  n                 = normalize(v2f.eyeNormal);
	vec3  v                 = normalize(-v2f.eyePosition);
	vec3  l                 = normalize(uLight.position);
	vec3  h                 = normalize(v + l);

	float roughness = clamp(uMaterial.roughness, 0.02, 1.0);
	float F0 = 0.16 * pow(uMaterial.reflectance, 2.0);
	float F1 = 1 - F0;

	float specular = 0.0f; 
	float diffuse = LambertDiffuse(clamp(dot(n, l), 0.0, 1.0)); 
	// keep in mind energy conservation
	diffuse *= (1 / PI) * F1;

	float D = BrdfGgx_D(NdotH, roughness);
	float G = BrdfSmithShlickGGX_G(clamp(dot(n, l), 0.0, 1.0), NdotV, roughness);
	float F = F_Shlick(F0, dot(l, h));
	
		specular = LightingFuncGGX_REF(n, v, l, roughness, F0);	

	float ambient = uLight.ambientPower;
	
	vec3 finalColor = (diffuse * (uMaterial.kd) + finalSpecular) * uLight.color * uLight.power;
	FS_fragColor = vec4(finalColor, 1.0f);
}
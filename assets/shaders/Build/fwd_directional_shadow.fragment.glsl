#version 410 core

#define PI 3.14159265
#define saturate(x) clamp(x, 0.0, 1.0);

layout (binding = 0) uniform sampler2D shadowTexture;

layout(std140) uniform MATERIAL
{
	vec3	kd;	                // the diffuse color of the surface
	float	roughness;			// roughness of the material

	float	reflectance;	   	// reflectance of the material;
    float   metalness;
} uMaterial;

layout(std140) uniform LIGHT
{
	vec3 	color;				// the color of the light
	float	power;				// the power of the light;

	vec3  	position;			// the position of the light
	float 	ambientPower;		// the power of the ambient term;
	vec3	direction;			// the direction of the light;
} uLight;

in V2f
{
	vec3 normal; 			// normal in model space
	vec3 eyeNormal;			// normal in eye space
	
	vec3 position;			// position in model space
	vec3 eyePosition;		// position in eye space

	vec2 texCoord;			// texCoord in model space	
	vec4 shadowCoord;

	mat4 modelViewProjection;
	mat4 modelViewMatrix;
	mat4 viewMatrix;
} v2f;


// outAttributes
out vec4 FS_fragColor;

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

vec3 gammaCorrected(vec3 v) {
	//return v;  
	return pow(v, vec3(1.0f/2.2f));
}

vec3 toLinearSpace(vec3 v) {
	return pow(v, vec3(2.2f));
}

float ShadowCalculation(vec4 fragPosLightSpace, float NdotL)
{
    float visibility = 1.0;
	float bias = 0.00005 * tan(acos(NdotL)); 
	if ( texture(shadowTexture, fragPosLightSpace.xy ).z < fragPosLightSpace.z - bias) {
    	visibility = 0;
	}

	return visibility;
}

void main()
{
	vec3 N = normalize(v2f.eyeNormal);
	vec3 V = normalize(-v2f.eyePosition);
	vec3 L = normalize(uLight.direction * inverse(mat3(v2f.viewMatrix)));
	float NdotL = dot(N, L);

	float roughness = clamp(uMaterial.roughness, 0.02f, 1.0f);
	float F0 = 0.16f * pow(uMaterial.reflectance, 2.0f);
	float F1 = 1 - F0;

	float shadow = ShadowCalculation(v2f.shadowCoord, NdotL); 
	float diffuse = LambertDiffuse(NdotL) * shadow;
	diffuse *= (1 / PI) * F1;

	float specular = 0.0f;
	float ambient = uLight.ambientPower;

	if(diffuse > 0) {
		specular = GGX_Brdf(N, V, L, roughness, F0);
	}

	float finalSpecular = saturate(specular);
	vec3 specularColor = mix(uLight.color, uMaterial.kd, uMaterial.metalness);
	vec3 finalColor = (ambient + diffuse) * uMaterial.kd + finalSpecular * specularColor * uLight.color * uLight.power;
	FS_fragColor = vec4(finalColor, 1.0);
}
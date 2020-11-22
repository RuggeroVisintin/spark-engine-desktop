#version 410 core

#define PI 3.14159265
#define saturate(x) clamp(x, 0.0, 1.0);

layout(std140) uniform MATERIAL
{
	vec3	kd;	                // the diffuse color of the surface
	float	roughness;		// roughness of the material

	float	reflectance;	        // reflectance of the material;
        float   metalness;
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

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}  

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}

void main()
{		
	vec3 N = normalize(v2f.eyeNormal);
	vec3 V = normalize(-v2f.eyePosition);
	vec3 L = normalize(uLight.position);

    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, uMaterial.kd, uMaterial.metalness);   
    // reflectance equation
    vec3 Lo = vec3(0.0);
 
        vec3 H = normalize(V + L);
        float distance    = length(L);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance     = uLight.color * attenuation;        
        
        // cook-torrance brdf
        float NDF = DistributionGGX(N, H, uMaterial.roughness);        
        float G   = GeometrySmith(N, V, L, uMaterial.roughness);      
        vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);       
        
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - uMaterial.metalness;	  
        
        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
        vec3 specular     = numerator / max(denominator, 0.001);  
            
        // add to outgoing radiance Lo
        float NdotL = max(dot(N, L), 0.0);                
        Lo += (kD * uMaterial.kd / PI + specular) * radiance * NdotL; 

    vec3 ambient = vec3(0.03) * uMaterial.kd * uMaterial.reflectance;
    vec3 color = ambient + Lo;
	
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));  
   
    FS_fragColor = vec4(color, 1.0);
}  
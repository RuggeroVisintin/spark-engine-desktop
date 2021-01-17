layout (binding = 0) uniform sampler2D shadowTexture;

float ShadowCalculation(vec4 fragPosLightSpace, float NdotL. float diffuse)
{
    float visibility = 1.0;
	float bias = 0.00005 * tan(acos(NdotL)); 
	if ( texture(shadowTexture, fragPosLightSpace.xy ).z < fragPosLightSpace.z - bias) {
    	visibility = 0;
	}

	return diffuse * visibility;
}
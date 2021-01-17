layout(std140) uniform LIGHT
{
	vec3 	color;				// the color of the light
	float	power;				// the power of the light;

	vec3  	position;			// the position of the light
	float 	ambientPower;		// the power of the ambient term;
	vec3	direction;			// the direction of the light;
} uLight;

vec3 L(vec3 inverseViewMatrix) 
{
    return normalize(uLight.direction * inverseViewMatrix);
}
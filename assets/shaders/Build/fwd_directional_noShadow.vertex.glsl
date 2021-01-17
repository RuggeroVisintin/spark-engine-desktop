#version 330 core

layout (location = 0) in vec3 aPositions;
layout (location = 1) in vec3 aNormals;
layout (location = 2) in vec2 aTexCoords;

//const float w = 5.2f;
//const float amplitude = 0.1f;
//const float phase = 1.2f;

layout(std140) uniform VIEW
{
	mat4 modelViewProjection;
	mat4 normalMatrix;
	mat4 modelViewMatrix;
	mat4 viewMatrix;
} uCamera;

layout(std140) uniform ENGINE
{
	float deltaTime;
} uEngine;

layout(std140) uniform LIGHT
{
	vec3 	color;				// the color of the light
	float	power;				// the power of the light;

	vec3  	position;			// the position of the light. Not used for directional lights. 
                                // TODO: maybe it can be moved to a specific block for positional lights
	float 	ambientPower;		// the power of the ambient term;
	mat4 	shadowMatrix;		// the shadow matrix: Refactor in a specific uniform for shadows

	vec3	direction;			// the direction of the light;
} uLight;

in V2f
{
	vec3 normal; 			// normal in model space
	vec3 eyeNormal;			// normal in eye space
	
	vec3 position;			// position in model space
	vec3 eyePosition;		// position in eye space

	vec2 texCoord;			// texCoord in model space	

	mat4 modelViewProjection;
	mat4 modelViewMatrix;
	mat4 viewMatrix;
} v2f;

void main() 
{
	v2f.modelViewProjection = uCamera.modelViewProjection;
	v2f.modelViewMatrix = uCamera.modelViewMatrix;
	v2f.viewMatrix = uCamera.viewMatrix;

	v2f.normal = aNormals;
	v2f.eyeNormal = (uCamera.modelViewMatrix * vec4(aNormals, 0.0)).xyz;

	v2f.position = aPositions;
	v2f.eyePosition = (uCamera.modelViewMatrix * vec4(aPositions, 1.0)).xyz;

	v2f.texCoord = aTexCoords;
	v2f.shadowCoord = uLight.shadowMatrix * vec4(aPositions, 1.0);

	vec4 finalPos = uCamera.modelViewProjection * vec4(aPositions, 1.0);
	gl_Position = finalPos;
}
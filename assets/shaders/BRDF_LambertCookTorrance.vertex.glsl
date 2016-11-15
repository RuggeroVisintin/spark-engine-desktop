#version 330 core

layout (location = 0) in vec3 aPositions;
layout (location = 1) in vec3 aNormals;
layout (location = 2) in vec2 aTexCoords;

layout(std140) uniform VIEW
{
	mat4 modelViewProjection;
	mat4 normalMatrix;
	mat4 modelViewMatrix;
	mat4 viewMatrix;
} uCamera;

out V2f
{
	vec3 normal;
	vec3 eyeNormal;
	
	vec3 position;
	vec3 eyePosition;

	vec2 texCoord;	
} v2f;

void main() 
{
	v2f.normal = aNormals;
	v2f.eyeNormal = (uCamera.normalMatrix * vec4(aNormals, 0.0)).xyz;

	v2f.position = aPositions;
	v2f.eyePosition = (uCamera.modelViewMatrix * vec4(aPositions, 1.0)).xyz;

	v2f.texCoord = aTexCoords;

	vec4 finalPos = uCamera.modelViewProjection * vec4(aPositions, 1.0);	
	gl_Position = finalPos;
}
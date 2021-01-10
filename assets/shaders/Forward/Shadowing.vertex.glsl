#version 330 core

layout (location = 0) in vec3 aPositions;

layout(std140) uniform SHADOW
{
	mat4 shadowMatrix;
} uShadow;

void main() {
    gl_Position = uShadow.shadowMatrix * vec4(aPositions, 1);
}
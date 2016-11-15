#version 330 core

in V2f
{
	vec2 texCoord;			// texCoord in model space	
} v2f;

out vec3 		outColor;
uniform sampler2D 	screenTexture;

void main()
{
	color = texture2D(screenTexture, 
}
#version 330 core

const vec2 madd=vec2(0.5,0.5);
layout (location = 0) in vec2 aPositions;

out V2f
{
	vec2 texCoord;			// texCoord in model space	
} v2f;

void main()
{
	v2f.texCoord = aPositions.xy * madd + madd;
	gl_Position = vec4(aPositions.xy, 0.0, 1.0);
}
#version 430 core

layout (location = 0)  in vec3 vPosition;
layout (location = 1)  in vec2 vUV;

layout (location = 16) uniform mat4 MAT;

//out data
out vec2 UV;

//out vec4 color;

void main()
{
	vec4 vertPos = vec4(vPosition, 1.0);
	gl_Position = MAT *  vertPos;

	UV = vUV;
	
	
}
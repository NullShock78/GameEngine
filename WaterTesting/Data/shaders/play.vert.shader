#version 430 core

layout (location = 0)  in vec3 vPosition;
layout (location = 1)  in vec3 vColor;
layout (location = 15) uniform vec3 colorin;
layout (location = 16) uniform mat4 MAT;

out vec4 color;

void main()
{
	vec4 vertPos = vec4(vPosition, 1.0);
	gl_Position = MAT *  vertPos;
	color = vec4((vColor + colorin), 1.0);
}
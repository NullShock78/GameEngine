
#version 430 core

layout (location = 0) in vec2 vPosition;
layout (location = 1) in vec3 vColor;

//out vec4 pos;
out vec4 color;

void main()
{
 gl_Position = vec4( vPosition, 0.0, 1.0);  
 color = vec4(vColor, 1.0);

 
}
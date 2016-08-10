#version 430 core

layout (location  = 0)  in vec3 vPosition;
layout (location  = 1)  in vec2 vUV;
layout (location  = 2)  in vec3 vNorm;

layout (location = 16) uniform mat4 MAT;

layout(location = 21) uniform mat4 SRmat;
layout(location = 22) uniform vec3 lPos;
layout(location = 23) uniform vec3 objPos;
layout(location = 24) uniform vec3 camPos;

out vec3 lightPos;
out vec3 normal;
out vec2 UV;
out vec3 Pos;
out vec3 cameraPos;
//out vec4 color;

void main()
{
	vec4 vertPos = MAT * vec4(vPosition, 1.0);
	gl_Position = vertPos;

	Pos = objPos + vec3(SRmat * vec4(vPosition, 1.0));
	cameraPos = camPos;
	normal = vec3(SRmat * vec4(vNorm, 1.0));
	UV = vUV;
	lightPos = lPos; 

	
	//if (falloff < 1.0f) falloff = 1.0f;
	//color = vec3(finalLight, finalLight, finalLight);
	//normal = vNorm;
	
	
}
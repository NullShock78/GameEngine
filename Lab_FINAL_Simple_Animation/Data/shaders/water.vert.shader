#version 430 core

layout (location  = 0)  in vec3 vPosition;
layout (location  = 1)  in vec2 vUV;
layout (location  = 2)  in vec3 vNorm;

layout (location = 16) uniform mat4 MAT;

layout(location = 21) uniform mat4 SRmat;
layout(location = 22) uniform vec3 lPos;
layout(location = 23) uniform vec3 objPos;
layout(location = 24) uniform vec3 camPos;

//layout(location = 25) uniform mat4  uvscale;
//layout(location = 26) uniform float shift;
layout(location = 30) uniform sampler2D normalSampler; //Refraction
out vec3 lightPos;
out vec3 normal;
out vec2 UV;
out vec3 Pos;
out vec3 nPos;
out vec3 cameraPos;
//out vec4 color;

void main()
{
	vec4 vertPos = MAT * vec4(vPosition, 1.0);
	gl_Position = vertPos;

	nPos = objPos + vec3(SRmat * vec4(vPosition, 1.0));
	Pos = objPos;
	cameraPos = camPos;
	//vec2 tmpUV = vec2(uvscale * vec4(vUV.x, vUV.y, 0, 1.0));
	//vec2 newNormUV = vec2(tmpUV.x, clamp(tmpUV.y + (shift * 0.1), 0.0, 1.0));

	vec3 normalRGB = (2 * texture(normalSampler, vUV).rgb) - 1.0f;
	normal = normalize(vec3(SRmat * vec4(normalRGB, 1.0)));
	

	float newUVx = clamp(vUV.x - .1*normal.x, 0.0,1.0);
	float newUVy = clamp(vUV.y - .1*normal.z, 0.0, 1.0);
	
	
	

	
	UV = vec2(newUVx, newUVy);
	lightPos = lPos; 

	
	//if (falloff < 1.0f) falloff = 1.0f;
	//color = vec3(finalLight, finalLight, finalLight);
	//normal = vNorm;
	
	
}
#version 430 core

layout(location = 0)  in vec3 vPosition;
layout(location = 1)  in vec3 vNorm;

//layout(location = 16) uniform mat4 MAT;
layout(location = 19) uniform vec3  objPos; //WORLD


layout(location = 20) uniform mat4 ModelWorldMat;
layout(location = 22) uniform vec3 lPos;
layout(location = 41) uniform mat4 Model;
layout(location = 42) uniform mat4 View;

//NORMALIZE!!!!


out vec3 normal;
out vec3 lightPos;
out vec3 light_cam;
out vec3 eyeDir;
out vec3 worldPosition;
out vec3 objPosition;
//out vec4 color;

void main()
{

	vec4 vertPos = vec4(vPosition, 1.0);
	vec4 matPos = View * Model * vertPos;
	gl_Position = matPos;

	objPosition = objPos;


	vec3 pos_worldspace = (ModelWorldMat * vertPos).xyz;
	vec3 pos_camspace = (View * Model * vertPos).xyz;
	eyeDir = vec3(0, 0, 0) - pos_camspace;

	vec3 lightpos_camspace = (View * vec4(lPos, 1)).xyz;
	light_cam = lightpos_camspace + eyeDir;

	normal = (View * Model * vec4(vNorm, 0)).xyz;


}
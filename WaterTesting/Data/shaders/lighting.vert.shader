#version 430 core

layout (location = 0)  in vec3 vPosition;
layout (location = 1)  in vec3 vNorm;
layout (location = 15) uniform vec3 tint;
layout (location = 16) uniform mat4 MAT;

layout(location = 19) uniform vec3 WORLD;
layout(location = 20) uniform mat4 SRmat;
layout(location = 22) uniform vec3 lPos;

//NORMALIZE!!!!
layout(location = 23) uniform vec3 lVec;
layout(location = 24) uniform vec3 eyePos;
//out data
out vec3 normal;
out vec3 color;

//out vec4 color;

void main()
{
	vec4 vertPos = vec4(vPosition, 1.0);
	vec4 matPos = MAT *  vertPos;
	gl_Position = matPos;

	vec3 posRotationScale = vec3(SRmat * vec4(vPosition, 1.0));

	vec3 normRotationScale = vec3(SRmat * vec4(vNorm, 1.0));
	//vec3 worldPos = vec3(VIEW * vec4(vPosition, 1.0f));  //vec3(matPos.x, matPos.y, matPos.z);

	vec3 aVec = lPos - (WORLD + posRotationScale);
	vec3 lightVec = normalize( lPos - (WORLD + posRotationScale));
	vec3 bVec = normalize(vec3(matPos) - lPos );
	vec3 cVec = lPos - vec3(matPos);
	float dist = length(cVec);


	//vec3 cVec = (eyePos - vec3(matPos));
	//vec3 dVec = vec3(reflect(bVec, normRotationScale));
	//vec3 eVec = ((cVec.r*dVec.x) + (cVec.g*dVec.y) + (cVec.b*dVec.z));

	vec3 matLightPos = vec3(MAT * vec4(lVec, 1.0f));

	//lightPos;
	//DOT

	//float light = max( ((lVec.r*normRotationScale.x) + (lVec.g*normRotationScale.y) + (lVec.b*normRotationScale.z)) *-1.0f, 0.0);
	float light = ((lightVec.r*normRotationScale.x) + (lightVec.g*normRotationScale.y) + (lightVec.b*normRotationScale.z));

	
	light = clamp(light, 0.0, 1.0);
	float falloff = (dist/50.0f);
	//if (falloff == 0.0f) falloff = 0.01f;
	
	falloff = clamp(falloff, 0.0, 1.0);

	//if (falloff < 1.0f) falloff = 1.0f;
	//color = vec3((tint.r * (light / falloff)), (tint.g * (light / falloff)), (tint.b* (light / falloff)));
	//color = vec3( (tint.r * (light) - falloff), (tint.g * (light)-falloff),  ( tint.b* (light)-falloff)) ;



	color = vec3((1.0f * tint * light)); //+ (0.5 * eVec);
	normal = vNorm;
	
	
}
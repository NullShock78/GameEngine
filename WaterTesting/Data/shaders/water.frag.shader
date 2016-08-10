#version 430 core

in  vec2 UV;
in  vec3 normal;
in  vec3 lightPos;
in  vec3 Pos;
in  vec3 cameraPos;
out vec4 outColor;
layout(location = 20) uniform sampler2D textureSampler;
//layout(location = 25) uniform sampler2D reflectionSampler;

//layout(location = 31) uniform sampler2D normalSampler;

void main()
{
	vec3 tex = texture(textureSampler, UV).rgb;
	//vec3 lightVec = normalize(Pos - lightPos);
	float lightLen = length(Pos - lightPos)/ 40.0f;
	lightLen = clamp(lightLen, 0.0,1.0);
	vec3 lightVec2 = normalize(vec3(0.0, -0.5, -0.5));//normalize(lightPos - Pos);


	vec3 diffuse = vec3(1.0, 1.0, 1.0) * dot(normal, lightVec2) * 0.5f;//((lightVec.x * normal.x) + (lightVec.y * normal.y) + (lightVec.z * normal.z)) * 1.0f;
	vec3 reflectVec = normalize(reflect(lightVec2, normal));
	vec3 vVec = normalize(cameraPos - Pos);
	vec3 camVec = vec3(normalize(Pos - cameraPos));
	float specularPow = dot(camVec, reflectVec);
	specularPow = clamp(specularPow, 0.0, 1.0);
	vec3 specular = vec3(1.0, 1.0, 1.0) * specularPow * .50f;//vec3(1.0,1.0,1.0) * tex * ((reflectVec.x * vVec.x) + (reflectVec.y * vVec.y) + (reflectVec.z * vVec.z)) * 0.40f;//((reflectVec.x * camVec.x) + (reflectVec.y * camVec.y) + (reflectVec.z * camVec.z)) * 0.3f;
	
	//vec3 camVec = vec3(normalize(Pos - cameraPos));
	vec3 cuttoffVec = reflect(camVec, normal);
	vec3 finalLight;
	if (dot(cuttoffVec, -camVec) < 0.01f)
	{
		finalLight = tex * (vec3(0.6, 0.6, 0.6) + diffuse +  specular);// -lightLen;

	}
	else
	{
		finalLight =  tex * (vec3(0.6, 0.6, 0.6) + diffuse + (specular*1.2f));// -lightLen;
	}
	
	outColor = vec4(finalLight, 0.5f);

}


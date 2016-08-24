#version 430 core

in  vec2 UV;
in  vec3 normal;
in  vec3 lightPos;
in  vec3 Pos;
in  vec3 nPos;
in  vec3 cameraPos;
out vec4 outColor;
layout(location = 20) uniform sampler2D textureSampler;
//layout(location = 25) uniform sampler2D reflectionSampler;

//layout(location = 31) uniform sampler2D normalSampler;

void main()
{
	vec3 tex = texture(textureSampler, UV).rgb;
	//vec3 lightVec = normalize(Pos - lightPos);
	//float lightLen = length(Pos - lightPos)/ 40.0f;
	//lightLen = clamp(lightLen, 0.0,1.0);
	//vec3 lightVec2 = normalize(lightPos - Pos);
	//vec3 diffuse = vec3(1.0, 1.0, .70) * tex * clamp(dot(normal, lightVec2) * 0.5f, 0.0, 1.0);//((lightVec.x * normal.x) + (lightVec.y * normal.y) + (lightVec.z * normal.z)) * 1.0f;
	//vec3 reflectVec = normalize(reflect(lightVec2, normal));
	//vec3 vVec = normalize(cameraPos - Pos);
	//vec3 camVec = vec3(normalize(Pos - cameraPos));
	//float specularPow = clamp(dot(camVec, reflectVec), 0.0,1.0);
	
	//vec3 specular = vec3(1.0, 1.0, .50)* tex * specularPow * .70f;//vec3(1.0,1.0,1.0) * tex * ((reflectVec.x * vVec.x) + (reflectVec.y * vVec.y) + (reflectVec.z * vVec.z)) * 0.40f;//((reflectVec.x * camVec.x) + (reflectVec.y * camVec.y) + (reflectVec.z * camVec.z)) * 0.3f;
	
	
	vec3 lightVec = normalize(Pos- lightPos);
	


	float cosTheta = clamp(dot(normal, lightVec), 0.0, 1.0);


	float dist = length(Pos - lightPos);
	//float att = 1.0 / (fa + (fb*dist) + fc*(dist*dist));



	//vec3 diffuse = f_diffuseCol * clamp(f_diffuseRef *dot(lightVec, normRotationScale), 0.0, 1.0);// ((lightVec.r*normRotationScale.x) + (lightVec.g*normRotationScale.y) + (lightVec.b*normRotationScale.z));




	vec3 diffuse = tex * vec3(1.0,1.0,1.0) * .76f * cosTheta;





	vec3 E = normalize(cameraPos - nPos);

	vec3 R = normalize(reflect(-lightVec, normal));


	float cosAlpha = clamp(dot(E, R), 0.0, 1.0);

	vec3 specular = tex *  vec3(1.0, 1.0, 1.0)  * 1.0f * pow(cosAlpha, .1f);//vec3(1.0,1.0,1.0) * tex * ((reflectVec.x * vVec.x) + (reflectVec.y * vVec.y) + 


																								  //(reflectVec.z * vVec.z)) * 0.40f;//((reflectVec.x * camVec.x) + (reflectVec.y * camVec.y) + (reflectVec.z * camVec.z)) * 0.3f;
	outColor = vec4(tex, 0.6f);// vec4((vec3(0.03, 0.03, 0.03) + diffuse + specular), 0.6f);


	//vec3 finalLight = (vec3(0.03, 0.03, 0.03) + diffuse + specular);// -lightLen;

	
//	outColor = vec4(finalLight, 0.50f);

}


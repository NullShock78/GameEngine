#version 430 core

layout(location = 15) uniform vec3 tint;

//layout(location = 23) uniform vec3 lVec;
layout(location = 24) uniform vec3  eyePos;
layout(location = 25) uniform vec3  ambientCol;
layout(location = 26) uniform vec3  diffuseCol;
layout(location = 27) uniform vec3  specCol;
layout(location = 28) uniform float ambientRef;
layout(location = 29) uniform float diffuseRef;
layout(location = 30) uniform float specularityRef;
layout(location = 31) uniform float specularityShininess;
layout(location = 32) uniform float fa;
layout(location = 33) uniform float fb;
layout(location = 34) uniform float fc;
layout(location = 35) uniform bool  directional;
layout(location = 40) uniform sampler2D textureSampler;


in  vec3 normal;
in  vec3 lightPos;
in  vec3 light_cam;
in  vec3 eyeDir;
in  vec3 worldPosition;
in  vec3 objPosition;

out vec4 outColor;


//layout(location = 31) uniform sampler2D normalSampler;

void main()
{

	vec3 ambient = tint * ambientRef * ambientCol;

	vec3 n = normalize(normal);
	vec3 l = normalize(light_cam);


	float dist = length(light_cam);
	float att = 1.0 / (fa + (fb*dist) + fc*(dist*dist));


	float cosTheta = clamp(dot(n, l), 0.0, 1.0);
	vec3 diffuse = tint * diffuseCol * diffuseRef * cosTheta / att;

	vec3 E = normalize(eyeDir);
	vec3 R = reflect(-l, n);
	float cosAlpha = clamp(dot(E, R), 0.0, 1.0);

	vec3 specular = tint * specCol  * clamp(specularityRef * (pow(cosAlpha, specularityShininess)) / att, 0.0, 1.0);//vec3(1.0,1.0,1.0) * tex * ((reflectVec.x * vVec.x) + (reflectVec.y * vVec.y) + 
																													//(reflectVec.z * vVec.z)) * 0.40f;//((reflectVec.x * camVec.x) + (reflectVec.y * camVec.y) + (reflectVec.z * camVec.z)) * 0.3f;
	outColor = vec4((ambient + diffuse + specular), 1.0);



}

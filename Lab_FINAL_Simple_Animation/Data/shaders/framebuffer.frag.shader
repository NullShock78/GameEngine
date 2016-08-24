#version 430 core


in  vec2 UV;
out vec4 outColor;

layout(location = 20) uniform sampler2D textureSampler;

void main()
{


	vec3 tempCol = texture(textureSampler, UV).rgb;

	outColor = vec4(tempCol.r / 1.5f, tempCol.g / 1.5f, tempCol.b / 1.5f, 1.0f);
}


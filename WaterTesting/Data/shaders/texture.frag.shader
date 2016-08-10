#version 430 core


in  vec2 UV;
out vec4 outColor;

layout(location = 20) uniform sampler2D textureSampler;

void main()
{

	//if (color.r < .7) discard;
	outColor = vec4(texture(textureSampler, UV).rgb, 1.0);

	//if(((gl_FragCoord.x  > 600)&& (gl_FragCoord.y < 300)) || ((gl_FragCoord.y < 300)  && (gl_FragCoord.x  < 600) )) {
	//discard;
	//}
	//vec2 scrPos = vec2(gl_FragCoord) - vec2(350,150);
	//float len =  length(scrPos);
	//if(len < 50 )discard;
}


#version 430 core


in  vec4 color;
out vec4 outColor;

void main()
{

	//if (color.r < .7) discard;
	outColor = color;

	//if(((gl_FragCoord.x  > 600)&& (gl_FragCoord.y < 300)) || ((gl_FragCoord.y < 300)  && (gl_FragCoord.x  < 600) )) {
	//discard;
	//}

	//vec2 scrPos = vec2(gl_FragCoord) - vec2(350,150);
	//float len =  length(scrPos);
	//if(len < 50 )discard;
}


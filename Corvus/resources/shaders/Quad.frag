#version 330 core

in vec2 uv ;
out vec4 outColor ;

uniform sampler2D sampler ;

void main()
{
	vec4 tex = texture(sampler, uv) ;
	if(tex.a < 0.1)
		discard ;
	else
		outColor = vec4(tex);

}
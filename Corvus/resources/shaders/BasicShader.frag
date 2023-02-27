#version 330 core
in vec2 uv ;
in vec4 color ;
out vec4 outColor ;

uniform sampler2D sampler ;

void main()
{
	outColor = mix(texture(sampler, uv), color, 0.5);
}
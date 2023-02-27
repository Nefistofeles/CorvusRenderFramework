#version 330 core
in vec2 uv;
out vec4 outColor ;

uniform sampler2D sampler ;

void main()
{
	outColor = texture(sampler, uv);
}
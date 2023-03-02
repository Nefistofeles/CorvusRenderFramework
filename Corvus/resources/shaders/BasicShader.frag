#version 330 core
in vec2 uv ;
in vec3 normal ;
out vec4 outColor ;

uniform sampler2D sampler ;
uniform float uv_multiplier ;

void main()
{
	outColor = texture(sampler, uv * uv_multiplier);
}
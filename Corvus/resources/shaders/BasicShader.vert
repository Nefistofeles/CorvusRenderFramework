#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;
layout (location = 2) in vec4 aColor;

out vec2 uv;
out vec4 color ;

uniform mat4 projView ;
uniform mat4 transform ;

void main()
{
	gl_Position = projView * transform * vec4(aPos, 1.0);
	uv = aUv;
	color = aColor ;
}
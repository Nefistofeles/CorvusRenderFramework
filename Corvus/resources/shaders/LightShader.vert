#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 projView ;
uniform mat4 transform ;

void main()
{
	gl_Position = projView * transform * vec4(aPos, 1.0) ;
}
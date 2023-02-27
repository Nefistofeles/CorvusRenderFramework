#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;
layout (location = 2) in vec3 aNormal;

out vec2 uv;
out vec3 normal ;
out vec3 localPos ;

uniform mat4 projView ;
uniform mat4 transform ;

void main()
{
	vec4 local = transform * vec4(aPos, 1.0) ;
	gl_Position = projView * local;
	uv = aUv;
	normal = aNormal ;
	localPos = local.xyz; //only rotation and scale
}
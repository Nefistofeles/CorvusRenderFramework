#version 330 core

out vec2 uv ;

uniform mat4 projView ;
uniform mat4 transform ;

void main()
{
	vec2 vertices[4];
	vertices[0] = vec2(-0.5, 0.5);
	vertices[1] = vec2( 0.5, 0.5);
	vertices[2] = vec2(-0.5,-0.5);
	vertices[3] = vec2( 0.5,-0.5);

	vec2 uvs[4];
	uvs[0] = vec2(0.0, 1.0);
	uvs[1] = vec2(1.0, 1.0);
	uvs[2] = vec2(0.0, 0.0);
	uvs[3] = vec2(1.0, 0.0);

	gl_Position = projView * transform * vec4(vertices[gl_VertexID], 0.0, 1.0);
	uv = uvs[gl_VertexID];
}
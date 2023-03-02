#version 330 core

out vec2 uv ;

void main()
{
	vec2 vertices[6];
	vertices[0] = vec2(-1.0,-1.0);
	vertices[1] = vec2( 1.0,-1.0);
	vertices[2] = vec2(-1.0, 1.0);
	vertices[3] = vec2( 1.0, 1.0);

	vec2 uvs[6];
	uvs[0] = vec2(0.0, 0.0);
	uvs[1] = vec2(1.0, 0.0);
	uvs[2] = vec2(0.0, 1.0);
	uvs[3] = vec2(1.0, 1.0);

	gl_Position = vec4(vertices[gl_VertexID], 0.0, 1.0);
	uv = uvs[gl_VertexID];
}
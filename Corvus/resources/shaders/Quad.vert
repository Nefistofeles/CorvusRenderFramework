#version 330 core

layout (location = 0) in vec2 aPos ;
layout (location = 1) in vec4 aRotScale ;
out vec2 uv ;
uniform mat4 projView ;

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

	vec2 pos =vertices[gl_VertexID];
    mat2 mat = mat2(aRotScale.x, aRotScale.y, aRotScale.z, aRotScale.w);
    pos = mat * pos ;
    pos += aPos ;
	gl_Position = projView * vec4(pos, 0.0, 1.0);
	uv = uvs[gl_VertexID];
}
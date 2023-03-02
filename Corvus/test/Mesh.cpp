#include "Mesh.h"

StaticMesh::StaticMesh(int32 elementCount, gl::LayoutElement* elements, int32 vertexSize, const void* vertices, int32 indexSize, uint32* indices)
{
	vao = gl::CreateVertexArray();
	gl::BindVertexArray(vao);
	ebo = gl::CreateStaticIndexBuffer(indexSize, indices);
	vbo = gl::CreateStaticVertexBuffer(vertexSize, vertices);
	gl::BindLayoutElements(elementCount, elements);
	gl::BindVertexArray(0);
	indexCount = (indexSize / sizeof(uint32));
}
StaticMesh::~StaticMesh()
{
	gl::DeleteVertexArray(vao);
	gl::DeleteBuffer(vbo);
	gl::DeleteBuffer(ebo);
}
void StaticMesh::Bind()
{
	gl::BindVertexArray(vao);
}
void StaticMesh::EnableAttrib(uint32 until)
{
	for (uint32 i = 0; i < until; i++)
	{
		gl::EnableVertexAttrib(vao, i);
	}
}
void StaticMesh::Draw()
{
	gl::DrawIndexed(gl::DRAW_MODE_TRIANGLES, indexCount, gl::DATA_TYPE_UNSIGNED_INT, 0);
}
#pragma once
#include "../core/Core.h"
#include "../graphics/Graphics.h"
using namespace Corvus;
class StaticMesh
{
private :
	uint32 vao = 0, vbo = 0, ebo = 0;
	uint32 indexCount = 0;
public :
	StaticMesh(int32 elementCount, gl::LayoutElement* elements, int32 vertexSize, const void* vertices, int32 indexSize, uint32* indices);
	~StaticMesh();
	void Bind();
	void EnableAttrib(uint32 until);
	void Draw();
};
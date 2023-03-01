#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../core/Core.h"
#include "../core/Array.h"
#include "../core/Math.h"

namespace Corvus::gl
{
	struct VertexData
	{
		glm::vec3 position;
		glm::vec2 uv;
		glm::vec3 normal;
	};
	struct MeshData
	{
		Array<VertexData> pVertices;
		Array<uint32> pIndices;
	};
	struct Scene
	{
		Array<MeshData> pMeshes;
	};
	Scene* LoadObjectFromFile(cstring path);
}
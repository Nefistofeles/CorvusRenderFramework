#include "ObjectLoader.h"

namespace Corvus::gl
{
	Scene* LoadObjectFromFile(cstring path)
	{
		static Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			DEBUG(path, " load failed");
		}
		Scene* myScene = new Scene();
		myScene->pMeshes.Resize(scene->mNumMeshes);
		for (int32 mesh = 0; mesh < scene->mNumMeshes; mesh++)
		{
			auto& vertices = myScene->pMeshes[mesh].pVertices;
			vertices.Resize(scene->mMeshes[mesh]->mNumVertices);
			aiMesh* meshData = scene->mMeshes[mesh];
			for (int32 i = 0; i < meshData->mNumVertices; i++)
			{
				vertices[i].position = glm::vec3(meshData->mVertices[i].x, meshData->mVertices[i].y, meshData->mVertices[i].z);
				if(meshData->HasNormals()) vertices[i].normal = glm::vec3(meshData->mNormals[i].x, meshData->mNormals[i].y, meshData->mNormals[i].z);
				if (meshData->mTextureCoords[0]) vertices[i].uv = glm::vec2(meshData->mTextureCoords[0][i].x, meshData->mTextureCoords[0][i].y);
			}
			auto& indices = myScene->pMeshes[mesh].pIndices;
			indices.Resize(meshData->mNumFaces * 3);
			int32 indexCount = 0;
			for (int32 i = 0; i < meshData->mNumFaces; i++)
			{
				indices[indexCount++] = meshData->mFaces[i].mIndices[0];
				indices[indexCount++] = meshData->mFaces[i].mIndices[1];
				indices[indexCount++] = meshData->mFaces[i].mIndices[2];				
			}
		}
		return myScene;
	}
}
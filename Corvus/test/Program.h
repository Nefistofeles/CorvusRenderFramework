#pragma once
#include "../graphics/Graphics.h"
#include "Camera.h"
#include "PhongShader.h"
#include "../graphics/ObjectLoader.h"
using namespace Corvus;

class Program
{
public :
	Program();
	~Program();
	void Init();
	void Run();
private :
	int32 polygonMode = 2;
	cstring polygonModeNames[3] = { "Point", "Line", "Fill" };
	gl::POLYGON_MODE polygonModes[3] = { gl::POLYGON_MODE_POINT, gl::POLYGON_MODE_LINE, gl::POLYGON_MODE_FILL };

	Camera camera;
	SDL_bool relative = SDL_TRUE;
	uint32 cubeVao = 0, dragonVao, dragonVbo = 0, cubeVbo = 0, dragonEbo = 0, cubeEbo = 0;

private :
	void CreateCube();
	void CreateTextures();
	struct Object
	{
		uint32 vao = 0;
		uint32 vbo = 0;
		uint32 ebo = 0;

		uint32 indiceCount = 0;

		glm::mat4 transform = glm::mat4(1.0f);

		Object() = default;
		~Object() = default;

		inline void Create(int32 verticesSize, const void* vertices, int32 indicesSize, uint32* indices, int32 layoutCount, gl::LayoutElement* layouts)
		{
			vao = gl::CreateVertexArray();
			gl::BindVertexArray(vao);

			vbo = gl::CreateStaticVertexBuffer(verticesSize, vertices);
			ebo = gl::CreateStaticIndexBuffer(indicesSize, indices);
			indiceCount = (indicesSize / sizeof(uint32));

			gl::BindLayoutElements(layoutCount, layouts);
			gl::BindVertexArray(0);
		}
		inline void Destroy()
		{
			gl::DeleteVertexArray(vao);
			gl::DeleteBuffer(vbo);
			gl::DeleteBuffer(ebo);
		}

	};
	Object dragon;
	Object cube;

	PhongLight phongLight = {};
	PhongMaterial phongMaterial = {};
	PhongShader phongShader = {};
	int32 shininespow = 1;
	
	uint32 lightProgram = 0;
	uint32 lightTransformLoc = 0;
	uint32 lightColorLoc = 0;
	uint32 lightProjViewLoc = 0;
};


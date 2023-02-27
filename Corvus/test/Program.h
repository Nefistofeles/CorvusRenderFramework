#pragma once
#include "../graphics/Graphics.h"
#include "Camera.h"

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
	glm::mat4 transform = glm::mat4(1.0f);
	SDL_bool relative = SDL_TRUE;

	uint32 vao = 0, vbo = 0, ebo = 0;
	uint32 program = 0;
	uint32 textureId = 0, textureLoc = 0;
private :
	void CreateCube();
	void CreateTexture();

	struct Light
	{
		float32 ambient = 0.4f;
		glm::vec3 position = glm::vec3(1.0f, 1.0f, 0.0f);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	};
	Light light;
	uint32 lightProgram = 0;
	glm::mat4 lightTransform = glm::mat4(1.0f);

};


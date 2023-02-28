#pragma once
#include "../graphics/Graphics.h"
#include "Camera.h"
#include "PhongShader.h"
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
	uint32 vao = 0, vbo = 0, ebo = 0;

private :
	void CreateCube();
	void CreateTextures();
	PhongLight phongLight = {};
	PhongMaterial phongMaterial = {};
	PhongShader phongShader = {};
	int32 shininespow = 1;
	
	glm::mat4 cubeTransform = glm::mat4(1.0f);

	uint32 lightProgram = 0;
	uint32 lightTransformLoc = 0;
	uint32 lightColorLoc = 0;
	uint32 lightProjViewLoc = 0;
	glm::mat4 lightTransform = glm::mat4(1.0f);
};


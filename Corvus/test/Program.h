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
};


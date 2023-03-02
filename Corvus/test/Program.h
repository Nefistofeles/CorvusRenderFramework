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
	float32 backgroundColor[4] = { 0.2f, 0.3f, 0.4f, 1.0f };
	Camera camera;
	SDL_bool relative = SDL_TRUE;
};


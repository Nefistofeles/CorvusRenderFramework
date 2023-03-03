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
	struct SampleData
	{
		glm::vec2 pos = glm::vec2(0.0f, 0.0f);
		float32 rot = 0;
		glm::vec2 scale = glm::vec2(1.0f, 1.0f);

		float32 speed = 0.0f;
		glm::vec2 dir = glm::vec2(0.0f, 0.0f);

		SampleData() = default;
		SampleData(glm::vec2 pos, float32 rot, glm::vec2 scale, float32 speed, glm::vec2 dir) : pos(pos), rot(rot), scale(scale), speed(speed), dir(dir) {}
	};
	void CalculateBoundary(glm::vec2& dir, const glm::vec2& pos, const float32& radius);

	float32 w = 136.6f / 2.0f;
	float32 h = 76.8f / 2.0f;
	Array<SampleData> samples;
	float32 backgroundColor[4] = { 0.2f, 0.3f, 0.4f, 1.0f };
	SDL_bool relative = SDL_TRUE;
};


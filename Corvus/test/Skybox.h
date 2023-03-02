#pragma once
#include "../graphics/Graphics.h"

struct SkyboxTexture
{
	cstring right;
	cstring left;
	cstring top;
	cstring bottom;
	cstring front;
	cstring back;
};
class Skybox
{
private :
	uint32 vao = 0, vbo = 0, texture = 0;
	uint32 program = 0, projViewLoc = 0, textureLoc = 0;

public :
	Skybox(const SkyboxTexture& texturePaths);
	~Skybox();

	void Bind();
	void SetProjView(const glm::mat4& projView);
	void Draw();
};
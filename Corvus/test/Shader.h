#pragma once
#include "../graphics/Graphics.h"
using namespace Corvus;
class Shader
{
private :
	uint32 program = 0;
	uint32 projViewLoc = 0, transformLoc = 0;
public :
	Shader(cstring vsPath, cstring fsPath);
	~Shader();
	void Bind();
	void SetProjView(const glm::mat4& projView);
	void SetTransform(const glm::mat4& transform);
	uint32 GetUniformLoc(cstring name);
};
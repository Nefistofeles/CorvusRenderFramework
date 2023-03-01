#pragma once
#include "../graphics/Graphics.h"
using namespace Corvus;

struct PhongLight
{
	glm::vec3 position = glm::vec3(1.0f, 1.0f, 0.0f);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
};
struct PhongMaterial
{
	float32 ambient = 0.1f;
	glm::vec3 diffuse = glm::vec3(0.2f, 0.2f, 0.2f);
	glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f);
	float32 shininess = 64.0f;
};
class PhongShader
{
private :
	uint32 program = 0;
	uint32 transformLoc = 0, projViewLoc = 0;
	uint32 cameraPosLoc = 0;
	uint32 lightPosLoc = 0, lightColorLoc;
	uint32 materialAmbientLoc = 0, materialDiffuseLoc = 0, materialSpecularLoc = 0, materialShininessLoc = 0;
public :
	void Create();
	void Bind(const PhongLight& light, const PhongMaterial& material, const glm::mat4& projView, const glm::vec3& cameraPos);
	void BindTransform(const glm::mat4& transform);
	void Delete();
};
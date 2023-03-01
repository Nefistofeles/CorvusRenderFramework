#pragma once
#include "../graphics/Graphics.h"
#include <sstream>
using namespace Corvus;
enum LIGHT_TYPE
{
	LIGHT_TYPE_SUN = 0,
	LIGHT_TYPE_POINT = 1
};
struct PhongLight
{
	LIGHT_TYPE type = LIGHT_TYPE_POINT;
	glm::vec3 position = glm::vec3(0.0, 7.0f, 6.0f);
	glm::vec3 direction = glm::vec3(-0.7f, -0.5f, -0.8f);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	/* dist	  constant	   linear		  quadratic
		7		1.0			0.7				1.8
		13		1.0			0.35			0.44
		20		1.0			0.22			0.20
		32		1.0			0.14			0.07
		50		1.0			0.09			0.032
		65		1.0			0.07			0.017
		100		1.0			0.045			0.0075
		160		1.0			0.027			0.0028
		200		1.0			0.022			0.0019
		325		1.0			0.014			0.0007
		600		1.0			0.007			0.0002
		3250	1.0			0.0014			0.000007
	*/
	//constant, linear, quadratic
	glm::vec3 attenuation = glm::vec3(1.0f, 0.022f, 0.0019f);
	
	bool isCreated = false;
	int32 index = 0;
	uint32 lightType = 0;
	uint32 lightPosLoc = 0, lightDirLoc = 0, lightColorLoc = 0, lightAttenuationLoc = 0;
		
	inline void Create(uint32 program)
	{
		std::string str = "";
		str.append("lights[").append(std::to_string(index)).append("].type");
		lightType = gl::GetUniformLocation(program, str.c_str());
		str.clear();
		str.append("lights[").append(std::to_string(index)).append("].position");
		lightPosLoc = gl::GetUniformLocation(program, str.c_str());
		str.clear();
		str.append("lights[").append(std::to_string(index)).append("].direction");
		lightDirLoc = gl::GetUniformLocation(program, str.c_str());
		str.clear();
		str.append("lights[").append(std::to_string(index)).append("].color");
		lightColorLoc = gl::GetUniformLocation(program, str.c_str());
		str.clear();
		str.append("lights[").append(std::to_string(index)).append("].attenuation");
		lightAttenuationLoc = gl::GetUniformLocation(program, str.c_str());
		
	}
	inline void Bind()
	{
		gl::SetUniformInt(lightType, static_cast<int>(type));
		gl::SetUniformVec3(lightPosLoc, position);
		gl::SetUniformVec3(lightDirLoc, direction);
		gl::SetUniformVec3(lightColorLoc, color);
		gl::SetUniformVec3(lightAttenuationLoc, attenuation);
	}

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
	uint32 materialAmbientLoc = 0, materialDiffuseLoc = 0, materialSpecularLoc = 0, materialShininessLoc = 0;
public :
	void Create();
	void Bind(PhongLight& light, const PhongMaterial& material, const glm::mat4& projView, const glm::vec3& cameraPos); 
	void Bind(int32 lightCount, PhongLight* lights, const PhongMaterial& material, const glm::mat4& projView, const glm::vec3& cameraPos);
	void BindTransform(const glm::mat4& transform);
	void Delete();
};
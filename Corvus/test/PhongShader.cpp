#include "PhongShader.h"

void PhongShader::Create()
{
	uint32 vs = gl::CreateShader("resources/shaders/PhongShader.vert", gl::SHADER_TYPE_VERTEX);
	uint32 fs = gl::CreateShader("resources/shaders/PhongShader.frag", gl::SHADER_TYPE_FRAGMENT);
	program = gl::CreateProgram(vs, fs, true);

	projViewLoc = gl::GetUniformLocation(program, "projView");
	transformLoc = gl::GetUniformLocation(program, "transform");
	cameraPosLoc = gl::GetUniformLocation(program, "cameraPos");

	materialAmbientLoc = gl::GetUniformLocation(program, "material.ambient");
	materialDiffuseLoc = gl::GetUniformLocation(program, "material.diffuse");
	materialSpecularLoc = gl::GetUniformLocation(program, "material.specular");
	materialShininessLoc = gl::GetUniformLocation(program, "material.shininess");
}

void PhongShader::Bind(PhongLight& light, const PhongMaterial& material, const glm::mat4& projView, const glm::vec3& cameraPos)
{
	gl::BindProgram(program);
	gl::SetUniformMat4(projViewLoc, projView, false);
	gl::SetUniformVec3(cameraPosLoc, cameraPos);

	if (!light.isCreated)
	{
		light.Create(program);
	}
	light.Bind();
	gl::SetUniformFloat(materialAmbientLoc, material.ambient);
	gl::SetUniformVec3(materialDiffuseLoc, material.diffuse);
	gl::SetUniformVec3(materialSpecularLoc, material.specular);
	gl::SetUniformFloat(materialShininessLoc, material.shininess);
}
void PhongShader::Bind(int32 lightCount, PhongLight* lights, const PhongMaterial& material, const glm::mat4& projView, const glm::vec3& cameraPos)
{
	gl::BindProgram(program);
	gl::SetUniformMat4(projViewLoc, projView, false);
	gl::SetUniformVec3(cameraPosLoc, cameraPos);

	for (int32 i = 0; i < lightCount; i++)
	{
		if (!lights[i].isCreated)
		{
			lights[i].Create(program);
		}
		lights[i].Bind();
	}

	gl::SetUniformFloat(materialAmbientLoc, material.ambient);
	gl::SetUniformVec3(materialDiffuseLoc, material.diffuse);
	gl::SetUniformVec3(materialSpecularLoc, material.specular);
	gl::SetUniformFloat(materialShininessLoc, material.shininess);
}
void PhongShader::BindTransform(const glm::mat4& transform)
{
	gl::SetUniformMat4(transformLoc, transform, false);
}

void PhongShader::Delete()
{
	gl::DeleteProgram(program);
}

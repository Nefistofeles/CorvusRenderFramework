#include "PhongShader.h"

void PhongShader::Create()
{
	uint32 vs = gl::CreateShader("resources/shaders/PhongShader.vert", gl::SHADER_TYPE_VERTEX);
	uint32 fs = gl::CreateShader("resources/shaders/PhongShader.frag", gl::SHADER_TYPE_FRAGMENT);
	program = gl::CreateProgram(vs, fs, true);

	projViewLoc = gl::GetUniformLocation(program, "projView");
	transformLoc = gl::GetUniformLocation(program, "transform");
	cameraPosLoc = gl::GetUniformLocation(program, "cameraPos");

	lightPosLoc = gl::GetUniformLocation(program, "light.position");
	lightColorLoc = gl::GetUniformLocation(program, "light.color");
	
	materialAmbientLoc = gl::GetUniformLocation(program, "material.ambient");
	materialDiffuseLoc = gl::GetUniformLocation(program, "material.diffuse");
	materialSpecularLoc = gl::GetUniformLocation(program, "material.specular");
	materialShininessLoc = gl::GetUniformLocation(program, "material.shininess");
}

void PhongShader::Bind(const PhongLight& light, const PhongMaterial& material, const glm::mat4& projView, const glm::vec3& cameraPos)
{
	gl::BindProgram(program);
	gl::SetUniformMat4(projViewLoc, projView, false);
	gl::SetUniformVec3(cameraPosLoc, cameraPos);

	gl::SetUniformFloat(materialShininessLoc, material.shininess);

	gl::SetUniformVec3(lightPosLoc, light.position);
	gl::SetUniformVec3(lightColorLoc, light.color);
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

#include "Shader.h"

Shader::Shader(cstring vsPath, cstring fsPath)
{
	uint32 vs = gl::CreateShader(vsPath, gl::SHADER_TYPE_VERTEX);
	uint32 fs = gl::CreateShader(fsPath, gl::SHADER_TYPE_FRAGMENT);
	program = gl::CreateProgram(vs, fs, true);
	projViewLoc = gl::GetUniformLocation(program, "projView");
	transformLoc = gl::GetUniformLocation(program, "transform");
}
Shader::~Shader()
{
	gl::DeleteProgram(program);
}
void Shader::Bind()
{
	gl::BindProgram(program);
}
void Shader::SetProjView(const glm::mat4& projView)
{
	gl::SetUniformMat4(projViewLoc, projView, false);
}
void Shader::SetTransform(const glm::mat4& transform)
{
	gl::SetUniformMat4(transformLoc, transform, false);
}
uint32 Shader::GetUniformLoc(cstring name)
{
	return gl::GetUniformLocation(program, name);
}
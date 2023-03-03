#include "Skybox.h"
using namespace Corvus;
float32 skyboxVertices[] = {
     
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

Skybox::Skybox(const SkyboxTexture& texturePaths)
{
	vao = gl::CreateVertexArray();
	gl::BindVertexArray(vao);
	vbo = gl::CreateStaticVertexBuffer(sizeof(skyboxVertices), skyboxVertices);
    gl::LayoutElement layout = { 0, 3, gl::DATA_TYPE_FLOAT, false};
    gl::BindLayoutElements(1, &layout);
	gl::BindVertexArray(0);
	gl::TextureParameter params =
	{
		gl::TEXTURE_FILTER_LINEAR, gl::TEXTURE_FILTER_LINEAR,
		gl::TEXTURE_WRAP_CLAMP_TO_EDGE,gl::TEXTURE_WRAP_CLAMP_TO_EDGE,gl::TEXTURE_WRAP_CLAMP_TO_EDGE
	};
	cstring texPaths[] =
	{
        texturePaths.right,
        texturePaths.left,
        texturePaths.top,
        texturePaths.bottom,
        texturePaths.front,
        texturePaths.back
	};
	texture = gl::CreateTextureCubeMap(texPaths, params, false);
	uint32 vs = gl::CreateShader("resources/shaders/Skybox.vert", gl::SHADER_TYPE_VERTEX);
	uint32 fs = gl::CreateShader("resources/shaders/Skybox.frag", gl::SHADER_TYPE_FRAGMENT);
	program = gl::CreateProgram(vs, fs, true);
	projViewLoc = gl::GetUniformLocation(program, "projView");
	textureLoc = gl::GetUniformLocation(program, "cubemap");
}

Skybox::~Skybox()
{
	gl::DeleteVertexArray(vao);
	gl::DeleteBuffer(vbo);
	gl::DeleteProgram(program);
	gl::DeleteTexture(texture);
}

void Skybox::Bind()
{
	gl::BindVertexArray(vao);
	gl::BindProgram(program);
	gl::BindTextureCubeMap(texture, 0, textureLoc);
}

void Skybox::SetProjView(const glm::mat4& projView)
{
	gl::SetUniformMat4(projViewLoc, projView, false);
}
void Skybox::Draw()
{
	gl::DepthFunc(gl::FUNC_LEQUAL);
	gl::DrawArrays(gl::DRAW_MODE_TRIANGLES, 0, 36);
	gl::DepthFunc(gl::FUNC_LESS);
}

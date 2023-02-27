#include "Program.h"

Program::Program()
{
	gl::Init(1366, 768, "Corvus");
}

Program::~Program()
{
	gl::Destroy();
}

void Program::Init()
{	
	gl::ClearColor(0.2f, 0.3f, 0.4f, 1.0f);
}

void Program::Run()
{
	float32 vertices[] = 
	{
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 
	};
	uint32 vao = gl::CreateVertexArray();
	gl::BindVertexArray(vao);
	uint32 vbo = gl::CreateStaticVertexBuffer(sizeof(vertices), vertices);
	gl::LayoutElement layouts[] =
	{
		{0, 3, gl::DATA_TYPE_FLOAT, false},
		{1, 4, gl::DATA_TYPE_FLOAT, false}
	};
	gl::BindLayoutElements(_countof(layouts), layouts);
	gl::BindVertexArray(0);
	uint32 vs = gl::CreateShader("resources/shaders/BasicShader.vert", gl::SHADER_TYPE_VERTEX);
	uint32 fs = gl::CreateShader("resources/shaders/BasicShader.frag", gl::SHADER_TYPE_FRAGMENT);
	uint32 program = gl::CreateProgram(vs, fs, true);

	while (gl::PollEvents())
	{
		gl::Clear(gl::CLEAR_BIT_COLOR);
		gl::BindProgram(program);
		gl::BindVertexArray(vao);
		gl::DrawArrays(gl::DRAW_MODE_TRIANGLES, 0, 3);
		gl::SwapBuffers();
	}
	gl::DeleteProgram(program);
	gl::DeleteVertexArray(vao);
	gl::DeleteBuffer(vbo);
}

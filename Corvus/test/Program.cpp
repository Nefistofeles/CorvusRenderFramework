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
	while (gl::PollEvents())
	{
		gl::Clear(gl::CLEAR_BIT_COLOR);
		gl::SwapBuffers();
	}
}

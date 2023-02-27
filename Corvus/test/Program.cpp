#include "Program.h"

Program::Program()
{
	gl::Init(1366, 768, "Corvus");
	gl::PolygonMode(gl::FACE_FRONT_AND_BACK, polygonModes[polygonMode]);
}

Program::~Program()
{
	gl::Destroy();
}

void Program::Init()
{	
	gl::ClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	proj = glm::ortho(-1.366f, 1.366f, -0.768f, 0.768f);
	projView = proj * view;
}

void Program::PolygonModeUI()
{
	if (ImGui::ListBox("Polygon Mode", &polygonMode, polygonModeNames, _countof(polygonModes)))
	{
		gl::PolygonMode(gl::FACE_FRONT_AND_BACK, polygonModes[polygonMode]);
	}
}

void Program::Run()
{
	float32 vertices[] = {
		-0.5f, 0.5f, 0.0f,   0.0f, 1.0f,   1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, 0.5f, 0.0f,   1.0f, 1.0f,   0.0f, 1.0f, 0.0f, 1.0f,
		 0.5f,-0.5f, 0.0f,   1.0f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f,-0.5f, 0.0f,   0.0f, 0.0f,   0.0f, 1.0f, 1.0f, 1.0f,
	};
	uint32 indices[] = { 
		0, 1, 3,
		3, 1, 2
	};
	uint32 vao = gl::CreateVertexArray();
	gl::BindVertexArray(vao);
	uint32 vbo = gl::CreateStaticVertexBuffer(sizeof(vertices), vertices);
	uint32 ebo = gl::CreateStaticIndexBuffer(sizeof(indices), indices);
	gl::LayoutElement layouts[] =
	{
		{0, 3, gl::DATA_TYPE_FLOAT, false},
		{1, 2, gl::DATA_TYPE_FLOAT, false},
		{2, 4, gl::DATA_TYPE_FLOAT, false},
	};
	gl::BindLayoutElements(_countof(layouts), layouts);
	gl::BindVertexArray(0);
	uint32 vs = gl::CreateShader("resources/shaders/BasicShader.vert", gl::SHADER_TYPE_VERTEX);
	uint32 fs = gl::CreateShader("resources/shaders/BasicShader.frag", gl::SHADER_TYPE_FRAGMENT);
	uint32 program = gl::CreateProgram(vs, fs, true);

	uint32 projViewLoc = gl::GetUniformLocation(program, "projView");
	uint32 transformLoc = gl::GetUniformLocation(program, "transform");

	transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
	transform = glm::rotate(transform, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));

	gl::TextureParameter params = 
	{
		gl::TEXTURE_FILTER_LINEAR, gl::TEXTURE_FILTER_LINEAR,
		gl::TEXTURE_WRAP_CLAMP_TO_EDGE, gl::TEXTURE_WRAP_CLAMP_TO_EDGE, gl::TEXTURE_WRAP_CLAMP_TO_EDGE
	};
	uint32 textureId = gl::CreateTexture2D("resources/textures/wall.jpg", params);
	uint32 textureLoc = gl::GetUniformLocation(program, "sampler");

	ImGuiIO& io = ImGui::GetIO();

	while (gl::PollEvents())
	{
		
		gl::Clear(gl::CLEAR_BIT_COLOR);
		gl::BindProgram(program);
		gl::BindTexture2D(textureId, 0, textureLoc);
		gl::SetUniformMat4(projViewLoc, projView, false);
		gl::SetUniformMat4(transformLoc, transform, false);

		gl::BindVertexArray(vao);
		gl::DrawIndexed(gl::DRAW_MODE_TRIANGLES, 6, gl::DATA_TYPE_UNSIGNED_INT, 0);
				
		//ui
		gl::UIBegin();
		ImGui::Begin("Settings");
		ImGui::Text("FPS: %f", io.Framerate);
		ImGui::Separator();
		PolygonModeUI();
		ImGui::End();
		gl::UIEnd();
		gl::SwapBuffers();
	}
	gl::DeleteTexture(textureId);
	gl::DeleteProgram(program);
	gl::DeleteVertexArray(vao);
	gl::DeleteBuffer(vbo);
	gl::DeleteBuffer(ebo);
}

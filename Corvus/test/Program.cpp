#include "Program.h"
#include <random>
#include "Mesh.h"
#include "Shader.h"
#include "ScreenBuffer.h"
#include "Skybox.h"

float32 vertices[] = {
	-0.5f, 0.5f,-0.5f,	  1.0f, 1.0f,	 0.0f, 0.0f,-1.0f, //0
	 0.5f, 0.5f,-0.5f,	  0.0f, 1.0f,	 0.0f, 0.0f,-1.0f, //1
	 0.5f,-0.5f,-0.5f,	  0.0f, 0.0f,	 0.0f, 0.0f,-1.0f, //2
	-0.5f,-0.5f,-0.5f,	  1.0f, 0.0f,	 0.0f, 0.0f,-1.0f, //3

	 0.5f, 0.5f, 0.5f,	  1.0f, 1.0f,	 0.0f, 0.0f, 1.0f, //4
	-0.5f, 0.5f, 0.5f,	  0.0f, 1.0f,	 0.0f, 0.0f, 1.0f, //5
	-0.5f,-0.5f, 0.5f,	  0.0f, 0.0f,	 0.0f, 0.0f, 1.0f, //6
	 0.5f,-0.5f, 0.5f,	  1.0f, 0.0f,	 0.0f, 0.0f, 1.0f, //7

	-0.5f, 0.5f, 0.5f,	  1.0f, 1.0f,	-1.0f, 0.0f, 0.0f, //8
	-0.5f, 0.5f,-0.5f,	  0.0f, 1.0f,	-1.0f, 0.0f, 0.0f, //9
	-0.5f,-0.5f,-0.5f,	  0.0f, 0.0f,	-1.0f, 0.0f, 0.0f, //10
	-0.5f,-0.5f, 0.5f,	  1.0f, 0.0f,	-1.0f, 0.0f, 0.0f, //11

	 0.5f, 0.5f,-0.5f,	  1.0f, 1.0f,	 1.0f, 0.0f, 0.0f, //12
	 0.5f, 0.5f, 0.5f,	  0.0f, 1.0f,	 1.0f, 0.0f, 0.0f, //13
	 0.5f,-0.5f, 0.5f,	  0.0f, 0.0f,	 1.0f, 0.0f, 0.0f, //14
	 0.5f,-0.5f,-0.5f,	  1.0f, 0.0f,	 1.0f, 0.0f, 0.0f, //15

	-0.5f,-0.5f,-0.5f,	  1.0f, 1.0f,	 0.0f,-1.0f, 0.0f, //16
	 0.5f,-0.5f,-0.5f,	  0.0f, 1.0f,	 0.0f,-1.0f, 0.0f, //17
	 0.5f,-0.5f, 0.5f,	  0.0f, 0.0f,	 0.0f,-1.0f, 0.0f, //18
	-0.5f,-0.5f, 0.5f,	  1.0f, 0.0f,	 0.0f,-1.0f, 0.0f, //19

	-0.5f, 0.5f, 0.5f,	  1.0f, 1.0f,	 0.0f, 1.0f, 0.0f, //20
	 0.5f, 0.5f, 0.5f,	  0.0f, 1.0f,	 0.0f, 1.0f, 0.0f, //21
	 0.5f, 0.5f,-0.5f,	  0.0f, 0.0f,	 0.0f, 1.0f, 0.0f, //22
	-0.5f, 0.5f,-0.5f,	  1.0f, 0.0f,	 0.0f, 1.0f, 0.0f, //23
};
uint32 indices[] =
{
	0, 1, 3, 3, 1, 2,
	4, 5, 7, 7, 5, 6,
	8, 9, 11, 11, 9, 10,
	12, 13, 15, 15, 13, 14,
	16, 17, 19, 19, 17, 18,
	20, 21, 23, 23, 21, 22
};

Program::Program()
{
	gl::Init(1366, 768, "Corvus");
	gl::RelativeMouse(relative);
	gl::WindowMouseGrab(relative);
	gl::Vsync(1);

	gl::PolygonMode(gl::FACE_FRONT_AND_BACK, polygonModes[polygonMode]);

	gl::Enable(gl::TEST_DEPTH);
	gl::Enable(gl::TEST_CULL_FACE);
	gl::CullFace(gl::FACE_BACK);
}

Program::~Program()
{
	gl::Destroy();
}

void Program::Init()
{
	gl::ClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);
	camera.Perspective(glm::radians(45.0f), 1.77f, 0.1f, 1000.0f);
	camera.SetPosition({ -10.0f, 14.0f, 14.0f });
}
void Program::Run()
{
	ImGuiIO& io = ImGui::GetIO();
	gl::LayoutElement elements[] =
	{
		{0, 3, gl::DATA_TYPE_FLOAT, false},
		{1, 2, gl::DATA_TYPE_FLOAT, false},
		{2, 3, gl::DATA_TYPE_FLOAT, false},
	};
	StaticMesh cube(_countof(elements), elements, sizeof(vertices), vertices, sizeof(indices), indices);
	Shader basicShader("resources/shaders/BasicShader.vert", "resources/shaders/BasicShader.frag");
	uint32 uv_multiplierLoc = basicShader.GetUniformLoc("uv_multiplier");
	uint32 samplerLoc = basicShader.GetUniformLoc("sampler");

	gl::TextureParameter params =
	{
		gl::TEXTURE_FILTER_LINEAR, gl::TEXTURE_FILTER_LINEAR,
		gl::TEXTURE_WRAP_REPEAT,gl::TEXTURE_WRAP_REPEAT,gl::TEXTURE_WRAP_REPEAT
	};
	uint32 texture1 = gl::CreateTexture2D("resources/textures/container.png", params);
	uint32 texture2 = gl::CreateTexture2D("resources/textures/wall.jpg", params);
	uint32 texture3 = gl::CreateTexture2D("resources/textures/grass.png", params);

	Shader quadShader("resources/shaders/Quad.vert", "resources/shaders/Quad.frag");
	uint32 grassSamplerLoc = quadShader.GetUniformLoc("sampler");
	glm::mat4 containerTransform = glm::mat4(1.0f);
	CalculateTransform(containerTransform, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	glm::mat4 ground = glm::mat4(1.0f);
	CalculateTransform(ground, glm::vec3(0.0f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::radians(0.0f), glm::vec3(15.0f, 0.1f, 15.0f));
	
	glm::mat4 grass = glm::mat4(1.0f);
	CalculateTransform(grass, glm::vec3(0.0f, 0.0f, -0.65f), glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(180.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	gl::DepthFunc(gl::FUNC_LESS);
	gl::Enable(gl::TEST_BLEND);
	gl::BlendFunc(gl::SOURCE_RGB_SRC_ALPHA, gl::DEST_RGB_ONE_MINUS_SRC_ALPHA);
	gl::BlendFuncSeperate(gl::SOURCE_RGB_SRC_ALPHA, gl::DEST_RGB_ONE_MINUS_SRC_ALPHA, 1, 0);

	//ScreenBuffer screenBuffer(1366, 768);

	SkyboxTexture skyboxTex;
	skyboxTex.right	= "resources/textures/skybox/day/right.jpg";
	skyboxTex.left	= "resources/textures/skybox/day/left.jpg";
	skyboxTex.top	= "resources/textures/skybox/day/top.jpg";
	skyboxTex.bottom= "resources/textures/skybox/day/bottom.jpg";
	skyboxTex.front	= "resources/textures/skybox/day/front.jpg";
	skyboxTex.back	= "resources/textures/skybox/day/back.jpg";
	Skybox skybox(skyboxTex);

	while (gl::PollEvents())
	{
		if (ImGui::IsKeyPressed(ImGuiKey_Escape))
		{
			relative == SDL_TRUE ? relative = SDL_FALSE : relative = SDL_TRUE;
			gl::RelativeMouse(relative);
			gl::WindowMouseGrab(relative);
		}
		if(relative)
			camera.ProcessInput();
		
		//screenBuffer.Start();
		gl::Clear(gl::CLEAR_BIT_COLOR_DEPTH);
		cube.Bind();
		basicShader.Bind();
		basicShader.SetProjView(camera.ProjView());
		basicShader.SetTransform(containerTransform);
		gl::SetUniformFloat(uv_multiplierLoc, 1.0f);
		gl::BindTexture2D(texture1, 0, samplerLoc);
		cube.Draw();
		
		gl::SetUniformFloat(uv_multiplierLoc, 10.0f);
		basicShader.SetProjView(camera.ProjView());
		basicShader.SetTransform(ground);
		gl::BindTexture2D(texture2, 0, samplerLoc);
		cube.Draw();

		quadShader.Bind();
		quadShader.SetProjView(camera.ProjView());
		quadShader.SetTransform(grass);
		gl::BindTexture2D(texture3, 0, grassSamplerLoc);
		gl::DrawArrays(gl::DRAW_MODE_TRIANGLE_STRIP, 0, 4);
		skybox.Bind();
		skybox.SetProjView(camera.Proj() * glm::mat4(glm::mat3(camera.View())));
		skybox.Draw();
		//screenBuffer.End();

		//screenBuffer.Draw(backgroundColor);
		//ui

		gl::UIBegin();
		ImGui::Begin("Settings");
		ImGui::Text("FPS: %f", io.Framerate);
		ImGui::End();
		gl::UIEnd();
		gl::SwapBuffers();
	}
	gl::DeleteTexture(texture1);
	gl::DeleteTexture(texture2);
	gl::DeleteTexture(texture3);
}

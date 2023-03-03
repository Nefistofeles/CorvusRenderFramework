#include "Program.h"
#include <random>
#include "Mesh.h"
#include "Shader.h"
#include "ScreenBuffer.h"
#include "Skybox.h"
#include "BatchRenderer.h"
/*
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
*/
Program::Program()
{
	gl::Init(1366, 768, "Corvus");
	gl::Vsync(1);

	//gl::Enable(gl::TEST_DEPTH);
	//gl::Enable(gl::TEST_CULL_FACE);
	//gl::CullFace(gl::FACE_BACK);
}

Program::~Program()
{
	gl::Destroy();
}

void Program::Init()
{
	gl::ClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);
}

void Program::CalculateBoundary(glm::vec2& dir, const glm::vec2& pos, const float32& radius)
{
	float32 minx = pos.x - radius;
	float32 maxx = pos.x + radius;
	float32 miny = pos.y - radius;
	float32 maxy = pos.y + radius;

	if (minx < -w || maxx > w)
	{
		dir.x *= -1;
	}
	if (miny < -h || maxy > h)
	{
		dir.y *= -1;
	}
}
void Program::Run()
{
	ImGuiIO& io = ImGui::GetIO();

	//gl::DepthFunc(gl::FUNC_LESS);
	gl::Enable(gl::TEST_BLEND);
	gl::BlendFunc(gl::SOURCE_RGB_SRC_ALPHA, gl::DEST_RGB_ONE_MINUS_SRC_ALPHA);
	gl::BlendFuncSeperate(gl::SOURCE_RGB_SRC_ALPHA, gl::DEST_RGB_ONE_MINUS_SRC_ALPHA, 1, 0);
	uint32 maxQuadSize = 1'000'000;
	// batch size effect performance
	//if object draw 50'000 batch size could be nearly ~100
	//but object size is increase like 1m, batch size also should be high value
	uint32 batchSize = 4000;
	UniquePtr<BatchRenderer> pBatchRenderer = new BatchRenderer(maxQuadSize, batchSize);
	samples.Resize(maxQuadSize);

	float32 w = 136.6f / 2.0f;
	float32 h = 76.8f / 2.0f;
	glm::mat4 projView = glm::ortho(-w, w, -h, h, -1.0f, 1.0f);

	std::mt19937 gen;
	//std::uniform_real_distribution<float32> scale_distr(0.05f, 0.3f);
	std::uniform_real_distribution<float32> scale_distr(0.3f, 1.0f);
	std::uniform_real_distribution<float32> dir_distr(-1.0f, 1.0f);
	std::uniform_real_distribution<float32> speed_distr(-10.0f, 10.0f);

	while (gl::PollEvents())
	{	
		gl::Clear(gl::CLEAR_BIT_COLOR);
		float32 mousePosX = 2.0f * (io.MousePos.x / io.DisplaySize.x) - 1.0f;
		float32 mousePosY = -2.0f * (io.MousePos.y / io.DisplaySize.y) + 1.0f;

		if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && samples.AvaliableSize() <= maxQuadSize)
		{
			for (int32 i = 0; i < 1000; i++)
			{
				SampleData data;
				data.pos = glm::vec2(mousePosX * w, mousePosY * h);
				data.rot = 0.0f;
				data.scale = glm::vec2(scale_distr(gen));
				data.dir = glm::normalize(glm::vec2(dir_distr(gen), dir_distr(gen)));
				data.speed = speed_distr(gen);
				samples.Emplace(data);
			}
		}		
		pBatchRenderer->SetViewProj(projView);
		pBatchRenderer->Begin();
		for (int32 i = 0; i < samples.AvaliableSize(); i++)
		{
			SampleData& sample = samples[i];
			CalculateBoundary(sample.dir, sample.pos, sample.scale.x);
			sample.pos += sample.dir * sample.speed * io.DeltaTime;
			pBatchRenderer->Draw(sample.pos, sample.rot, sample.scale);
		}
		pBatchRenderer->End();
		gl::UIBegin();
		ImGui::Begin("Settings");
		ImGui::Text("FPS: %f", io.Framerate);
		ImGui::Text("Mouse Position: %f, %f", mousePosX * w, mousePosY * h);
		ImGui::Text("Object Size %d", samples.AvaliableSize());
		if (ImGui::Button("Clear"))
		{
			samples.Reset();
		}
		ImGui::End();
		gl::UIEnd();
		gl::SwapBuffers();
	}
}

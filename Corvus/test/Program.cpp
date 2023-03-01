#include "Program.h"
#include <random>

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

void Program::CreateCube()
{
	gl::Scene* scene = gl::LoadObjectFromFile("resources/objects/dragon/dragon.obj");
	auto& dragonVertices = scene->pMeshes[0].pVertices;
	auto& dragonIndices = scene->pMeshes[0].pIndices;
	
	gl::LayoutElement layouts[] =
	{
		{0, 3, gl::DATA_TYPE_FLOAT, false},
		{1, 2, gl::DATA_TYPE_FLOAT, false},
		{2, 3, gl::DATA_TYPE_FLOAT, false},
	};

	dragon.Create(dragonVertices.Size() * sizeof(dragonVertices[0]), &dragonVertices[0], sizeof(uint32) * dragonIndices.Size(), &dragonIndices[0], _countof(layouts), layouts);
	cube.Create(sizeof(vertices), vertices, sizeof(indices), indices, _countof(layouts), layouts);
	delete scene;
}

void Program::LightUI()
{
	ImGui::Text("Light Settings");
	ImGui::Combo("Light Type", &currentLightItem, lightTypes, 2);
	if (currentLightItem == (int32)LIGHT_TYPE::LIGHT_TYPE_SUN)
	{
		ImGui::ColorEdit3("Light Color", glm::value_ptr(lights[0].color));
		ImGui::DragFloat3("Light Direction", glm::value_ptr(lights[0].direction), 0.1f, -1.0f, 1.0f);
	}
	else if (currentLightItem == (int32)LIGHT_TYPE::LIGHT_TYPE_POINT)
	{
		ImGui::ColorEdit3("Light Color", glm::value_ptr(lights[1].color));
		if (ImGui::DragFloat3("Light Position", glm::value_ptr(lights[1].position), 0.1f, -100.0f, 100.0f))
		{
			CalculateTransform(cube.transform, glm::vec3(lights[1].position), glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, glm::vec3(0.2f, 0.2f, 0.2f));
		}
		ImGui::DragFloat3("Light Attenuation", glm::value_ptr(lights[1].attenuation), 0.0001f, 0.0f, 1.0f, "%.5f");
	}
}
void Program::MateriaUI()
{
	ImGui::Text("Material Settings");
	ImGui::SliderFloat("Ambient", &phongMaterial.ambient, 0.0f, 1.0f);
	ImGui::SliderFloat3("Diffuse", glm::value_ptr(phongMaterial.diffuse), 0.0f, 1.0f);
	if (ImGui::SliderFloat("###Diffuse", &phongMaterial.diffuse.x, 0.0f, 1.0f))
	{
		phongMaterial.diffuse = glm::vec3(phongMaterial.diffuse.x, phongMaterial.diffuse.x, phongMaterial.diffuse.x);
	}
	ImGui::SliderFloat3("Specular", glm::value_ptr(phongMaterial.specular), 0.0f, 1.0f);
	if (ImGui::SliderFloat("###Specular", &phongMaterial.specular.x, 0.0f, 1.0f))
	{
		phongMaterial.specular = glm::vec3(phongMaterial.specular.x, phongMaterial.specular.x, phongMaterial.specular.x);
	}
	if (ImGui::DragInt("shininess", &shininespow, 1, 1, 8))
	{
		phongMaterial.shininess = (float32)pow(2, shininespow);
	}
	ImGui::Text("shininess: %f", phongMaterial.shininess);
}
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
	phongShader.Delete();
	dragon.Destroy();
	cube.Destroy();
	gl::Destroy();
}

void Program::Init()
{
	gl::ClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	camera.Perspective(glm::radians(45.0f), 1.77f, 0.1f, 1000.0f);
	camera.SetPosition({ -10.0f, 14.0f, 14.0f });
	phongShader.Create();
	CreateCube();

	uint32 vs = gl::CreateShader("resources/shaders/LightShader.vert", gl::SHADER_TYPE_VERTEX);
	uint32 fs = gl::CreateShader("resources/shaders/LightShader.frag", gl::SHADER_TYPE_FRAGMENT);
	lightProgram = gl::CreateProgram(vs, fs, true);
	lightProjViewLoc = gl::GetUniformLocation(lightProgram, "projView");
	lightTransformLoc = gl::GetUniformLocation(lightProgram, "transform");
	lightColorLoc = gl::GetUniformLocation(lightProgram, "color");

	lights[0].type = LIGHT_TYPE_SUN;
	lights[0].index = 0;
	lights[1].type = LIGHT_TYPE_POINT;
	lights[1].index = 1;
}
void Program::Run()
{
	ImGuiIO& io = ImGui::GetIO();	

	CalculateTransform(dragon.transform, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	CalculateTransform(cube.transform, lights[1].position, glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, glm::vec3(0.2f, 0.2f, 0.2f));

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
		
		gl::Clear(gl::CLEAR_BIT_COLOR_DEPTH);
		gl::BindVertexArray(dragon.vao);

		phongShader.Bind(2, lights, phongMaterial, camera.ProjView(), camera.GetPosition());
		phongShader.BindTransform(dragon.transform);
		gl::DrawIndexed(gl::DRAW_MODE_TRIANGLES, dragon.indiceCount, gl::DATA_TYPE_UNSIGNED_INT, 0);
		//for light
		gl::BindVertexArray(cube.vao);
		gl::BindProgram(lightProgram);
		gl::SetUniformMat4(lightProjViewLoc, camera.ProjView(), false);
		gl::SetUniformMat4(lightTransformLoc, cube.transform, false);
		gl::SetUniformVec3(lightColorLoc, lights[1].color);
		gl::DrawIndexed(gl::DRAW_MODE_TRIANGLES, cube.indiceCount, gl::DATA_TYPE_UNSIGNED_INT, 0);
		//ui
		gl::UIBegin();
		ImGui::Begin("Settings");
		ImGui::Text("FPS: %f", io.Framerate);
		ImGui::Separator();
		if (ImGui::ListBox("Polygon Mode", &polygonMode, polygonModeNames, _countof(polygonModes)))
		{
			gl::PolygonMode(gl::FACE_FRONT_AND_BACK, polygonModes[polygonMode]);
		}
		ImGui::Text("Camera Position: %f, %f, %f", camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		ImGui::Separator();
		LightUI();		
		ImGui::Separator();
		MateriaUI();
		ImGui::End();
		gl::UIEnd();
		gl::SwapBuffers();
	}
}

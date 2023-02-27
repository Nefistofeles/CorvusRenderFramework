#include "Program.h"
float32 vertices[] ={
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
	vao = gl::CreateVertexArray();
	gl::BindVertexArray(vao);
	vbo = gl::CreateStaticVertexBuffer(sizeof(vertices), vertices);
	ebo = gl::CreateStaticIndexBuffer(sizeof(indices), indices);
	gl::LayoutElement layouts[] =
	{
		{0, 3, gl::DATA_TYPE_FLOAT, false},
		{1, 2, gl::DATA_TYPE_FLOAT, false},
		{2, 3, gl::DATA_TYPE_FLOAT, false},
	};
	gl::BindLayoutElements(_countof(layouts), layouts);
	gl::BindVertexArray(0);

	uint32 vs = gl::CreateShader("resources/shaders/BasicShader.vert", gl::SHADER_TYPE_VERTEX);
	uint32 fs = gl::CreateShader("resources/shaders/BasicShader.frag", gl::SHADER_TYPE_FRAGMENT);
	program = gl::CreateProgram(vs, fs, true);
}

void Program::CreateTexture()
{	
	gl::TextureParameter params = 
	{
		gl::TEXTURE_FILTER_LINEAR, gl::TEXTURE_FILTER_LINEAR,
		gl::TEXTURE_WRAP_CLAMP_TO_EDGE, gl::TEXTURE_WRAP_CLAMP_TO_EDGE, gl::TEXTURE_WRAP_CLAMP_TO_EDGE
	};
	textureId = gl::CreateTexture2D("resources/textures/wall.jpg", params);
	textureLoc = gl::GetUniformLocation(program, "sampler");
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
	gl::DeleteVertexArray(vao);
	gl::DeleteBuffer(vbo);
	gl::DeleteBuffer(ebo);
	gl::DeleteProgram(program);
	gl::DeleteTexture(textureId);
	gl::Destroy();
}

void Program::Init()
{
	gl::ClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	camera.Perspective(glm::radians(45.0f), 1.77f, 0.1f, 1000.0f);
}

void Program::Run()
{
	CreateCube();
	CreateTexture();
	ImGuiIO& io = ImGui::GetIO();
	uint32 projViewLoc = gl::GetUniformLocation(program, "projView");
	uint32 transformLoc = gl::GetUniformLocation(program, "transform");
	uint32 cameraPosLoc = gl::GetUniformLocation(program, "cameraPos");
	
	CalculateTransform(transform, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	uint32 lightAmbientLoc = gl::GetUniformLocation(program, "light.ambient");
	uint32 lightPositionLoc = gl::GetUniformLocation(program, "light.position");
	uint32 lightColorLoc = gl::GetUniformLocation(program, "light.color");

	uint32 lightVS = gl::CreateShader("resources/shaders/LightShader.vert", gl::SHADER_TYPE_VERTEX);
	uint32 lightFS = gl::CreateShader("resources/shaders/LightShader.frag", gl::SHADER_TYPE_FRAGMENT);
	lightProgram = gl::CreateProgram(lightVS, lightFS, true);
	uint32 lightProjViewLoc = gl::GetUniformLocation(lightProgram, "projView");
	uint32 lightTransformLoc = gl::GetUniformLocation(lightProgram, "transform");
	CalculateTransform(lightTransform, light.position, glm::vec3(0.0f, 0.0f, 1.0f), 1.0f, glm::vec3(0.2f, 0.2f, 0.2f));

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
		gl::BindProgram(program);
		gl::BindVertexArray(vao);
		gl::EnableVertexAttrib(vao, 1);
		gl::EnableVertexAttrib(vao, 2);
		
		gl::SetUniformFloat(lightAmbientLoc, light.ambient);
		gl::SetUniformVec3(lightPositionLoc, light.position);
		gl::SetUniformVec3(lightColorLoc, light.color);		
		gl::SetUniformVec3(cameraPosLoc, camera.GetPosition());

		gl::SetUniformMat4(projViewLoc, camera.ProjView(), false);
		gl::SetUniformMat4(transformLoc, transform, false);
		
		gl::BindTexture2D(textureId, 0, textureLoc);
		gl::DrawIndexed(gl::DRAW_MODE_TRIANGLES, _countof(indices), gl::DATA_TYPE_UNSIGNED_INT, 0);

		gl::BindProgram(lightProgram);
		gl::DisableVertexAttrib(vao, 1);//disable uv and normal for light shader
		gl::DisableVertexAttrib(vao, 2);
		gl::SetUniformMat4(lightProjViewLoc, camera.ProjView(), false);
		gl::SetUniformMat4(lightTransformLoc, lightTransform, false);

		gl::DrawIndexed(gl::DRAW_MODE_TRIANGLES, _countof(indices), gl::DATA_TYPE_UNSIGNED_INT, 0);
		
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
		//light factors
		ImGui::Separator();
		ImGui::Text("Light Settings");
		ImGui::SliderFloat("Ambient", &light.ambient, 0.0f, 1.0f);
		if (ImGui::DragFloat3("Light Position", glm::value_ptr(light.position), 0.1f, -100.0f, 100.0f))
		{
			CalculateTransform(lightTransform, light.position, glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, glm::vec3(0.2f, 0.2f, 0.2f));
		}
		ImGui::End();
		gl::UIEnd();
		gl::SwapBuffers();
	}
	gl::DeleteProgram(lightProgram);
}

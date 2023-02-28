#pragma once
#include "../graphics/Graphics.h"
#include "Camera.h"

using namespace Corvus;

class Program
{
public :
	Program();
	~Program();
	void Init();
	void Run();
private :
	int32 polygonMode = 2;
	cstring polygonModeNames[3] = { "Point", "Line", "Fill" };
	gl::POLYGON_MODE polygonModes[3] = { gl::POLYGON_MODE_POINT, gl::POLYGON_MODE_LINE, gl::POLYGON_MODE_FILL };

	Camera camera;
	SDL_bool relative = SDL_TRUE;
	uint32 vao = 0, vbo = 0, ebo = 0;

private :
	void CreateCube();
	void CreateTexture();
	void LoadLight();
	struct Cube
	{
		uint32 program = 0;
		glm::mat4 transform = glm::mat4(1.0f);
		uint32 projViewLoc = 0, transformLoc = 0;
		uint32 cameraPosLoc = 0;

		inline void Create()
		{
			uint32 vs = gl::CreateShader("resources/shaders/BasicShader.vert", gl::SHADER_TYPE_VERTEX);
			uint32 fs = gl::CreateShader("resources/shaders/BasicShader.frag", gl::SHADER_TYPE_FRAGMENT);
			program = gl::CreateProgram(vs, fs, true);
			projViewLoc = gl::GetUniformLocation(program, "projView");
			transformLoc = gl::GetUniformLocation(program, "transform");
			cameraPosLoc = gl::GetUniformLocation(program, "cameraPos");
			CalculateTransform(transform, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		inline void SetUniformVariables(const glm::mat4& projView, const glm::vec3& cameraPos)
		{
			gl::SetUniformMat4(projViewLoc, projView, false);
			gl::SetUniformMat4(transformLoc, transform, false);
			gl::SetUniformVec3(cameraPosLoc, cameraPos);
		}
	};
	Cube cube;
	struct Light
	{
		glm::vec3 position = glm::vec3(1.0f, 1.0f, 0.0f);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		glm::vec3 ambient = glm::vec3(0.2f, 0.2f, 0.2f);
		glm::vec3 diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
		glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f);
		//for cube program
		uint32 ambientLoc = 0, diffuseLoc = 0, specularLoc = 0;
		uint32 positionLoc = 0, colorLoc = 0;
		
		//for visualization
		glm::mat4 transform = glm::mat4(1.0f);
		uint32 program = 0;
		uint32 projViewLoc = 0, transformLoc = 0;
		uint32 colorVisLoc = 0;		

		inline void Create()
		{
			uint32 lightVS = gl::CreateShader("resources/shaders/LightShader.vert", gl::SHADER_TYPE_VERTEX);
			uint32 lightFS = gl::CreateShader("resources/shaders/LightShader.frag", gl::SHADER_TYPE_FRAGMENT);
			program = gl::CreateProgram(lightVS, lightFS, true);
			projViewLoc = gl::GetUniformLocation(program, "projView");
			transformLoc = gl::GetUniformLocation(program, "transform");
			colorVisLoc = gl::GetUniformLocation(program, "color");
			CalculateTransform(transform, position, glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, glm::vec3(0.2f, 0.2f, 0.2f));
		}

		inline void SetUniformVariables()
		{
			gl::SetUniformVec3(ambientLoc, ambient);
			gl::SetUniformVec3(diffuseLoc, diffuse);
			gl::SetUniformVec3(specularLoc, specular);
			gl::SetUniformVec3(positionLoc, position);
			gl::SetUniformVec3(colorLoc, color);

		}
		inline void SetUniformForVisualizationVariables(const glm::mat4& projView)
		{
			gl::SetUniformMat4(projViewLoc, projView, false);
			gl::SetUniformMat4(transformLoc, transform, false);
			gl::SetUniformVec3(colorVisLoc, color);
		}
	};
	Light light;
	struct Material
	{
		uint32 diffuse = 0;
		uint32 specular = 0;
		float32 shininess = 0;
		uint32 diffuseLoc = 0, specularLoc = 0, shininesLoc = 0;

		void SetUnfiromVariables()
		{
			gl::BindTexture2D(diffuse, 0, diffuseLoc);
			gl::BindTexture2D(specular, 1, specularLoc);
			gl::SetUniformFloat(shininesLoc, shininess);
		}
	};
	int32 shininespow = 1;
	Material material;
};


#pragma once
#include "../core/Math.h"

class Camera
{
private:
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 projView = glm::mat4(1.0f);

	glm::vec3 cameraPos = glm::vec3(-3.0f, 0.0f, 0.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float32 pitch = 0, yaw = 0, roll = 0;
	float32 cameraSpeed = 5.0f;

	void FPSControl();
public:
	Camera();
	void ProcessInput();
	void Perspective(float32 fov, float32 aspect, float32 n, float32 f);
	glm::mat4 ProjView();
	glm::mat4 View();
	glm::mat4 Proj();
	glm::vec3 GetPosition();
};


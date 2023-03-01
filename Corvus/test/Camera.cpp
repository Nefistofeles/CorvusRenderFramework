#include "Camera.h"
#include "../imgui/GraphicsUi.h"

void Camera::FPSControl()
{
	const float32 sensitivity = 0.1f;
	int32 x = 0;
	int32 y = 0;
	SDL_GetRelativeMouseState(&x, &y);
	float32 deltaX = static_cast<float32>(x);
	float32 deltaY = static_cast<float32>(y);

	yaw += deltaX * sensitivity;
	pitch -= deltaY * sensitivity;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}
Camera::Camera()
{
	view = glm::lookAt(cameraPos, cameraFront + cameraPos, cameraUp);
	projView = proj * view;
}
void Camera::ProcessInput()
{
	FPSControl();
	ImGuiIO& io = ImGui::GetIO();
	if (ImGui::IsKeyDown(ImGuiKey_W))
	{
		cameraPos += cameraFront * cameraSpeed * io.DeltaTime;
	}
	if (ImGui::IsKeyDown(ImGuiKey_S))
	{
		cameraPos -= cameraFront * cameraSpeed * io.DeltaTime;
	}
	if (ImGui::IsKeyDown(ImGuiKey_A))
	{
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * io.DeltaTime;
	}
	if (ImGui::IsKeyDown(ImGuiKey_D))
	{
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * io.DeltaTime;
	}
	view = glm::lookAt(cameraPos, cameraFront + cameraPos, cameraUp);
	projView = proj * view;
}
void Camera::Perspective(float32 fov, float32 aspect, float32 n, float32 f)
{
	proj = glm::perspective(fov, aspect, n, f);
	projView = proj * view;
}
glm::mat4 Camera::ProjView()
{
	return projView;
}

glm::mat4 Camera::View()
{
	return view;
}

glm::mat4 Camera::Proj()
{
	return proj;
}

glm::vec3 Camera::GetPosition()
{
	return cameraPos;
}

void Camera::SetPosition(const glm::vec3& position)
{
	cameraPos = position;
}

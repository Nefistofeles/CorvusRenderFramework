#include "GraphicsUi.h"

namespace Corvus::ui
{
	void Init(SDL_Window* pWindow, SDL_GLContext context, cstring glslVersion)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();

		ImGui_ImplSDL2_InitForOpenGL(pWindow, context);
		ImGui_ImplOpenGL3_Init(glslVersion);
	}
	void Destroy()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}
	void Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

	}
	void End()
	{
		ImGui::Render();
	}
	void Render()
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
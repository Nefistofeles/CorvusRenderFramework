#pragma once
#include <SDL2/SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "../core/Core.h"

namespace Corvus::ui
{
	void Init(SDL_Window* pWindow, SDL_GLContext context, cstring glslVersion);
	void Destroy();
	void Begin();
	void End();
	void Render();
}



#pragma once
#include <glad/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include "../core/UniquePtr.h"
#include "../core/Array.h"
#include "../core/Math.h"
#include "../imgui/imgui.h"

namespace Corvus::gl
{
	struct Graphics
	{
		SDL_Window* pWindow = nullptr;
		SDL_GLContext context = 0;
		HWND hwnd = 0;
		Graphics() = default;
		~Graphics() = default;
	};
	Graphics* Gfx();
	enum INPUT_TYPE
	{
		CLOSE = 0,
		NONE = 1,
		RESIZED = 2
	};
	void Init(int32 width, int32 height, cstring title);
	void Destroy();
	void RelativeMouse(SDL_bool isTrue);
	void WindowMouseGrab(SDL_bool isTrue);
	void SwapBuffers();

	INPUT_TYPE PollEvents();
	void Vsync(bool32 vsync = 1);
	void UIBegin();
	void UIEnd();

	enum CLEAR_BIT
	{
		CLEAR_BIT_COLOR = GL_COLOR_BUFFER_BIT,
		CLEAR_BIT_DEPTH = GL_DEPTH_BUFFER_BIT,
		CLEAR_BIT_STENCIL = GL_STENCIL_BUFFER_BIT,
		CLEAR_BIT_COLOR_DEPTH = (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT),
		CLEAR_BIT_COLOR_DEPTH_STENCIL = (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT),

	};
	void Clear(CLEAR_BIT bit);
	void ClearColor(float32 r, float32 g, float32 b, float32 a);
}


#include "Graphics.h"
#include "../imgui/GraphicsUi.h"

namespace Corvus::gl
{
	void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		//if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;
		std::string error;
		error += "id " + std::to_string(id) + "\n";
		error += "message " + std::string(message) + "\n";

		switch (source)
		{
		case GL_DEBUG_SOURCE_API:             error += "Source: API\n";              break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   error += "Source: Window System\n";    break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER: error += "Source: Shader Compiler\n";  break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:     error += "Source: Third Party\n";      break;
		case GL_DEBUG_SOURCE_APPLICATION:     error += "Source: Application\n";      break;
		case GL_DEBUG_SOURCE_OTHER:           error += "Source: Other\n";            break;
		}
		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR:                error += "Type: Error\n";                break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:  error += "Type: Deprecated Behaviour\n"; break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:   error += "Type: Undefined Behaviour\n";  break;
		case GL_DEBUG_TYPE_PORTABILITY:          error += "Type: Portability\n";          break;
		case GL_DEBUG_TYPE_PERFORMANCE:          error += "Type: Performance\n";          break;
		case GL_DEBUG_TYPE_MARKER:               error += "Type: Marker\n";               break;
		case GL_DEBUG_TYPE_PUSH_GROUP:           error += "Type: Push Group\n";           break;
		case GL_DEBUG_TYPE_POP_GROUP:            error += "Type: Pop Group\n";            break;
		case GL_DEBUG_TYPE_OTHER:                error += "Type: Other\n";                break;
		}
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			error += "Severity: high\n";
			PRINT_ERROR(error.c_str());
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			error += "Severity: medium\n";
			PRINT_ERROR(error.c_str());
			break;
		case GL_DEBUG_SEVERITY_LOW:
			error += "Severity: low\n";
			PRINT_WARNING(error.c_str());
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			error += "Severity: notification\n";
			PRINT_INFO(error.c_str());
			break;
		}
	}
	Graphics* Gfx()
	{
		static Corvus::UniquePtr<Graphics> graphics = new Graphics();
		return graphics.Get();
	}

	void Init(int32 width, int32 height, cstring title)
	{
		NASSERT(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0, "SDL2 init failed");
		SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
#ifdef _DEBUG
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif
		Graphics* gfx = Gfx();
		SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);
		gfx->pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);
		NASSERT(gfx->pWindow == nullptr, "SDL_Window init failed");
		gfx->context = SDL_GL_CreateContext(gfx->pWindow);
		SDL_GL_MakeCurrent(gfx->pWindow, gfx->context);
		int32 version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
		NASSERT(!version, "gload load failed");
		PRINT_INFO("OpenGL version ", GLAD_VERSION_MAJOR(version), " ", GLAD_VERSION_MINOR(version));
#ifdef _DEBUG
		int32 flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(MessageCallback, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}
#endif
		SDL_SysWMinfo wmInfo;
		SDL_VERSION(&wmInfo.version);
		SDL_GetWindowWMInfo(gfx->pWindow, &wmInfo);
		gfx->hwnd = (HWND)wmInfo.info.win.window;

		ui::Init(gfx->pWindow, gfx->context, "#version 330 core");
		glViewport(0, 0, width, height);
		gl::Vsync(1);
	}
	void Destroy()
	{
		SDL_GL_DeleteContext(Gfx()->context);
		SDL_DestroyWindow(Gfx()->pWindow);
		SDL_Quit();
	}
	void RelativeMouse(SDL_bool isTrue)
	{
		SDL_SetRelativeMouseMode(isTrue);
	}
	void WindowMouseGrab(SDL_bool isTrue)
	{
		SDL_SetWindowMouseGrab(Gfx()->pWindow, isTrue);
	}
	void SwapBuffers()
	{
		SDL_GL_SwapWindow(Gfx()->pWindow);
		//SDL_Delay(1);
	}
	void Vsync(bool32 vsync)
	{
		SDL_GL_SetSwapInterval(vsync);
	}
	INPUT_TYPE PollEvents()
	{
		SDL_Event ev;
		while (SDL_PollEvent(&ev))
		{
			ImGui_ImplSDL2_ProcessEvent(&ev);
			if (ev.type == SDL_QUIT)
				return INPUT_TYPE::CLOSE;
			if (ev.type == SDL_WINDOWEVENT && ev.window.event == SDL_WINDOWEVENT_CLOSE)
				return INPUT_TYPE::CLOSE;
			if (ev.type == SDL_WINDOWEVENT)
			{
				if (ev.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					glViewport(0, 0, ev.window.data1, ev.window.data2);
					return INPUT_TYPE::RESIZED;
				}
			}
		}
		return INPUT_TYPE::NONE;
	}
	void UIBegin()
	{
		ui::Begin();
	}
	void UIEnd()
	{
		ui::End();
		ui::Render();
	}
	void Clear(CLEAR_BIT bit)
	{
		glClear(bit);
	}
	void ClearColor(float32 r, float32 g, float32 b, float32 a)
	{
		glClearColor(r, g, b, a);
	}
}

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
	enum DATA_TYPE
	{
		DATA_TYPE_BYTE = GL_BYTE,
		DATA_TYPE_UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
		DATA_TYPE_SHORT = GL_SHORT,
		DATA_TYPE_UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
		DATA_TYPE_INT = GL_INT,
		DATA_TYPE_UNSIGNED_INT = GL_UNSIGNED_INT,
		DATA_TYPE_FLOAT = GL_FLOAT,
	};
	int64 GetDataSize(int32 type);
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
		CLEAR_BIT_COLOR_DEPTH_STENCIL = (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)
	};
	void Clear(CLEAR_BIT bit);
	void ClearColor(float32 r, float32 g, float32 b, float32 a);
	void Viewport(int32 x, int32 y, int32 width, int32 height);

	enum DRAW_MODE
	{
		DRAW_MODE_POINTS = GL_POINTS,
		DRAW_MODE_LINES = GL_LINES,
		DRAW_MODE_LINE_LOOP = GL_LINE_LOOP,
		DRAW_MODE_LINE_STRIP = GL_LINE_STRIP,
		DRAW_MODE_TRIANGLES = GL_TRIANGLES,
		DRAW_MODE_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
		DRAW_MODE_TRIANGLE_FAN = GL_TRIANGLE_FAN,

	};
	void DrawArrays(DRAW_MODE mode, int32 first, int32 count);


	uint32 CreateVertexArray();
	void BindVertexArray(const uint32& id);
	void DeleteVertexArray(uint32& id);

	struct LayoutElement
	{
		uint32 index;
		uint32 count;
		DATA_TYPE type;
		uint8 normalized;
		LayoutElement() : index(0), count(0), type(DATA_TYPE_FLOAT), normalized(false) {}
		LayoutElement(uint32 index, uint32 count, DATA_TYPE type, uint8 normalized) : index(index), count(count), type(type), normalized(normalized) {}
	};
	enum BUFFER_TARGET
	{
		BUFFER_TARGET_VERTEX = GL_ARRAY_BUFFER,
		BUFFER_TARGET_INDEX = GL_ELEMENT_ARRAY_BUFFER
	};
	enum BUFFER_USAGE
	{
		BUFFER_USAGE_STATIC = GL_STATIC_DRAW,
		BUFFER_USAGE_DYNAMIC = GL_DYNAMIC_DRAW,
		BUFFER_USAGE_STREAM = GL_STREAM_DRAW,
	};
	uint32 CreateBuffer(BUFFER_TARGET target, int64 size, const void* data, BUFFER_USAGE usage);
	uint32 CreateStaticVertexBuffer(int64 size, const void* data);
	uint32 CreateStaticIndexBuffer(int64 size, uint32* data);
	void BindLayoutElements(uint32 count, LayoutElement* elements);
	void BindBuffer(BUFFER_TARGET target, const uint32& id);
	void BindVertexBuffer(const uint32& id);
	void BindIndexBuffer(const uint32& id);
	void DeleteBuffer(uint32& id);

	enum SHADER_TYPE
	{
		SHADER_TYPE_VERTEX = GL_VERTEX_SHADER,
		SHADER_TYPE_FRAGMENT = GL_FRAGMENT_SHADER,
		SHADER_TYPE_COMPUTE = GL_COMPUTE_SHADER
	};

	uint32 CreateShader(cstring path, SHADER_TYPE type);
	uint32 CreateProgram(uint32& vs, uint32& fs, bool afterDeleteShaders);
	void DeleteProgram(uint32& program);
	void BindProgram(const uint32& program);
	uint32 GetUniformLocation(const uint32& program, cstring name);
	void SetUniformFloat(const uint32& location, const float32& data);
	void SetUniformInt(const uint32& location, const int32& data);
	void SetUniformVec2(const uint32& location, const glm::vec2& data);
	void SetUniformVec3(const uint32& location, const glm::vec3& data);
	void SetUniformVec4(const uint32& location, const glm::vec4& data);
	void SetUniformMat4(const uint32& location, const glm::mat4& data, bool32 normalized);
}


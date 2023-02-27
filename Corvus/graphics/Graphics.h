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
	enum FACE
	{
		FACE_FRONT_LEFT = GL_FRONT_LEFT,
		FACE_FRONT_RIGHT = GL_FRONT_RIGHT,
		FACE_BACK_LEFT = GL_BACK_LEFT,
		FACE_BACK_RIGHT = GL_BACK_RIGHT,
		FACE_FRONT = GL_FRONT,
		FACE_BACK = GL_BACK,
		FACE_LEFT = GL_LEFT,
		FACE_RIGHT = GL_RIGHT,
		FACE_FRONT_AND_BACK = GL_FRONT_AND_BACK,
	};
	enum POLYGON_MODE
	{
		POLYGON_MODE_POINT = GL_POINT,
		POLYGON_MODE_LINE = GL_LINE,
		POLYGON_MODE_FILL = GL_FILL,
	};
	void PolygonMode(FACE face, POLYGON_MODE mode);
	enum TEST
	{
		TEST_DEPTH = GL_DEPTH_TEST,
		TEST_STENCIL = GL_STENCIL_TEST,
		TEST_CULL_FACE = GL_CULL_FACE,
		TEST_BLEND = GL_BLEND
	};
	enum DRAW_ORDER
	{
		DRAW_ORDER_CLOCKWISE = GL_CW,
		DRAW_ORDER_COUNTER_CLOCKWISE = GL_CCW,
	};
	void Enable(TEST bit);
	void Disable(TEST bit);
	void CullFace(FACE face);
	void FrontFace(DRAW_ORDER order);

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
	void DrawIndexed(DRAW_MODE mode, int32 count, DATA_TYPE dataType, const void* indices);

	uint32 CreateVertexArray();
	void BindVertexArray(const uint32& id);
	void DeleteVertexArray(uint32& id);
	void EnableVertexAttrib(uint32 vao, uint32 index);
	void DisableVertexAttrib(uint32 vao, uint32 index);
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

	enum TEXTURE_TYPE
	{
		TEXTURE_TYPE_1D = GL_TEXTURE_1D,
		TEXTURE_TYPE_2D = GL_TEXTURE_2D,
		TEXTURE_TYPE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
		TEXTURE_TYPE_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
		TEXTURE_TYPE_CUBE_MAP = GL_TEXTURE_CUBE_MAP
	};
	enum TEXTURE_FILTER_PNAME
	{
		TEXTURE_FILTER_MAG_FILTER = GL_TEXTURE_MAG_FILTER,
		TEXTURE_FILTER_MIN_FILTER = GL_TEXTURE_MIN_FILTER,
	};
	enum TEXTURE_FILTER_PARAM
	{
		TEXTURE_FILTER_NEAREST = GL_NEAREST,
		TEXTURE_FILTER_LINEAR = GL_LINEAR,
		TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
		TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
		TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
		TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
	};
	enum TEXTURE_WRAP_PNAME
	{
		TEXTURE_WRAP_S = GL_TEXTURE_WRAP_S,
		TEXTURE_WRAP_T = GL_TEXTURE_WRAP_T,
		TEXTURE_WRAP_R = GL_TEXTURE_WRAP_R,
	};
	enum TEXTURE_WRAP_PARAM
	{
		TEXTURE_WRAP_REPEAT = GL_REPEAT,
		TEXTURE_WRAP_MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
		TEXTURE_WRAP_CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
	};
	enum TEXTURE_FORMAT
	{
		TEXTURE_FORMAT_RGB = GL_RGB,
		TEXTURE_FORMAT_RGBA = GL_RGBA,
	};
	struct TextureParameter
	{
		TEXTURE_FILTER_PARAM filterMin = TEXTURE_FILTER_LINEAR;
		TEXTURE_FILTER_PARAM filterMag = TEXTURE_FILTER_LINEAR;

		TEXTURE_WRAP_PARAM wrap_s = TEXTURE_WRAP_CLAMP_TO_EDGE;
		TEXTURE_WRAP_PARAM wrap_t = TEXTURE_WRAP_CLAMP_TO_EDGE;
		TEXTURE_WRAP_PARAM wrap_r = TEXTURE_WRAP_CLAMP_TO_EDGE;

		TextureParameter() = default;
		TextureParameter(
			TEXTURE_FILTER_PARAM filterMin,
			TEXTURE_FILTER_PARAM filterMag,
			TEXTURE_WRAP_PARAM wrap_s,
			TEXTURE_WRAP_PARAM wrap_t,
			TEXTURE_WRAP_PARAM wrap_r) :
			filterMin(filterMin),
			filterMag(filterMag),
			wrap_s(wrap_s),
			wrap_t(wrap_t),
			wrap_r(wrap_r)
		{
		}
	};
	uint32 CreateTexture(cstring path, TEXTURE_TYPE target, TextureParameter params);
	uint32 CreateTexture2D(cstring path, TextureParameter params);
	void BindTexture(TEXTURE_TYPE target, const uint32& id);
	void BindTexture2D(const uint32& id);
	void BindTexture2D(const uint32& id, const uint32& active);
	void BindTexture2D(const uint32& id, const uint32& active, const uint32& location);
	void DeleteTexture(uint32& id);
	void ActivateTexture(const int32& i);
}


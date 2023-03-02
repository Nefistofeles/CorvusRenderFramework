#include "ScreenBuffer.h"

ScreenBuffer::ScreenBuffer(int32 width, int32 height)
{
	fbo = gl::CreateFrameBuffer();
	gl::BindFrameBuffer(fbo);

	gl::TextureParameter params =
	{
		gl::TEXTURE_FILTER_LINEAR, gl::TEXTURE_FILTER_LINEAR,
		gl::TEXTURE_WRAP_CLAMP_TO_EDGE,gl::TEXTURE_WRAP_CLAMP_TO_EDGE,gl::TEXTURE_WRAP_CLAMP_TO_EDGE
	};
	screenTexture = gl::CreateTexture(gl::TEXTURE_TYPE_2D, gl::TEXTURE_FORMAT_RGB, 1366, 768, params);
	gl::SetFrameBufferTexture2D(gl::ATTACHMENT_COLOR0, screenTexture);

	rbo = gl::CreateRenderBuffer();
	gl::BindRenderBuffer(rbo);
	gl::SetRenderBufferStorage(gl::ATTACHMENT_DATA_TYPE_DEPTH24_STENCIL8, 1366, 768);
	gl::SetFrameBufferRenderBuffer(gl::ATTACHMENT_DEPTH_STENCIL, rbo);
	if (!gl::CheckFrameBufferCompleted())
		DEBUG("fbo create failed");
	gl::BindFrameBuffer(0);

	uint32 vs = gl::CreateShader("resources/shaders/ScreenShader.vert", gl::SHADER_TYPE_VERTEX);
	uint32 fs = gl::CreateShader("resources/shaders/ScreenShader.frag", gl::SHADER_TYPE_FRAGMENT);
	program = gl::CreateProgram(vs, fs, true);
	samplerLoc = gl::GetUniformLocation(program, "sampler");
}
ScreenBuffer::~ScreenBuffer()
{
	gl::DeleteFrameBuffer(fbo);
	gl::DeleteRenderBuffer(rbo);
	gl::DeleteProgram(program);
	gl::DeleteTexture(screenTexture);
}

void ScreenBuffer::Start()
{
	gl::BindFrameBuffer(fbo);
}
void ScreenBuffer::End()
{
	gl::BindFrameBuffer(0);
}
void ScreenBuffer::Draw(const float32 color[4])
{
	gl::Disable(gl::TEST_DEPTH);
	gl::Clear(gl::CLEAR_BIT_COLOR);
	gl::ClearColor(color[0], color[1], color[2], color[3]);
	gl::BindProgram(program);
	gl::BindTexture2D(screenTexture, 0, samplerLoc);
	gl::DrawArrays(gl::DRAW_MODE_TRIANGLE_STRIP, 0, 4);
	gl::Enable(gl::TEST_DEPTH);
}
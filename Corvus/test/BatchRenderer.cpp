#include "BatchRenderer.h"

void BatchRenderer::CalculateRotScaleMatrix(glm::vec4& mat, const float32& angle, const glm::vec2& scale)
{
	float32    sinAngle = sinf(angle);
	float32    cosAngle = cosf(angle);
	mat = glm::vec4(
		cosAngle * scale.x, sinAngle * scale.y,
		-sinAngle * scale.x, cosAngle * scale.y
	);
}

BatchRenderer::BatchRenderer(uint32 maxQuadSize, uint32 maxBatchSize)
	: maxQuadSize(maxQuadSize), maxBatchSize(maxBatchSize)
{
	quads.Resize(maxQuadSize);

	gl::LayoutElement elements[] =
	{
		{0, 2, gl::DATA_TYPE_FLOAT, false, gl::INPUT_ELEMENT::INPUT_ELEMENT_FREQUENCY_PER_INSTANCE},
		{1, 4, gl::DATA_TYPE_FLOAT, false, gl::INPUT_ELEMENT::INPUT_ELEMENT_FREQUENCY_PER_INSTANCE},
	};
	vao = gl::CreateVertexArray();
	gl::BindVertexArray(vao);
	vbo = gl::CreateDynamicVertexBuffer(sizeof(Quad) * maxBatchSize);
	gl::BindLayoutElements(_countof(elements), elements);
	gl::BindVertexArray(0);
	
	uint32 vs = gl::CreateShader("resources/shaders/Quad.vert", gl::SHADER_TYPE_VERTEX);
	uint32 fs = gl::CreateShader("resources/shaders/Quad.frag", gl::SHADER_TYPE_FRAGMENT);
	program = gl::CreateProgram(vs, fs, true);
	projViewLoc = gl::GetUniformLocation(program, "projView");
	textureLoc = gl::GetUniformLocation(program, "sampler");
	gl::TextureParameter params =
	{
		gl::TEXTURE_FILTER_LINEAR, gl::TEXTURE_FILTER_LINEAR,
		gl::TEXTURE_WRAP_CLAMP_TO_EDGE, gl::TEXTURE_WRAP_CLAMP_TO_EDGE, gl::TEXTURE_WRAP_CLAMP_TO_EDGE
	};
	texture = gl::CreateTexture2D("resources/textures/flash.png", params, true);
}

BatchRenderer::~BatchRenderer()
{
	gl::DeleteVertexArray(vao);
	gl::DeleteBuffer(vbo);
	gl::DeleteProgram(program);
	gl::DeleteTexture(texture);
}

void BatchRenderer::SetViewProj(const glm::mat4& matrix)
{
	projView = matrix;
}

void BatchRenderer::Begin()
{
	quads.Reset();
	gl::BindProgram(program);
	gl::SetUniformMat4(projViewLoc, projView, false);
	gl::BindTexture2D(texture, 0, textureLoc);
}

void BatchRenderer::End()
{
	if (quads.AvaliableSize() <= 0)
		return;
	gl::BindVertexArray(vao);
	int32 totalSize = quads.AvaliableSize();
	int32 drawCount = totalSize / maxBatchSize + (totalSize % maxBatchSize != 0 ? 1 : 0);
	for (int32 draw = 0; draw < drawCount; draw++)
	{
		int32 drawStart = draw * maxBatchSize;
		int32 drawEnd = drawStart + maxBatchSize;
		if (drawCount - 1 == draw)
		{
			drawEnd = totalSize;
		}
		gl::BindVertexBuffer(vbo);
		Quad* data = (Quad*)gl::MapVertexBuffer(gl::ACCESS_FLAG_WRITE);
		memcpy(data, &quads[drawStart], (drawEnd - drawStart) * sizeof(Quad));
		gl::UnMapVertexBuffer();
		gl::DrawInstanced(gl::DRAW_MODE_TRIANGLE_STRIP, 0, 4, drawEnd - drawStart);
	}
	gl::BindVertexArray(0);
}

void BatchRenderer::Draw(const glm::vec2& pos, const float32& rot, const glm::vec2& scale)
{
	if (quads.AvaliableSize() == quads.Size())	//discard more draw functionality if avaliableSize >= size
		return;
	Quad quad = {};
	quad.position = pos;
	CalculateRotScaleMatrix(quad.rotScale, rot, scale);
	quads.Emplace(quad);
}


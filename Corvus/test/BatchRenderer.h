#pragma once
#include "../graphics/Graphics.h"
#include "../core/Array.h"
using namespace Corvus;

class BatchRenderer
{
private :
	struct Quad
	{
		glm::vec2 position = glm::vec2(0.0f, 0.0f);
		glm::vec4 rotScale = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		Quad() = default;
		Quad(const glm::vec2& position, const glm::vec4& rotScale)
			: position(position), rotScale(rotScale)
		{
		}
	};
	uint32 maxQuadSize = 0;
	uint32 maxBatchSize = 1000;
	uint32 vao = 0, vbo = 0;
	uint32 program = 0, projViewLoc = 0;
	uint32 texture = 0, textureLoc = 0;
	Array<Quad> quads;
	glm::mat4 projView = glm::mat4(1.0f);

	void CalculateRotScaleMatrix(glm::vec4& mat, const float32& angle, const glm::vec2& scale);
public :
	BatchRenderer(uint32 maxQuadSize, uint32 maxBatchSize);
	~BatchRenderer();
	void SetViewProj(const glm::mat4& matrix);
	void Begin();
	void End();
	void Draw(const glm::vec2& pos, const float32& rot, const glm::vec2& scale);
};
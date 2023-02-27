#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Core.h"

namespace Corvus
{
	inline void CalculateTransform(glm::mat4& transform, const glm::vec3& pos, const glm::vec3& rotDir, const float32 rot, const glm::vec3& scale)
	{
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, pos);
		transform = glm::rotate(transform, rot, rotDir);
		transform = glm::scale(transform, scale);
	}
}
#include "objects.h"

namespace eng
{

	Triangle::Triangle(const glm::mat2x3& vertices, const glm::vec4& color)
		: m_VertexBuffer(vertices), m_Color(color)
	{
	}

}
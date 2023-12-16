#include "objects.h"

namespace eng
{

	Triangle::Triangle(const glm::mat2x3& vertices, const glm::vec4& color)
		: m_IndexBuffer(glm::uvec4(0, 1, 2, 0)), m_VertexBuffer(vertices), m_Color(color)
	{
	}

	void Triangle::Draw(Renderer* renderer)
	{
		renderer->Draw(m_VertexArray.GetId());
	}

}
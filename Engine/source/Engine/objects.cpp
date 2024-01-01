#include "objects.h"

namespace eng
{

	Triangle::Triangle(const glm::mat3x2& vertices, const glm::fvec4& color)
		: m_IndexBuffer(glm::uvec4(0, 1, 2, 0)), m_VertexBuffer(vertices, color)
	{
	}

	void Triangle::Draw(Renderer* renderer)
	{
		renderer->Draw(m_VertexArray.GetId());
	}

	void Triangle::SetPosition(const glm::mat3x2& vertices)
	{
		m_VertexBuffer.SetData(vertices, m_VertexBuffer.GetColor());
	}

}
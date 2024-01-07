#include "objects.h"

namespace eng
{

	Triangle::Triangle(const glm::mat3x2& vertices, const glm::fvec4& color)
		: m_IndexBuffer(glm::uvec4(0, 1, 2, 0)), m_VertexBuffer(vertices, color)
	{
	}

	glm::fvec2 Triangle::GetCenter() const
	{
		const glm::mat3x2& vertices = m_VertexBuffer.GetVertices();

		const float x = (vertices[0][0] + vertices[1][0] + vertices[2][0]) / 3;
		const float y = (vertices[0][1] + vertices[1][1] + vertices[2][1]) / 3;

		return glm::fvec2(x, y);
	}

	void Triangle::Draw(Renderer* renderer)
	{
		renderer->Draw(m_VertexArray.GetId());
	}

	void Triangle::SetPosition(const glm::mat3x2& vertices)
	{
		m_VertexBuffer.SetData(vertices, m_VertexBuffer.GetColor());
	}

	void Triangle::SetRotation(float angle)
	{
		float sinus = glm::sin(angle);
		float cosinus = glm::cos(angle);

		glm::fvec2 pivot = GetCenter();

		glm::mat3x2 vertices = m_VertexBuffer.GetVertices();

		for (std::uint32_t i = 0; i < 3; i++)
		{
			glm::fvec2 currentPoint(vertices[i][0], vertices[i][1]);

			float x = (currentPoint.x - pivot.x) * cosinus - (currentPoint.y - pivot.y) * sinus + pivot.x;
			float y = (currentPoint.x - pivot.x) * sinus + (currentPoint.y - pivot.y) * cosinus + pivot.y;

			vertices[i] = { currentPoint.x, currentPoint.y };
		}

		m_VertexArray.Bind();
		m_VertexBuffer.SetData(vertices, m_VertexBuffer.GetColor());
	}

}
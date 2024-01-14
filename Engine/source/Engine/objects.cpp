#include "objects.h"

namespace eng
{

	Triangle::Triangle(const glm::mat3x2& vertices, const glm::fvec4& color)
		: m_IndexBuffer(glm::uvec4(0, 1, 2, 0)), m_VertexBuffer(vertices, color)
	{
	}

	Triangle::Triangle(const Triangle& other)
		: m_IndexBuffer(other.m_IndexBuffer), m_VertexBuffer(other.m_VertexBuffer)
	{
	}

	glm::fvec2 Triangle::GetCenter() const
	{
		const glm::mat3x2& positions = m_VertexBuffer.GetPositions();

		const float x = (positions[0][0] + positions[1][0] + positions[2][0]) / 3;
		const float y = (positions[0][1] + positions[1][1] + positions[2][1]) / 3;

		return glm::fvec2(x, y);
	}

	void Triangle::Draw(Renderer* renderer)
	{
		renderer->Draw(m_VertexArray.GetId());
	}

	void Triangle::Rotate(float radians)
	{
		float degrees = glm::degrees(radians);

		float sinus = glm::sin(degrees);
		float cosinus = glm::cos(degrees);

		glm::mat3x2 positions = m_VertexBuffer.GetPositions();

		for (std::uint32_t i = 0; i < 3; i++)
		{
			glm::fvec2 position = positions[i];

			float x = position.x;
			float y = position.y;

			float xp = x * cosinus - y * sinus;
			float yp = x * sinus + y * cosinus;

			glm::fvec2 newPosition(xp, yp);

			positions[i] = newPosition;
		}

		m_VertexBuffer.SetData(positions, m_VertexBuffer.GetColor());
	}

}
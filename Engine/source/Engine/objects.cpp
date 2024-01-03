#include "objects.h"

namespace eng
{

	Triangle::Triangle(const glm::mat3x2& vertices, const glm::fvec4& color)
		: m_IndexBuffer(glm::uvec4(0, 1, 2, 0)), m_VertexBuffer(vertices, color)
	{
	}

	glm::fvec2 Triangle::GetCenter() const
	{
		glm::mat3x2 vertices = m_VertexBuffer.GetVertices();

		for (std::int32_t i = 0; i < 3; i++)
		{

		}

		return glm::fvec2();
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

		// TODO: Zmienić pivot na środek trójkąta.
		glm::fvec2 pivot(0.0f, 0.0f);

		glm::mat3x2 vertices = m_VertexBuffer.GetVertices();

		for (std::uint32_t i = 0; i < 3; i++)
		{
			glm::fvec2 currentPoint(vertices[i][0], vertices[i][1]);

			currentPoint.x -= pivot.x;
			currentPoint.y -= pivot.y;

			float x = currentPoint.x * cosinus - currentPoint.y * sinus;
			float y = currentPoint.x * sinus - currentPoint.y * cosinus;

			currentPoint.x = x + pivot.x;
			currentPoint.y = y + pivot.y;

			vertices[i] = { currentPoint.x, currentPoint.y };
		}

		m_VertexBuffer.SetData(vertices, m_VertexBuffer.GetColor());
	}

}
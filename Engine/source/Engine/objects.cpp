#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "objects.h"

namespace eng
{

	Triangle::Triangle(const glm::mat3x4& positions, const glm::fvec4& color)
		: m_IndexBuffer(glm::uvec4(0, 1, 2, 0)), m_VertexBuffer(positions, color)
	{
	}

	Triangle::Triangle(const glm::mat3x4& positions, const glm::fvec4& color, const glm::mat3x2& texCoords)
		: m_IndexBuffer(glm::uvec4(0, 1, 2, 0)), m_VertexBuffer(positions, color, texCoords)
	{
	}

	Triangle::Triangle(const Triangle& other)
		: m_IndexBuffer(other.m_IndexBuffer), m_VertexBuffer(other.m_VertexBuffer)
	{
	}

	glm::fvec4 Triangle::GetCenter() const
	{
		const glm::mat3x4& positions = m_VertexBuffer.GetPositions();

		const float x = (positions[0][0] + positions[1][0] + positions[2][0]) / 3;
		const float y = (positions[0][1] + positions[1][1] + positions[2][1]) / 3;
		const float z = (positions[0][1] + positions[1][2] + positions[2][2]) / 3;
		const float w = (positions[0][1] + positions[1][3] + positions[2][3]) / 3;

		return glm::fvec4(x, y, z, w);
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

		glm::mat3x4 positions = m_VertexBuffer.GetPositions();

		for (std::uint32_t i = 0; i < 3; i++)
		{
			glm::fvec4 position = positions[i];

			float x = position.x;
			float y = position.y;
			float z = position.y;
			float w = position.y;

			float xp = x * cosinus - y * sinus;
			float yp = x * sinus + y * cosinus;

			glm::fvec4 newPosition(xp, yp, z, w);

			positions[i] = newPosition;
		}

		m_VertexBuffer.SetData(positions, m_VertexBuffer.GetColor(), m_VertexBuffer.GetTexCoords());
	}

	Texture::Texture(const std::string& filePath)
		: m_Path(filePath)
	{
		std::int32_t width = 0, height = 0, nChannels = 0;
		unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nChannels, 0);

		glGenTextures(1, &m_Id);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_Id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}

	Cube::Cube(const glm::vec4& position, float length)
	{
		const glm::fvec4 color(1.0f, 0.0f, 0.0f, 1.0f);

		// Przód
		{
			// 1
			glm::mat3x4 pos1 = {};
			pos1[0] = position;
			pos1[1] = position + glm::fvec4(length, 0.0f, 0.0f, 0.0f);
			pos1[2] = position + glm::fvec4(0.0f, length, 0.0f, 0.0f);

			m_Triangles.push_back(std::make_shared<Triangle>(pos1, color));

			// 2
			glm::mat3x4 pos2 = {};
			pos2[0] = position + glm::fvec4(length, 0.0f, 0.0f, 0.0f);
			pos2[1] = position + glm::fvec4(length, length, 0.0f, 0.0f);
			pos2[0] = position + glm::fvec4(0.0f, length , 0.0f, 0.0f);

			m_Triangles.push_back(std::make_shared<Triangle>(pos2, color));
		}

		// Tył
		{

		}

		// Góra
		{

		}
		
		// Dół
		{

		}

		// Lewo
		{

		}

		// Prawo
		{

		}
	}

	void Cube::Draw(Renderer* renderer)
	{
		for (auto& t : m_Triangles)
			t->Draw(renderer);
	}

	Rectangle::Rectangle(const glm::mat3x4& left, const glm::mat3x4& right, const glm::fvec4& color)
		: m_LeftTriangle(left, color), m_RightTriangle(right, color)
	{

	}

	Rectangle::Rectangle(const glm::mat3x4& left, const glm::fvec4& color)
		: m_LeftTriangle(left, color)
	{
		glm::mat3x4 right = { };
		right[0] = left[1];
		right[1] = glm::fvec4(left[1].x, left[2].y, left[1].z, left[2].w);
		right[2] = left[2];

		m_RightTriangle = Triangle(right, color);
	}

	Rectangle::Rectangle(const Rectangle& other)
		: m_LeftTriangle(other.m_LeftTriangle), m_RightTriangle(other.m_RightTriangle)
	{
	}

	glm::fvec4 Rectangle::GetCenter() const
	{
		return (m_LeftTriangle.GetCenter() + m_RightTriangle.GetCenter()) / glm::fvec4(2.0f, 2.0f, 2.0f, 2.0f);
	}

	void Rectangle::Draw(Renderer* renderer)
	{
		m_LeftTriangle.Draw(renderer);
		m_RightTriangle.Draw(renderer);
	}

	void Rectangle::Rotate(float radians)
	{
		m_LeftTriangle.Rotate(radians);
		m_RightTriangle.Rotate(radians);
	}

}
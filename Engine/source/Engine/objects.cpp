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

	void Triangle::Move(glm::fvec3 offset)
	{

		glm::fvec4 offset4 = { offset.x,offset.y,offset.z,1.0f };
		glm::mat3x4 positions = m_VertexBuffer.GetPositions();

		for (std::uint32_t i = 0; i < 3; i++)
		{
			glm::fvec4 position = positions[i];

			float x = position.x + offset4.x;
			float y = position.y + offset4.y;
			float z = position.z + offset4.z;
			float w = position.w;

			glm::fvec4 newPosition(x, y, z, w);

			positions[i] = newPosition;
		}
		m_VertexBuffer.SetData(positions, m_VertexBuffer.GetColor(), m_VertexBuffer.GetTexCoords());
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
		glm::fvec4 color(0.0f, 1.0f, 0.0f, 1.0f);

		// ---------------------------------------------
		//		Przód
		// ---------------------------------------------
		glm::mat3x4 pos = {};
		pos[0] = position;
		pos[1] = position + glm::fvec4(length, 0.0f, 0.0f, 0.0f);
		pos[2] = position + glm::fvec4(0.0f, length, 0.0f, 0.0f);

		m_Rectangles.push_back(std::make_shared<Rectangle>(Rectangle(pos, color)));

		// ---------------------------------------------
		//		Tył
		// ---------------------------------------------
		pos[0] = position + glm::fvec4(0.0f, 0.0f, 0.0f, length);
		pos[1] = position + glm::fvec4(length, 0.0f, 0.0f, length);
		pos[2] = position + glm::fvec4(0.0f, length, 0.0f, length);

		//color = glm::fvec4(0.0f, 1.0f, 0.0f, 1.0f);
		m_Rectangles.push_back(std::make_shared<Rectangle>(Rectangle(pos, color)));

		// ---------------------------------------------
		//		Dół
		// ---------------------------------------------
		pos[0] = position;
		pos[1] = position + glm::fvec4(length, 0.0f, 0.0f, 0.0f);
		pos[2] = position + glm::fvec4(0.0f, 0.0f, 0.0f, length);

		//color = glm::fvec4(0.0f, 0.0f, 1.0f, 1.0f);
		m_Rectangles.push_back(std::make_shared<Rectangle>(Rectangle(pos, color)));

		// ---------------------------------------------
		//		Góra
		// ---------------------------------------------
		pos[0] = position + glm::fvec4(0.0f, length, 0.0f, 0.0f);
		pos[1] = position + glm::fvec4(length, length, 0.0f, 0.0f);
		pos[2] = position + glm::fvec4(0.0f, length, 0.0f, length);

		//color = glm::fvec4(0.0f, 1.0f, 1.0f, 1.0f);
		m_Rectangles.push_back(std::make_shared<Rectangle>(Rectangle(pos, color)));

		// ---------------------------------------------
		//		Lewo
		// ---------------------------------------------
		pos[0] = position;
		pos[1] = position + glm::fvec4(0.0f, 0.0f, 0.0f, length);
		pos[2] = position + glm::fvec4(0.0f, length, 0.0f, 0.0f);

		//color = glm::fvec4(0.0f, 1.0f, 1.0f, 1.0f);
		m_Rectangles.push_back(std::make_shared<Rectangle>(Rectangle(pos, color)));

		// ---------------------------------------------
		//		Prawo
		// ---------------------------------------------
		pos[0] = position + glm::fvec4(length, 0.0f, 0.0f, 0.0f);
		pos[1] = position + glm::fvec4(length, 0.0f, 0.0f, length);
		pos[2] = position + glm::fvec4(length, length, 0.0f, 0.0f);

		//color = glm::fvec4(1.0f, 0.0f, 1.0f, 1.0f);
		m_Rectangles.push_back(std::make_shared<Rectangle>(Rectangle(pos, color)));
	}

	void Cube::Draw(Renderer* renderer)
	{
		for (auto& r : m_Rectangles)
			r->Draw(renderer);
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

	Sphere::Sphere(const glm::vec4& position, float radius, const glm::fvec4& color)
		: m_Position(position), m_Radius(radius), m_Color(color)
	{
		CreateMesh();
	}

	void Sphere::Draw(Renderer* renderer)
	{
		for (auto& triangle : m_Triangles)
		{
			triangle->Draw(renderer);
		}
	}

	void Sphere::Rotate(float radians)
	{
		for (auto& triangle : m_Triangles)
		{
			triangle->Rotate(radians);
		}
	}

	void Sphere::CreateMesh()
	{
		const int numSegments = 32;
		const int numRings = 16;

		for (int ring = 0; ring < numRings; ++ring)
		{
			for (int segment = 0; segment < numSegments; ++segment)
			{
				float theta1 = static_cast<float>(ring) * glm::pi<float>() / numRings;
				float theta2 = static_cast<float>(ring + 1) * glm::pi<float>() / numRings;
				float phi1 = static_cast<float>(segment) * 2.0f * glm::pi<float>() / numSegments;
				float phi2 = static_cast<float>(segment + 1) * 2.0f * glm::pi<float>() / numSegments;

				glm::fvec4 p1 = GetPoint(theta1, phi1);
				glm::fvec4 p2 = GetPoint(theta1, phi2);
				glm::fvec4 p3 = GetPoint(theta2, phi2);
				glm::fvec4 p4 = GetPoint(theta2, phi1);

				m_Triangles.push_back(std::make_shared<Triangle>(glm::mat3x4{ p1, p2, p3 }, m_Color));
				m_Triangles.push_back(std::make_shared<Triangle>(glm::mat3x4{ p3, p4, p1 }, m_Color));
			}
		}
	}

	glm::fvec4 Sphere::GetPoint(float theta, float phi)
	{
		float x = m_Position.x + m_Radius * sin(theta) * cos(phi);
		float y = m_Position.y + m_Radius * sin(theta) * sin(phi);
		float z = m_Position.z + m_Radius * cos(theta);

		return glm::fvec4(x, y, z, 1.0f);
	}

	void Sphere::Move(glm::fvec3 offset)
	{
		glm::fvec4 offset4 = { offset.x,offset.y,offset.z,0.0f };
		m_Position = m_Position + offset4;

		for (auto& triangle : m_Triangles)
		{
			triangle->Move(offset);
		}
	}

	void Sphere::CircleAround(glm::fvec2 center, float radius, float angle)
	{
		float x = center.x + radius * std::cos(glm::radians(angle));
		float y = center.y + radius * std::sin(glm::radians(angle));

		glm::fvec4 pos4 = { x,y,m_Position.z,1.0f };
		glm::fvec4 offset = pos4 - m_Position;

		Move(offset);
	}

	glm::fvec4 Sphere::GetPosition()
	{
		return m_Position;
	}

	void BaseObject::SetHasTexture(bool has)
	{
		m_HasTexture = has;
	}

}
#include "buffers.h"

namespace eng::inter
{

	VertexBuffer::VertexBuffer(const glm::mat3x4& positions, const glm::fvec4& color)
		: BufferBase(BufferType::Vertex), m_Positions(positions), m_Color(color)
	{
		glGenBuffers(1, &m_Id);
		SetData(positions, color, {});

		// Pozycje
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, 0);
		glEnableVertexAttribArray(0);

		// Kolor
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, reinterpret_cast<void*>(sizeof(float) * 4));
		glEnableVertexAttribArray(1);

		// Tekstury
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 10, reinterpret_cast<void*>(sizeof(float) * 8));
		glEnableVertexAttribArray(2);
	}

	VertexBuffer::VertexBuffer(const glm::mat3x4& positions, const glm::fvec4& color, const glm::mat3x2& texCoords)
	{
		glGenBuffers(1, &m_Id);
		SetData(positions, color, texCoords);

		// Pozycje
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, 0);
		glEnableVertexAttribArray(0);

		// Kolor
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, reinterpret_cast<void*>(sizeof(float) * 4));
		glEnableVertexAttribArray(1);

		// Tekstury
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 10, reinterpret_cast<void*>(sizeof(float) * 8));
		glEnableVertexAttribArray(2);
	}

	VertexBuffer::VertexBuffer(const VertexBuffer& other)
		: BufferBase(BufferType::Vertex), m_Positions(other.m_Positions), m_Color(other.m_Color)
	{
		glGenBuffers(1, &m_Id);
		SetData(other.m_Positions, other.m_Color, other.m_TexCoords);

		// Pozycje
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, 0);
		glEnableVertexAttribArray(0);

		// Kolor
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 10, reinterpret_cast<void*>(sizeof(float) * 4));
		glEnableVertexAttribArray(1);

		// Tekstury
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 10, reinterpret_cast<void*>(sizeof(float) * 8));
		glEnableVertexAttribArray(2);
	}

	VertexBuffer::~VertexBuffer()
	{
		glBindBuffer(GL_VERTEX_ARRAY, m_Id);
		glDeleteBuffers(1, &m_Id);
	}

	void VertexBuffer::SetData(const glm::mat3x4& positions, const glm::fvec4& color, const glm::mat3x2& texCoords)
	{
		// Łączenie danych w jeden liniowy bufor.
		{
			std::uint32_t vertexDataCounter = 0;
			for (std::uint32_t i = 0; i < 3; i++)
			{
				for (std::uint32_t j = 0; j < 4; j++)
				{
					m_VertexData[vertexDataCounter] = positions[i][j];
					vertexDataCounter++;
				}

				m_VertexData[vertexDataCounter] = color.r;
				m_VertexData[vertexDataCounter + 1] = color.g;
				m_VertexData[vertexDataCounter + 2] = color.b;
				m_VertexData[vertexDataCounter + 3] = color.a;
				vertexDataCounter += 4;

				m_VertexData[vertexDataCounter] = texCoords[i][0];
				m_VertexData[vertexDataCounter + 1] = texCoords[i][1];
				vertexDataCounter += 2;
			}
		}

		m_Positions = positions;
		m_Color = color;

		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_VertexData.size(), &m_VertexData, GL_STATIC_DRAW);
	}

	void VertexBuffer::SetDataArray(const std::array<float, 3 * 4 + 4 * 3 + 3 * 2>& vertexData)
	{
		m_VertexData = vertexData;

		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_VertexData.size(), &m_VertexData, GL_STATIC_DRAW);
	}

	IndexBuffer::IndexBuffer(const glm::uvec4& indexes)
		: BufferBase(BufferType::Index), m_Indexes(indexes)
	{
		glGenBuffers(1, &m_Id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::uint32_t) * 4, &m_Indexes, GL_STATIC_DRAW);
	}

	IndexBuffer::IndexBuffer(const IndexBuffer& other)
		: BufferBase(BufferType::Index), m_Indexes(other.m_Indexes)
	{
		glGenBuffers(1, &m_Id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::uint32_t) * 4, &m_Indexes, GL_STATIC_DRAW);
	}

	// TODO: Oczyszczanie
	IndexBuffer::~IndexBuffer()
	{
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
		//glDeleteBuffers(1, &m_Id);
	}

	BufferBase::BufferBase(BufferType type)
		: m_Type(type)
	{
	}

	void BufferBase::Bind() const
	{
		glBindBuffer(static_cast<GLenum>(m_Type), m_Id);
	}

	void BufferBase::Unbind() const
	{
		glBindBuffer(static_cast<GLenum>(m_Type), 0);
	}

	VertexArray::VertexArray()
		: BufferBase(BufferType::VArray)
	{
		glGenVertexArrays(1, &m_Id);
		glBindVertexArray(m_Id);
	}

	VertexArray::VertexArray(const VertexArray& other)
	{
		glGenVertexArrays(1, &m_Id);
		glBindVertexArray(m_Id);
	}

	VertexArray::~VertexArray()
	{
		//glDeleteVertexArrays(1, &m_Id);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_Id);
	}

}

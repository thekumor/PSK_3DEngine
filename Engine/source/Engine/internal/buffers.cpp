#include "buffers.h"

namespace eng::inter
{

	VertexBuffer::VertexBuffer(const glm::mat3x2& vertices, const glm::fvec4& color)
		: BufferBase(BufferType::Vertex), m_Vertices(vertices), m_Color(color)
	{
		// Łączenie danych w jeden liniowy bufor.
		{
			std::uint32_t vertexDataCounter = 0;
			for (std::uint32_t i = 0; i < 3; i++)
			{
				for (std::uint32_t j = 0; j < 2; j++)
				{
					m_VertexData[vertexDataCounter] = vertices[i][j];
					vertexDataCounter++;
				}

				m_VertexData[vertexDataCounter] = color.r;
				m_VertexData[vertexDataCounter + 1] = color.g;
				m_VertexData[vertexDataCounter + 2] = color.b;
				m_VertexData[vertexDataCounter + 3] = color.a;
				vertexDataCounter += 4;
			}
		}

		glGenBuffers(1, &m_Id);
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, &m_VertexData, GL_STATIC_DRAW);

		// Werteksy
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
		glEnableVertexAttribArray(0);

		// Kolor
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 6, reinterpret_cast<void*>(sizeof(float) * 2));
		glEnableVertexAttribArray(1);
	}

	VertexBuffer::~VertexBuffer()
	{
	}

	IndexBuffer::IndexBuffer(const glm::uvec4& indexes)
		: BufferBase(BufferType::Index), m_Indexes(indexes)
	{
		glGenBuffers(1, &m_Id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::uint32_t) * 4, &indexes, GL_STATIC_DRAW);
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

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_Id);
	}

}

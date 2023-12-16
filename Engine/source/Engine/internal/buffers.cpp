#include "buffers.h"

namespace eng::inter
{
	
	VertexBuffer::VertexBuffer(const glm::mat2x3& vertices)
		: BufferBase(BufferType::Vertex), m_Vertices(vertices)
	{
		glGenBuffers(1, &m_Id);
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 3, &vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
		glEnableVertexAttribArray(0);
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

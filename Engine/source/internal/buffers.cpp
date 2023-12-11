#include "buffers.h"

namespace eng::inter
{
	
	VertexBuffer::VertexBuffer(const glm::mat2x3& vertices)
		: BufferBase(GL_ARRAY_BUFFER), m_Vertices(vertices)
	{
		glGenBuffers(1, &m_Id);
		glBindBuffer(GL_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
	}

	IndexBuffer::IndexBuffer(const glm::uvec4& indexes)
		: BufferBase(GL_ELEMENT_ARRAY_BUFFER), m_Indexes(indexes)
	{
		glGenBuffers(1, &m_Id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), &indexes, GL_STATIC_DRAW);
	}

	BufferBase::BufferBase(GLenum type)
		: m_Type(type)
	{
	}

	void BufferBase::Bind() const
	{
		glBindBuffer(m_Type, m_Id);
	}

}

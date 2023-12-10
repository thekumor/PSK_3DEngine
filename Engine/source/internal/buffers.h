#pragma once

#include <glad/glad.h>

namespace eng::inter
{

	class BufferBase
	{
	public:
		BufferBase() = default;
		virtual ~BufferBase() {};
	};

	class VertexBuffer : public BufferBase
	{
	public:
		VertexBuffer() = default;
		~VertexBuffer();
	};

}
#pragma once

#include <glad/glad.h>
#include <cstdint>
#include <glm/glm.hpp>
#include "../BaseClass.h"

namespace eng::inter // engine::internal
{

	// Klasa bazowa dla buforów OpenGL.
	class BufferBase : public BaseClass
	{
	public:
		BufferBase(GLenum type);
		BufferBase() = default;
		virtual ~BufferBase() {};

		// Zwraca typ bufora.
		inline GLenum GetType() const { return m_Type; }

		// Zwraca identyfikator bufora.
		inline std::uint32_t GetId() const { return m_Id; }

		void Bind() const;

	protected:
		// Typ bufora, np. bufor werteksów, indeksów.
		GLenum m_Type = 0;

		// Identyfikator bufora.
		std::uint32_t m_Id = 0;
	};

	// Bufor werteksów.
	class VertexBuffer : public BufferBase
	{
	public:
		VertexBuffer(const glm::mat2x3& vertices);
		VertexBuffer() = default;
		~VertexBuffer();

		// Zwraca werteksy bufora.
		inline const glm::mat2x3& GetVertices() const { return m_Vertices; }

	private:
		// Werteksy bufora.
		glm::mat2x3 m_Vertices = {};
	};

	// Bufor indeksów.
	class IndexBuffer : public BufferBase
	{
	public:
		IndexBuffer(const glm::uvec4& indexes);
		IndexBuffer() = default;

		// Zwraca indeksy bufora.
		inline const glm::uvec4& GetIndexes() const { return m_Indexes; }

	private:
		// Indeksy bufora.
		glm::uvec4 m_Indexes = {};
	};

}
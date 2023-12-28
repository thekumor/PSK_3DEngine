﻿#pragma once

#include <cstdint>
#include <array>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <Engine/BaseClass.h>

namespace eng::inter // engine::internal
{

	enum class BufferType : std::uint32_t
	{
		Invalid = 0,
		Vertex = GL_ARRAY_BUFFER,
		Index = GL_ELEMENT_ARRAY_BUFFER,
		VArray = GL_VERTEX_ARRAY
	};

	// Klasa bazowa dla buforów OpenGL.
	class BufferBase : public BaseClass
	{
	public:
		BufferBase(BufferType type);
		BufferBase() = default;
		virtual ~BufferBase() {};

		// Zwraca typ bufora.
		inline BufferType GetType() const { return m_Type; }

		// Zwraca identyfikator bufora.
		inline std::uint32_t GetId() const { return m_Id; }

		// Używa bufora.
		void Bind() const;

		// Przestaje używać bufora.
		void Unbind() const;

	protected:
		// Typ bufora, np. bufor werteksów, indeksów.
		BufferType m_Type = BufferType::Invalid;

		// Identyfikator bufora.
		std::uint32_t m_Id = 0;
	};

	// Bufor werteksów.
	class VertexBuffer : public BufferBase
	{
	public:
		VertexBuffer(const glm::mat3x2& vertices, const glm::fvec4& color);
		VertexBuffer() = default;
		~VertexBuffer();

		// Zwraca werteksy bufora.
		inline const glm::mat2x3& GetVertices() const { return m_Vertices; }

	private:
		// Werteksy bufora.
		glm::mat3x2 m_Vertices = {};

		// Kolor bufora.
		glm::fvec4 m_Color = {};

		// Dane dla bufora w OpenGL.
		std::array<float, 18> m_VertexData = {};
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

	// Tablica werteksów.
	class VertexArray : public BufferBase
	{
	public:
		VertexArray();

		// Używa tablicy.
		void Bind() const;

		// Przestaje używać tablicy.
		void Unbind() const;
	};

}
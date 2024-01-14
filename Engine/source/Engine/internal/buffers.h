#pragma once

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
		VertexBuffer(const VertexBuffer& other);
		VertexBuffer() = default;
		~VertexBuffer();

		// Zwraca pozycje bufora.
		inline const glm::mat3x2& GetPositions() const { return m_Positions; }

		// Zwraca kolor bufora.
		inline const glm::fvec4& GetColor() const { return m_Color; }

		// Zwraca dane bufora ułożone liniowo.
		inline const std::array<float, 18> GetData() const { return m_VertexData; }

		// Ustawia dane bufora.
		void SetData(const glm::mat3x2& positions, const glm::fvec4& color);

		// Ustawia dane bufora ułożone liniowo.
		void SetDataArray(const std::array<float, 18>& vertexData);

	private:
		// Pozycje bufora.
		glm::mat3x2 m_Positions = {};

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
		IndexBuffer(const IndexBuffer& other);
		IndexBuffer() = default;
		~IndexBuffer();

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
		VertexArray(const VertexArray& other);
		~VertexArray();

		// Używa tablicy.
		void Bind() const;

		// Przestaje używać tablicy.
		void Unbind() const;
	};

}
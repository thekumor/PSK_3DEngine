#pragma once

#include <cstdint>
#include <array>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <Engine/BaseClass.h>

namespace eng::inter // engine::internal
{

	/// <summary>
	/// Typ bufora.
	/// </summary>
	enum class BufferType : std::uint32_t
	{
		Invalid = 0,
		Vertex = GL_ARRAY_BUFFER,
		Index = GL_ELEMENT_ARRAY_BUFFER,
		VArray = GL_VERTEX_ARRAY
	};

	/// <summary>
	/// Bazowa klasa dla buforów.
	/// </summary>
	class BufferBase : public BaseClass
	{
	public:
		BufferBase(BufferType type);
		BufferBase() = default;
		virtual ~BufferBase() {};

		/// <summary>
		/// Zwraca typ bufora.
		/// </summary>
		/// <returns>Typ bufora.</returns>
		inline BufferType GetType() const { return m_Type; }

		/// <summary>
		/// Zwraca identyfikator bufora.
		/// </summary>
		/// <returns>Identyfikator bufora.</returns>
		inline std::uint32_t GetId() const { return m_Id; }

		/// <summary>
		/// Przywiązuje ten bufor.
		/// </summary>
		void Bind() const;

		/// <summary>
		/// Odwiązuje ten bufor.
		/// </summary>
		void Unbind() const;

	protected:
		/// <summary>
		/// Rodzaj bufora.
		/// </summary>
		BufferType m_Type = BufferType::Invalid;

		/// <summary>
		/// Unikatowy identyfikator bufora.
		/// </summary>
		std::uint32_t m_Id = 0;
	};

	/// <summary>
	/// Bufor werteksów.
	/// </summary>
	class VertexBuffer : public BufferBase
	{
	public:
		VertexBuffer(const glm::mat3x4& positions, const glm::fvec4& color);
		VertexBuffer(const glm::mat3x4& positions, const glm::fvec4& color, const glm::mat3x2& texCoords);
		VertexBuffer(const VertexBuffer& other);
		VertexBuffer() = default;
		~VertexBuffer();

		/// <summary>
		/// Zwraca pozycje werteksów.
		/// </summary>
		/// <returns>Pozycje werteksów</returns>
		inline const glm::mat3x4& GetPositions() const { return m_Positions; }

		/// <summary>
		/// Zwraca kolor bufora.
		/// </summary>
		/// <returns>Kolor bufora</returns>
		inline const glm::fvec4& GetColor() const { return m_Color; }

		/// <summary>
		/// Zwraca pozycje tekstury.
		/// </summary>
		/// <returns>Pozycje tekstury</returns>
		inline const glm::mat3x2& GetTexCoords() const { return m_TexCoords; }

		/// <summary>
		/// Zwraca dane bufora.
		/// </summary>
		/// <returns>Dane bufora.</returns>
		inline const std::array<float, 3 * 4 + 3 * 4 + 3 * 2> GetData() const { return m_VertexData; }

		/// <summary>
		/// Ustawia dane dla bufora.
		/// </summary>
		/// <param name="positions">Pozycje werteksów</param>
		/// <param name="color">Kolory werteksów</param>
		void SetData(const glm::mat3x4& positions, const glm::fvec4& color, const glm::mat3x2& texCoords);

		/// <summary>
		/// Ustawia dane dla bufora.
		/// </summary>
		/// <param name="vertexData">Dane bufora</param>
		void SetDataArray(const std::array<float, 3 * 4 + 3 * 4 + 3 * 2>& vertexData);

	private:
		/// <summary>
		/// Pozycje werteksów.
		/// </summary>
		glm::mat3x4 m_Positions = {};

		/// <summary>
		/// Kolor werteksów.
		/// </summary>
		glm::fvec4 m_Color = {};

		/// <summary>
		/// Pozycje tekstury.
		/// </summary>
		glm::mat3x2 m_TexCoords = {};

		/// <summary>
		/// Dane bufora.
		/// </summary>
		std::array<float, 3 * 4 + 3 * 4 + 3 * 2> m_VertexData = {};
	};

	/// <summary>
	/// Bufor indeksów.
	/// </summary>
	class IndexBuffer : public BufferBase
	{
	public:
		IndexBuffer(const glm::uvec4& indexes);
		IndexBuffer(const IndexBuffer& other);
		IndexBuffer() = default;
		~IndexBuffer();

		/// <summary>
		/// Zwraca indeksy bufora.
		/// </summary>
		/// <returns>Indeksy bufora.</returns>
		inline const glm::uvec4& GetIndexes() const { return m_Indexes; }

	private:
		/// <summary>
		/// Indeksy bufora.
		/// </summary>
		glm::uvec4 m_Indexes = {};
	};

	/// <summary>
	/// Tablica werteksów.
	/// </summary>
	class VertexArray : public BufferBase
	{
	public:
		VertexArray();
		VertexArray(const VertexArray& other);
		~VertexArray();

		/// <summary>
		/// Przywiązuje tablicę.
		/// </summary>
		void Bind() const;

		/// <summary>
		/// Odwiązuje tablicę.
		/// </summary>
		void Unbind() const;
	};

}
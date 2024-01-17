#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include <Engine/internal/buffers.h>
#include <Engine/Renderer.h>
#include <Engine/events.h>

namespace eng
{

	/// <summary>
	/// Klasa bazowa obiektów.
	/// </summary>
	class BaseObject
	{
	public:
		BaseObject() = default;

		/// <summary>
		/// Zwraca odbiornik zdarzeń.
		/// </summary>
		/// <returns>Odbiornik zdarzeń</returns>
		EventReceiver& GetReceiver() { return m_Receiver; }

	private:
		/// <summary>
		/// Odbiornik zdarzeń.
		/// </summary>
		EventReceiver m_Receiver;
	};

	/// <summary>
	/// Trójkąt, z którego można składać prymitywy.
	/// </summary>
	class Triangle : public BaseObject
	{
	public:
		Triangle(const glm::mat3x2& vertices, const glm::fvec4& color);
		Triangle(const Triangle& other);
		Triangle() = default;

		/// <summary>
		/// Zwraca bufor werteksów.
		/// </summary>
		/// <returns>Bufor werteksów</returns>
		inline const inter::VertexBuffer& GetVertexBuffer() const { return m_VertexBuffer; }

		/// <summary>
		/// Wylicza środek trójkąta.
		/// </summary>
		/// <returns>Środek trójkąta, punkt</returns>
		glm::fvec2 GetCenter() const;

		/// <summary>
		/// Rysuje ten trójkąt.
		/// </summary>
		/// <param name="renderer">Renderer który ma go narysować</param>
		void Draw(Renderer* renderer);

		/// <summary>
		/// Rotuje ten trójkąt.
		/// </summary>
		/// <param name="radians">Radiany</param>
		void Rotate(float radians);

	private:
		/// <summary>
		/// Tablica werteksów.
		/// </summary>
		inter::VertexArray m_VertexArray;

		/// <summary>
		/// Bufor indeksów.
		/// </summary>
		inter::IndexBuffer m_IndexBuffer;

		/// <summary>
		/// Bufor werteksów.
		/// </summary>
		inter::VertexBuffer m_VertexBuffer;
	};

}
#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include <Engine/internal/buffers.h>
#include <Engine/Renderer.h>
#include <Engine/events.h>

namespace eng
{

	// Klasa bazowa obiektu.
	class BaseObject
	{
	public:
		BaseObject() = default;

		// Odbiornik zdarzeń.
		EventReceiver& GetReceiver() { return m_Receiver; }

	private:
		EventReceiver m_Receiver;
	};

	// Trójkąt.
	class Triangle : public BaseObject
	{
	public:
		Triangle(const glm::mat3x2& vertices, const glm::fvec4& color);
		Triangle() = default;

		// Zwraca bufor werteksów trójkąta.
		inline const inter::VertexBuffer& GetVertexBuffer() const { return m_VertexBuffer; }

		// Wylicza środek.
		glm::fvec2 GetCenter() const;

		// Rysuje trójkąt.
		void Draw(Renderer* renderer);

		// Ustawia nową pozycję trójkąta.
		void SetPosition(const glm::mat3x2& vertices);

		// Ustawia nową rotację trójkąta.
		void SetRotation(float angle);

	private:
		// Tablica werteksów.
		inter::VertexArray m_VertexArray;

		// Bufor indeksów.
		inter::IndexBuffer m_IndexBuffer;

		// Bufor werteksów.
		inter::VertexBuffer m_VertexBuffer;
	};

}
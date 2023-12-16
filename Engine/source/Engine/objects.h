#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include <Engine/internal/buffers.h>
#include <Engine/Renderer.h>

namespace eng
{

	// Klasa bazowa obiektu.
	class BaseObject
	{
	public:
		BaseObject() = default;
	};

	// Trójkąt.
	class Triangle : public BaseObject
	{
	public:
		Triangle(const glm::mat2x3& vertices, const glm::vec4& color);
		Triangle() = default;

		// Zwraca bufor werteksów trójkąta.
		inline const inter::VertexBuffer& GetVertexBuffer() const { return m_VertexBuffer; }

		// Rysuje trójkąt.
		void Draw(Renderer* renderer);

	private:
		// Tablica werteksów.
		inter::VertexArray m_VertexArray;

		// Bufor indeksów.
		inter::IndexBuffer m_IndexBuffer;

		// Bufor werteksów.
		inter::VertexBuffer m_VertexBuffer;

		// Kolor trójkąta.
		glm::vec4 m_Color = {};
	};

}
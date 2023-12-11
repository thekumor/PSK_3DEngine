#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include "internal/buffers.h"

namespace eng
{

	// Klasa bazowa obiektu.
	class BaseObject
	{
	public:
		BaseObject() = default;
	};

	// Trójk¹t.
	class Triangle : public BaseObject
	{
	public:
		Triangle(const glm::mat2x3& vertices, const glm::vec4& color);
		Triangle() = default;

		// Zwraca bufor werteksów trójk¹ta.
		const inter::VertexBuffer& GetVertexBuffer() const { return m_VertexBuffer; }

	private:
		// Bufor werteksów trójk¹ta.
		inter::VertexBuffer m_VertexBuffer;

		// Kolor trójk¹ta.
		glm::vec4 m_Color = {};
	};

}
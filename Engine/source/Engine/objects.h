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

	// Tr�jk�t.
	class Triangle : public BaseObject
	{
	public:
		Triangle(const glm::mat2x3& vertices, const glm::vec4& color);
		Triangle() = default;

		// Zwraca bufor werteks�w tr�jk�ta.
		inline const inter::VertexBuffer& GetVertexBuffer() const { return m_VertexBuffer; }

		void Draw(Renderer* renderer);

	private:
		// Bufor werteks�w tr�jk�ta.
		inter::VertexBuffer m_VertexBuffer;

		// Kolor tr�jk�ta.
		glm::vec4 m_Color = {};
	};

}
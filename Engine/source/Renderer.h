#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace eng
{

	// Używane do wyświetlania obiektów. Singleton.
	class Renderer
	{
	public:
		Renderer(const Renderer&) = delete;
		Renderer& operator=(Renderer&) = delete;

		// Zwraca instancję klasy.
		static Renderer* Get();
		
		// Czyści ekran.
		void Clear(const glm::fvec4& color);

		// Rysuje trójkąt.
		void DrawTriangle(const glm::mat3x2& vertices, const glm::fvec4& color);
	private:
		Renderer() = default;
	};

}
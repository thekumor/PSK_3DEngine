#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "internal/buffers.h"
#include "BaseClass.h"

namespace eng
{

	// Używane do wyświetlania obiektów. Singleton.
	class Renderer : public BaseClass
	{
	public:
		Renderer(const Renderer&) = delete;
		Renderer& operator=(Renderer&) = delete;

		// Zwraca instancję klasy.
		static Renderer* Get();
		
		// Czyści ekran.
		void Clear(const glm::fvec4& color);

		// Rysuje z bufora.
		void Draw(const inter::VertexBuffer& buf, const glm::vec4& color);
	private:
		Renderer() = default;
	};

}
#pragma once

#include <glm/glm.hpp>
#include <glfw/glfw3.h>

namespace eng
{

	// Used to render objects. Singleton.
	class Renderer
	{
	public:
		Renderer(const Renderer&) = delete;
		Renderer& operator=(Renderer&) = delete;

		// Gets the singleton instance.
		static Renderer* Get();

		// Clears the screen.
		void Clear(const glm::fvec4& color);

		// Draws a triangle.
		// TODO: Use color.
		void DrawTriangle(const glm::mat3x2& vertices, const glm::fvec4& color);
	private:
		Renderer() = default;
	};

}
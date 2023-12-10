#include "Renderer.h"

namespace eng
{

	Renderer* Renderer::Get()
	{
		static Renderer* instance = new Renderer();
		return instance;
	}

	void Renderer::Clear(const glm::fvec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::DrawTriangle(const glm::mat3x2& vertices, const glm::fvec4& color)
	{
	}

}
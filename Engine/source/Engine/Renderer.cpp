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

	void Renderer::Draw(const inter::VertexBuffer& buf, const glm::vec4& color)
	{
		glBindBuffer(GL_ARRAY_BUFFER, buf.GetId());
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

}
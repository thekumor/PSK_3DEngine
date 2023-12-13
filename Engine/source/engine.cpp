#include "engine.h"

namespace eng
{

	Engine::Engine(std::uint32_t width, std::uint32_t height, const std::string& title)
	{
		if (!glfwInit())
			std::cerr << "Failed to initialize GLFW" << std::endl;
		else
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			m_Window = Window(width, height, title);

			if (m_Window.IsValid())
			{
				m_Window.SetCurrent();

				if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
					std::cerr << "Failed to initialize GLAD" << std::endl;
			}
		}
	}

	Engine::~Engine()
	{
		glfwTerminate();
	}

	void Engine::Run()
	{
		std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;

		Renderer* renderer = Renderer::Get();

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(float) * 3, nullptr);

		glm::mat2x3 vertices = {
			-0.5f, -0.5f,
			0.0f, 0.5f,
			0.5f, -0.5f
		};

		Triangle triangle(vertices, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

		while (!m_Window.ShouldClose())
		{
			m_Window.HandleEvents();
			renderer->Clear(ENG_CLEAR_COLOR);
			triangle.Draw(renderer);
			m_Window.SwapBuffers();
		}
	}

}
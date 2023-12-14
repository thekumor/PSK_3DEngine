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
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

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

		glm::mat2x3 vertices = {
			-0.5f, -0.5f,
			0.0f, 0.5f,
			0.5f, -0.5f
		};

		glm::mat2x3 vertices1 = {
			-0.9f, -0.9f,
			-0.8f, -0.7f,
			-0.7f, -0.9f
		};

		Triangle triangle(vertices, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		Triangle triangle1(vertices1, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

		Program program("shaders/test");
		program.Bind();

		while (!m_Window.ShouldClose())
		{
			m_Window.HandleEvents();
			renderer->Clear(ENG_CLEAR_COLOR);
			triangle.Draw(renderer);
			triangle1.Draw(renderer);
			m_Window.SwapBuffers();
		}
	}

}
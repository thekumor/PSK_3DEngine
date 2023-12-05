#include "engine.h"

namespace eng
{

	Engine::Engine(std::uint32_t width, std::uint32_t height, const std::string& title)
	{
		if (!glfwInit())
			std::cerr << "Failed to initialize GLFW" << std::endl;
		else
		{
			m_Window = Window(width, height, title);

			if (m_Window.IsValid())
				m_Window.SetCurrent();
			else
				glfwTerminate();
		}
	}

	void Engine::Run()
	{
		std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;

		Renderer* renderer = Renderer::Get();

		while (!m_Window.ShouldClose())
		{
			m_Window.HandleEvents();
			m_Window.SwapBuffers();
		}
	}

}
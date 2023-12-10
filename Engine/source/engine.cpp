﻿#include "engine.h"

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

		glm::mat3x2 vertices = {
			-0.5f, -0.5f,
			0.0f, 0.5f,
			0.5f, -0.5f
		};

		// We are just drawing a triangle :)
		while (!m_Window.ShouldClose())
		{
			m_Window.HandleEvents();
			renderer->Clear(ENG_CLEAR_COLOR);
			renderer->DrawTriangle(vertices, glm::fvec4(0.2f, 0.2f, 0.5f, 1.0f));
			m_Window.SwapBuffers();
		}
	}

}
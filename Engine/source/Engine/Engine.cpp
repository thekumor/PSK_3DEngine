#include "engine.h"

namespace eng
{

	Engine::Engine(std::uint32_t width, std::uint32_t height, const std::string& title)
	{
		if (!glfwInit())
			std::cerr << "Failed to initialize GLFW" << std::endl;
		else
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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
		// Debugowanie
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);

		std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;

		Renderer* renderer = Renderer::Get();

		glm::mat3x2 vertices = {
			-0.5f, -0.5f,
			0.0f, 0.5f,
			0.5f, -0.5f
		};
		glm::fvec4 color = {
			1.0f, 0.0f, 0.0f, 1.0f
		};

		glm::mat3x2 vertices1 = {
			-0.9f, -0.9f,
			-0.8f, -0.7f,
			-0.7f, -0.9f
		};
		glm::fvec4 color1 = {
			0.0f, 1.0f, 0.0f, 1.0f
		};

		Program program("shaders/test");
		Uniform brightness("uBrightness", program);
		brightness.SetFloat(1.0f);
		program.Bind();

		Triangle triangle(vertices, color);
		Triangle triangle1(vertices1, color1);

		float time = 1.0f;
		float factor = -0.007f;
		while (!m_Window.ShouldClose())
		{
			time += factor;
			if (time > 1.0f)
			{
				factor = -factor;
				time = 1.0f;
			}
			else if (time < 0.0f)
			{
				factor = -factor;
				time = 0.0f;
			}
			brightness.SetFloat(1.0f * time);

			m_Window.HandleEvents();
			renderer->Clear(ENG_CLEAR_COLOR);
			triangle.Draw(renderer);
			triangle1.Draw(renderer);
			m_Window.SwapBuffers();
		}
	}

}
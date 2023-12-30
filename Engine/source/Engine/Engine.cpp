#include "engine.h"

namespace eng
{

	Engine::Engine(std::uint32_t width, std::uint32_t height, const std::string& title)
		: m_Camera(glm::fvec3(0.0f, 0.0f, 0.0f), glm::fvec3(0.0f, 0.0f, 0.0f))
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

		// Obiekty
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
		Triangle triangle(vertices, color);
		Triangle triangle1(vertices1, color1);

		g_EventSource.AddReceiver(&triangle.GetReceiver());
		triangle.GetReceiver().AddHook(EventType::KeyPress, Hook(
			"Nothing", [&](const EventData& data)
			{
				std::cout << "Hello, I receive: " << std::any_cast<std::int32_t>(data.Data) << std::endl;
			}
		));

		// Shadery, uniformy.
		Program program("shaders/test");
		Uniform brightness("uBrightness", program);
		const float brightnessValue = 0.5f;
		brightness.SetFloat(brightnessValue);
		Uniform camera("uCamera", program);
		program.Bind();

		// Pętla główna.
		while (!m_Window.ShouldClose())
		{
			// Logika
			m_Window.HandleEvents();
			const glm::fvec3& camPos = m_Camera.GetPosition();
			camera.SetVec4f(glm::fvec4(camPos.x, camPos.y, camPos.z, 0.0));

			// Rysowanie
			renderer->Clear(ENG_CLEAR_COLOR * brightnessValue);
			triangle.Draw(renderer);
			triangle1.Draw(renderer);
			m_Window.SwapBuffers();
		}
	}

}
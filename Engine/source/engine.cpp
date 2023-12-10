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

				if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
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

		// --------------------------------------
		// Event Test
		// --------------------------------------
		EventReceiver r;
		r.AddHook(EventType::Update, Hook("Test", [&](const EventData& data)
			{
				std::int32_t val = std::any_cast<std::int32_t>(data.Data);
				std::cout << "Lambda! Value: " << val << std::endl;
			}));

		m_EventSource.AddReceiver(r);
		m_EventSource.CallEvent(EventType::Update, EventData(65));
		// --------------------------------------

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
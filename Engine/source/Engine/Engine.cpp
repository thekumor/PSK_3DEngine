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
		std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;

		Renderer* renderer = Renderer::Get();

		// ---------------------------------------------
		//		Domyślne shadery.
		// ---------------------------------------------
		Program program("shaders/test");
		Uniform brightness("uBrightness", program);
		const float brightnessValue = 0.9f;
		brightness.SetFloat(brightnessValue);
		Uniform cameraPos("uCameraPos", program);
		Uniform cameraRot("uCameraRotation", program);
		program.Bind();

		// Pętla główna.
		while (!m_Window.ShouldClose())
		{
			// ---------------------------------------------
			//		Logika
			// ---------------------------------------------
			m_Window.HandleEvents();
			const glm::fvec3& camPosVec = m_Camera.GetPosition();
			const glm::fvec3& camRotVec = m_Camera.GetRotation();
			cameraPos.SetVec4f(glm::fvec4(camPosVec.x, camPosVec.y, 0.0f, camPosVec.z));
			cameraRot.SetVec4f(glm::fvec4(camRotVec.x, camRotVec.y, 0.0f, camRotVec.z));

			// ---------------------------------------------
			//		Rysowanie
			// ---------------------------------------------
			renderer->Clear(ENG_CLEAR_COLOR * brightnessValue);

			for (auto& t : m_Triangles)
				(*t)->Draw(renderer);

			m_Window.SwapBuffers();
		}
	}

	std::shared_ptr<Triangle*> Engine::CreateTriangle(Triangle* object)
	{
		std::shared_ptr<Triangle*> pointer = std::make_shared<Triangle*>(object);
		m_Triangles.emplace_back(pointer);

		return pointer;
	}

}
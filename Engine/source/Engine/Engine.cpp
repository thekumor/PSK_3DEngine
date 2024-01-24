#include "engine.h"

namespace eng
{

	Engine::Engine(std::uint32_t width, std::uint32_t height, const std::string& title)
		: m_Camera(glm::fvec3(0.0f, 0.0f, 0.0f), 0.0f)
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

	std::shared_ptr<Scene> Engine::CreateScene()
	{
		return m_Scenes.emplace_back(std::make_shared<Scene>(Scene()));
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
		const float brightnessValue = 1.0f;
		brightness.SetFloat(brightnessValue);
		Uniform cameraPos("uCameraPos", program);
		Uniform cameraRot("uCameraRotRadians", program);
		program.Bind();

		double time = 0;
		std::uint64_t timeStamp = 0;

		// Pętla główna.
		while (!m_Window.ShouldClose())
		{
			// ---------------------------------------------
			//		Logika
			// ---------------------------------------------
			m_Window.HandleEvents();
			const glm::fvec3& camPosVec = m_Camera.GetPosition();
			float camRot = m_Camera.GetRotation();
			cameraPos.SetVec4f(glm::fvec4(camPosVec.x, camPosVec.y, 0.0f, camPosVec.z));
			cameraRot.SetFloat(camRot);

			double frameTime = 1.0 / m_Fps;

			if (glfwGetTime() > time + frameTime)
				time = glfwGetTime();
			else
				continue;

			eng::EventData updateData(timeStamp);
			g_EventSource.CallEvent(EventType::Update, updateData);

			timeStamp++;

			// ---------------------------------------------
			//		Rysowanie
			// ---------------------------------------------
			renderer->Clear(ENG_CLEAR_COLOR * brightnessValue);

			for (auto& scene : m_Scenes)
			{
				for (auto& t : scene->m_Triangles)
					t->Draw(renderer);
			}

			m_Window.SwapBuffers();
		}
	}

	void Engine::SetFPS(std::uint32_t fps)
	{
		std::cout << "FPS set to: " << fps << std::endl;
		m_Fps = fps;
	}

	std::shared_ptr<Triangle> Scene::CreateTriangle(Triangle object)
	{
		std::shared_ptr<Triangle> pointer = std::make_shared<Triangle>(object);
		m_Triangles.emplace_back(pointer);

		return pointer;
	}

}
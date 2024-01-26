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
		float brightnessValue = 1.0f;
		//brightness.SetFloat(brightnessValue);
		Uniform cameraPos("uCameraPos", program);
		Uniform cameraRot("uCameraRotRadians", program);
		Uniform cameraRot4("uCameraRotRadians4", program);
		Uniform hasTexture("uHasTexture", program);
		program.Bind();

		double time = 0;
		std::uint64_t timeStamp = 0;

		std::shared_ptr<Scene> scene = CreateScene();

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
			cameraRot4.SetVec4f(m_Camera.GetRotation4());
			cameraRot.SetFloat(camRot);
			
			if (glfwGetKey(m_Window.GetWindow(), GLFW_KEY_P) == GLFW_PRESS) {
				brightnessValue = 1.0f;
				brightness.SetFloat(brightnessValue);
			}
			else if (glfwGetKey(m_Window.GetWindow(), GLFW_KEY_O) == GLFW_PRESS) {
				brightnessValue = 0.5f;
				brightness.SetFloat(brightnessValue);
			}
			else if (glfwGetKey(m_Window.GetWindow(), GLFW_KEY_I) == GLFW_PRESS) {
				brightnessValue = 0.0f;
				brightness.SetFloat(brightnessValue);
			}

			double frameTime = 1.0 / m_Fps;

			if (glfwGetTime() > time + frameTime)
			{
				time = glfwGetTime();
				// ---------------------------------------------
				//		FPS
				// ---------------------------------------------

			}
			else
				continue;

			eng::EventData updateData(timeStamp);
			g_EventSource.CallEvent(EventType::Update, updateData);


				m_LightingEnabled = !m_LightingEnabled;


			timeStamp++;

			// ---------------------------------------------
			//		Rysowanie
			// ---------------------------------------------
			renderer->Clear(ENG_CLEAR_COLOR * 1.0f);

			for (auto& scene : m_Scenes)
			{
				for (auto& t : scene->m_Triangles)
				{
					hasTexture.SetInt(t->HasTexture());
					t->Draw(renderer);
				}

				for (auto& r : scene->m_Rectangles)
				{
					hasTexture.SetInt(r->HasTexture());
					r->Draw(renderer);
				}

				for (auto& c : scene->m_Cubes)
				{
					hasTexture.SetInt(c->HasTexture());
					c->Draw(renderer);
				}

				for (auto& s : scene->m_Spheres)
				{
					hasTexture.SetInt(s->HasTexture());
					s->Draw(renderer);
				}
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

	std::shared_ptr<Rectangle> Scene::CreateRectangle(Rectangle object)
	{
		std::shared_ptr<Rectangle> pointer = std::make_shared<Rectangle>(object);
		m_Rectangles.emplace_back(pointer);

		return pointer;
	}

	std::shared_ptr<Cube> Scene::CreateCube(Cube object)
	{
		std::shared_ptr<Cube> pointer = std::make_shared<Cube>(object);
		m_Cubes.emplace_back(pointer);

		return pointer;
	}

	std::shared_ptr<Sphere> Scene::CreateSphere(Sphere object)
	{
		std::shared_ptr<Sphere> pointer = std::make_shared<Sphere>(object);
		m_Spheres.emplace_back(pointer);

		return pointer;
	}

}
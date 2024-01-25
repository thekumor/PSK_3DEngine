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
		Uniform cameraRot4("uCameraRotRadians4", program);
		program.Bind();

		double time = 0;
		std::uint64_t timeStamp = 0;

		std::shared_ptr<Scene> scene = CreateScene();


		// ------ MODEL ATOMU ------
		float kat = 0.0f;
		float kat2 = 25.0f;
		float kat3 = 50.0f;
		float zmianaNaFps = 1.0f;
		float zmianaNaFps2 = 2.0f;
		float zmianaNaFps3 = 3.5f;
		float maxKat = 360.0f;
		Sphere sphere(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 0.05f, glm::fvec4(1.0f, 0.0f, 0.0f, 1.0f));
		std::shared_ptr<Sphere> r3 = scene->CreateSphere(sphere);

		Sphere sphere2(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 0.05f, glm::fvec4(1.0f, 0.0f, 0.0f, 1.0f));
		std::shared_ptr<Sphere> r5 = scene->CreateSphere(sphere2);

		Sphere sphere3(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 0.05f, glm::fvec4(1.0f, 0.0f, 0.0f, 1.0f));
		std::shared_ptr<Sphere> r6 = scene->CreateSphere(sphere3);

		Sphere sphere1(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 0.3f, glm::fvec4(1.0f, 0.0f, 0.0f, 1.0f));
		std::shared_ptr<Sphere> r4 = scene->CreateSphere(sphere1);

		glm::fvec2 cent = { sphere1.GetPosition().x,sphere1.GetPosition().z };
		// ------ MODEL ATOMU ------ //

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

			double frameTime = 1.0 / m_Fps;

			if (glfwGetTime() > time + frameTime)
			{
				time = glfwGetTime();
				// ---------------------------------------------
				//		FPS
				// ---------------------------------------------

				// ------ MODEL ATOMU ------
				kat += zmianaNaFps;
				kat2 += zmianaNaFps2;
				kat3 += zmianaNaFps3;
				if (kat > maxKat)
					kat = 0.0;
				if (kat2 > maxKat)
					kat2 = 0.0;
				if (kat3 > maxKat)
					kat3 = 0.0;

				sphere.CircleAround(cent, 2.0f, kat);
				sphere2.CircleAround(cent, 1.5f, kat2);
				sphere3.CircleAround(cent, 1.0f, kat3);
				// ------ MODEL ATOMU ------ //

			}
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

				for (auto& r : scene->m_Rectangles)
					r->Draw(renderer);

				for (auto& c : scene->m_Cubes)
					c->Draw(renderer);

				for (auto& s : scene->m_Spheres)
					s->Draw(renderer);
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
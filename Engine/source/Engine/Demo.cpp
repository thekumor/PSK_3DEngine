#include "demo.h"

namespace eng::showcase
{

	void Demo::Run(Engine& engine)
	{
		std::cout << "Demo is running!" << std::endl;

		Camera& camera = engine.GetCamera();

		g_EventSource.AddReceiver(&camera.GetReceiver());
		g_EventSource.AddReceiver(&GetReceiver());

		camera.GetReceiver().AddHook(EventType::KeyPress, Hook("CameraBehavior", [&](const EventData& data)
			{
				const float defaultMoveFactor = 0.05f;

				switch (std::any_cast<std::int32_t>(data.Data))
				{
					case GLFW_KEY_W:
					{
						camera.Move(glm::fvec3(0.0f, -defaultMoveFactor, 0.0f));
					} break;

					case GLFW_KEY_S:
					{
						camera.Move(glm::fvec3(0.0f, defaultMoveFactor, 0.0f));
					} break;

					case GLFW_KEY_A:
					{
						camera.Move(glm::fvec3(defaultMoveFactor, 0.0f, 0.0f));
					} break;

					case GLFW_KEY_D:
					{
						camera.Move(glm::fvec3(-defaultMoveFactor, 0.0f, 0.0f));
					} break;

					case GLFW_KEY_Q:
					{
						camera.Rotate(glm::fvec3(0.0f, 0.5f, 0.0f));
					} break;

					case GLFW_KEY_E:
					{
						camera.Rotate(glm::fvec3(0.5f, 0.0f, 0.0f));
					} break;
				}
			}));

		camera.GetReceiver().AddHook(EventType::MouseWheel, Hook("CameraBehavior", [&](const EventData& data)
			{
				const glm::dvec2& scroll = std::any_cast<glm::dvec2>(data.Data);
				const double xOffset = scroll[0];
				const double yOffset = scroll[1];

				camera.Move(glm::fvec3(0.0f, 0.0f, -yOffset / 10));
			}));

		GetReceiver().AddHook(EventType::KeyPress, Hook("FPSChange", [&](const EventData& data)
			{
				switch (std::any_cast<std::int32_t>(data.Data))
				{
					case GLFW_KEY_1:
					{
						engine.SetFPS(5);
					} break;

					case GLFW_KEY_2:
					{
						engine.SetFPS(20);
					} break;

					case GLFW_KEY_3:
					{
						engine.SetFPS(60);
					} break;

					case GLFW_KEY_4:
					{
						engine.SetFPS(200);
					} break;

					case GLFW_KEY_5:
					{
						engine.SetFPS(500);
					} break;
				}
			}));

		std::shared_ptr<Scene> scene = engine.CreateScene();

		for (std::uint32_t i = 0; i < 9; i++) // y
		{
			for (std::uint32_t j = 0; j < 9; j++) // x
			{
				glm::mat3x2 vertices = {
					-0.95f + (j * 0.22f), -0.95f + (i * 0.22f),
					-0.85f + (j * 0.22f), -0.75f + (i * 0.22f),
					-0.75f + (j * 0.22f), -0.95f + (i * 0.22f)
				};
				glm::fvec4 color = {
					j % 2 ? 1.0f : 0.0f, j % 3 ? 1.0f : 0.0f, j % 4 ? 1.0f : 0.0f, 1.0f
				};

				std::shared_ptr<Triangle*> triangle = scene->CreateTriangle(new Triangle(vertices, color));
				//(*triangle)->SetRotation(0.0f);
			}
		}
	}

}
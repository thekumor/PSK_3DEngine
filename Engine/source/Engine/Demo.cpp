#include "demo.h"

namespace eng::showcase
{

	void Demo::Run(Engine& engine)
	{
		std::cout << "Demo is running!" << std::endl;

		Camera& camera = engine.GetCamera();

		ENG_ADD_RECEIVER(camera);
		ENG_ADD_RECEIVER_PTR(this);

		ENG_ADD_HOOK(camera, EventType::KeyPress, Hook("CameraBehavior", [&](const EventData& data)
			{
				const float defaultMoveFactor = 0.03f;

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

		ENG_ADD_HOOK(camera, EventType::MouseWheel, Hook("CameraBehavior", [&](const EventData& data)
			{
				const glm::dvec2& scroll = std::any_cast<glm::dvec2>(data.Data);
				const double xOffset = scroll[0];
				const double yOffset = scroll[1];

				camera.Move(glm::fvec3(0.0f, 0.0f, -yOffset / 10));
			}));

		ENG_ADD_HOOK_PTR(this, EventType::KeyPress, Hook("FPSChange", [&](const EventData& data)
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
		glm::mat3x4 vertices = {
			-0.5f, -0.5f, 1.0f, 1.0f,
			0.0f, 0.5f, 1.0f, 1.0f,
			0.5f, -0.5f, 1.0f, 1.0f
		};
		glm::vec4 color = {
			1.0f, 0.0f, 0.0f, 1.0f
		};
		glm::mat3x2 texCoords = {
			0.0f, 0.0f,
			0.5f, 1.0f,
			1.0f, 0.0f,
		};
		Texture brick("textures/wall.jpg");
		std::shared_ptr<Scene> scene = engine.CreateScene();
		std::shared_ptr<Triangle> triangle = scene->CreateTriangle(Triangle(vertices, color, texCoords));

		ENG_ADD_RECEIVER_PTR(triangle);

		ENG_ADD_HOOK_PTR(triangle, EventType::Update, Hook("RotateTriangle", [=](const EventData& data)
			{
				std::uint64_t timeStamp = std::any_cast<std::uint64_t>(data.Data);

				//triangle->Rotate(0.0000001f * timeStamp);
			}));
	}

}
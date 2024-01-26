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
				constexpr float defaultMoveFactor = 0.03f;
				constexpr float defaultRotFactor = 0.001f;

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
						camera.Rotate(defaultRotFactor);
					} break;

					case GLFW_KEY_E:
					{
						camera.Rotate(-defaultRotFactor);
					} break;

					case GLFW_KEY_R:
					{
						camera.Rotate4(glm::fvec4(defaultRotFactor, 0.0f, 0.0f, 0.0f));
					} break;

					case GLFW_KEY_T:
					{
						camera.Rotate4(glm::fvec4(-defaultRotFactor, 0.0f, 0.0f, 0.0f));
					} break;

					case GLFW_KEY_F:
					{
						camera.Rotate4(glm::fvec4(0.0f, defaultRotFactor, 0.0f, 0.0f));
					} break;

					case GLFW_KEY_G:
					{
						camera.Rotate4(glm::fvec4(0.0f, -defaultRotFactor, 0.0f, 0.0f));
					} break;

					case GLFW_KEY_V:
					{
						camera.Rotate4(glm::fvec4(0.0f, 0.0f, defaultRotFactor, 0.0f));
					} break;

					case GLFW_KEY_B:
					{
						camera.Rotate4(glm::fvec4(0.0f, 0.0f, -defaultRotFactor, 0.0f));
					} break;

					case GLFW_KEY_U:
					{
						camera.SetRotation4(glm::fvec4(0.0f, 0.0f, 0.0f, 0.0f));
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

		std::shared_ptr<Scene> scene = engine.CreateScene();
		//std::shared_ptr<Cube> cube = scene->CreateCube(Cube(glm::fvec4(0.25f, 0.25f, 1.0f, 1.0f), 0.7f));
		//std::shared_ptr<Cube> cube1 = scene->CreateCube(Cube(glm::fvec4(-0.25f, -0.25f, 1.0f, 1.0f), 0.3f));
		//std::shared_ptr<Cube> cube2 = scene->CreateCube(Cube(glm::fvec4(-0.9f, -0.4f, 1.0f, 0.0f), 0.1f));
		Texture tex("textures/wall.jpg");
		//cube2->SetHasTexture(true);

		/*Sphere sphere(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 0.05f, glm::fvec4(1.0f, 0.0f, 0.0f, 1.0f));
		std::shared_ptr<Sphere> r3 = scene->CreateSphere(sphere);

		Sphere sphere1(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 0.3f, glm::fvec4(1.0f, 0.0f, 0.0f, 1.0f));
		std::shared_ptr<Sphere> r4 = scene->CreateSphere(sphere1);

		glm::fvec2 cent = { sphere1.GetPosition().x,sphere1.GetPosition().z};
		sphere.CircleAround(cent, 2.0f, 125.0f);*/

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

		ENG_ADD_HOOK_PTR(this, EventType::Update, Hook("ModelAtomu", [=](const EventData& data) mutable
			{
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
			}));

	}

}
#include "demo.h"

namespace eng::showcase
{

	void Demo::Run(Engine& engine)
	{
		std::cout << "Demo is running!" << std::endl;

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
		std::shared_ptr<Triangle*> triangle = engine.CreateTriangle(new Triangle(vertices, color));
		std::shared_ptr<Triangle*> triangle1 = engine.CreateTriangle(new Triangle(vertices1, color1));

		g_EventSource.AddReceiver(&(*triangle)->GetReceiver());
		(*triangle)->GetReceiver().AddHook(EventType::KeyPress, Hook(
			"Nothing", [&](const EventData& data)
			{
				std::cout << "Hello, I receive: " << std::any_cast<std::int32_t>(data.Data) << std::endl;
			}
		));
	}

}
#include "demo.h"

namespace eng::showcase
{

	void Demo::Run(Engine& engine)
	{
		std::cout << "Demo is running!" << std::endl;

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

				std::shared_ptr<Triangle*> triangle = engine.CreateTriangle(new Triangle(vertices, color));
			}
		}
	}

}
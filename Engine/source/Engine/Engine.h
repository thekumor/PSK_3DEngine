#pragma once

#include <cstdint>
#include <string>
#include <iostream>
#include <memory>
#include <vector>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <Engine/Shader.h>
#include <Engine/Window.h>
#include <Engine/Renderer.h>
#include <Engine/objects.h>
#include <Engine/events.h>
#include <Engine/BaseClass.h>
#include <Engine/Uniform.h>
#include <Engine/utility.h>
#include <Engine/Camera.h>

#define ENG_CLEAR_COLOR glm::fvec4(0.1f, 0.1f, 0.1f, 1.0f)

namespace eng
{

	// Klasa silnika która zawiera główne okno.
	class Engine : public BaseClass
	{
	public:
		Engine(std::uint32_t width, std::uint32_t height, const std::string& title);
		Engine() = default;
		~Engine();

		// Zawiera pętlę główną.
		void Run();

		std::shared_ptr<Triangle*> CreateTriangle(Triangle* object);

	private:
		// Okienko aplikacji.
		Window m_Window;

		// Źródło zdarzeń.
		EventSource m_EventSource;

		// Kamera silnika.
		Camera m_Camera;

		// Trójkąty silnika.
		std::vector<std::shared_ptr<Triangle*>> m_Triangles = { };
	};

}
#pragma once

#include <cstdint>
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "Window.h"
#include "Renderer.h"
#include "objects.h"
#include "events.h"
#include "BaseClass.h"

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

	private:
		// Okienko aplikacji.
		Window m_Window;

		// Źródło zdarzeń.
		EventSource m_EventSource;
	};

}
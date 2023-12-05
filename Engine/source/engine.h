#pragma once

#include <cstdint>
#include <string>
#include <iostream>
#include "Window.h"
#include "Renderer.h"
#include "BaseClass.h"

#define ENG_CLEAR_COLOR glm::fvec4(0.1f, 0.1f, 0.1f, 1.0f)

namespace eng
{

	// Engine class that stores the main window.
	class Engine : public BaseClass
	{
	public:
		Engine(std::uint32_t width, std::uint32_t height, const std::string& title);
		Engine() = default;

		// This has the main loop.
		void Run();

	private:
		Window m_Window;
	};

}
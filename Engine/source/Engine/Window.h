#pragma once

#include <cstdint>
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Engine/BaseClass.h>

namespace eng
{

	// Można na nim rysować elementy.
	class Window : public BaseClass
	{
	public:
		Window(std::uint32_t width, std::uint32_t height, const std::string& title);
		Window() = default;

		// Czy okno powinno być zamknięte?
		inline bool ShouldClose() const { return glfwWindowShouldClose(m_Window); }

		// Przetwarza eventy np. przyciśnięcia klawiszy.
		void HandleEvents();

		// Ustanawia to okno jako aktualne dla silnika.
		void SetCurrent();

		// Podmienia bufory ekranu.
		void SwapBuffers();

	private:
		// Szerokość i wysokość.
		std::uint32_t m_Width = 0, m_Height = 0;

		// Tytuł okna.
		std::string m_Title = "";

		// Wskaźnik okna.
		GLFWwindow* m_Window = nullptr;
	};

}
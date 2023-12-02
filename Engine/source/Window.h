#pragma once

#include <cstdint>
#include <string>
#include <iostream>
#include <GLFW/glfw3.h>

namespace eng
{

	// Can be shown and drawn onto.
	// Handles input and window-specific events.
	class Window
	{
	public:
		Window(std::uint32_t width, std::uint32_t height, const std::string& title);
		Window() = default;

		// Should the window be closed?
		inline bool ShouldClose() const { return glfwWindowShouldClose(m_Window); }

		// Has this window been properly initialized?
		inline bool IsValid() const { return m_IsValid; }

		// Processes all the events, this includes input events.
		void HandleEvents();

		// Makes the window be set as context current.
		void SetCurrent();

		// Swaps it's internal buffers so that the image is displayed.
		void SwapBuffers();

	private:
		bool m_IsValid = false;
		std::uint32_t m_Width = 0, m_Height = 0;
		std::string m_Title = "";
		GLFWwindow* m_Window = nullptr;
	};

}
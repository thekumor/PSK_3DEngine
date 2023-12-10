#pragma once

#include <cstdint>
#include <string>
#include <iostream>
#include <GLFW/glfw3.h>
#include "BaseClass.h"

namespace eng
{

	// Can be shown and drawn onto.
	// Handles input and window-specific events.
	class Window : public BaseClass
	{
	public:
		Window(std::uint32_t width, std::uint32_t height, const std::string& title);
		Window() = default;

		// Should the window be closed?
		inline bool ShouldClose() const { return glfwWindowShouldClose(m_Window); }

		// Processes all the events, this includes input events.
		void HandleEvents();

		// Makes the window be set as context current.
		void SetCurrent();

		// Swaps it's internal buffers so that the image is displayed.
		void SwapBuffers();

	private:
		// Width and height.
		std::uint32_t m_Width = 0, m_Height = 0;

		// Title displayed on top of the window.
		std::string m_Title = "";

		// Window pointer.
		GLFWwindow* m_Window = nullptr;
	};

}
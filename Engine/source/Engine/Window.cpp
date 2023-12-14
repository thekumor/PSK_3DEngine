#include "window.h"

namespace eng
{

	Window::Window(std::uint32_t width, std::uint32_t height, const std::string& title)
		: m_Width(width), m_Height(height), m_Title(title)
	{
		m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

		if (!m_Window)
		{
			std::cerr << "Failed to create a GLFW window." << std::endl;
			SetValid(false);
		}
	}

	void Window::HandleEvents()
	{
		glfwPollEvents();
	}

	void Window::SetCurrent()
	{
		glfwMakeContextCurrent(m_Window);
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}

}
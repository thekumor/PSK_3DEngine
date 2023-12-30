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
		else
		{
			glfwSetKeyCallback(m_Window, KeyCallback);
			glfwSetMouseButtonCallback(m_Window, MouseCallback);
			glfwSetScrollCallback(m_Window, ScrollCallback);
			glfwSetCursorPosCallback(m_Window, MousePosCallback);
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

	void KeyCallback(GLFWwindow* window, std::int32_t key, std::int32_t scanCode, std::int32_t action, std::int32_t mods)
	{
		const EventData eventData(key);
		g_EventSource.CallEvent(EventType::KeyPress, eventData);
	}

	void MousePosCallback(GLFWwindow* window, double x, double y)
	{
	}

	void MouseCallback(GLFWwindow* window, std::int32_t button, std::int32_t action, std::int32_t mods)
	{
		const EventData eventData(button);
		g_EventSource.CallEvent(EventType::MousePress, eventData);
	}

	void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
	{
		const EventData eventData(glm::dvec2(xOffset, yOffset));
		g_EventSource.CallEvent(EventType::MouseWheel, eventData);
	}

}
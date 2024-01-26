#pragma once

#include <cstdint>
#include <string>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <Engine/BaseClass.h>
#include <Engine/events.h>
#include <engine/globals.h>

namespace eng
{

	/// <summary>
	/// Funkcja zwrotna dla wejścia z klawiatury.
	/// </summary>
	/// <param name="window">Okno z którego pochodzi wejście</param>
	/// <param name="key">Wciśnięty klawisz</param>
	/// <param name="scanCode">???</param>
	/// <param name="action">???</param>
	/// <param name="mods">???</param>
	static void KeyCallback(GLFWwindow* window, std::int32_t key, std::int32_t scanCode, std::int32_t action, std::int32_t mods);

	/// <summary>
	/// Funkcja zwrotna dla wejścia z myszy (pozycja).
	/// </summary>
	/// <param name="window">Okno z którego pochodzi wejście</param>
	/// <param name="x">Pozycja x myszy</param>
	/// <param name="y">Pozycja y myszy</param>
	static void MousePosCallback(GLFWwindow* window, double x, double y);

	/// <summary>
	/// Funkcja zwrotna dla wejścia z myszy (przyciski).
	/// </summary>
	/// <param name="window">Okno z którego pochodzi wejście</param>
	/// <param name="button">Przycisk myszy</param>
	/// <param name="action">???</param>
	/// <param name="mods">???</param>
	static void MouseCallback(GLFWwindow* window, std::int32_t button, std::int32_t action, std::int32_t mods);

	/// <summary>
	/// Funkcja zwrotna dla wejścia z myszy (scroll).
	/// </summary>
	/// <param name="window">Okno z którego pochodzi wejście</param>
	/// <param name="xOffset">Przesunięcie x pozycji</param>
	/// <param name="yOffset">Przesunięcie y pozycji</param>
	static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);

	/// <summary>
	/// Okno. Na nim rysowane są elementy.
	/// </summary>
	class Window : public BaseClass
	{
	public:
		Window(std::uint32_t width, std::uint32_t height, const std::string& title);
		Window() = default;

		/// <summary>
		/// Zwraca, czy okno powinno być zamknięte.
		/// </summary>
		/// <returns>Czy powinno być zamknięte?</returns>
		inline bool ShouldClose() const { return glfwWindowShouldClose(m_Window); }

		/// <summary>
		/// Przetwarza zdarzenia, np. wciśnięcia klawisza.
		/// </summary>
		void HandleEvents();

		/// <summary>
		/// Ustanawia okno jako aktualne i główne dla silnika.
		/// </summary>
		void SetCurrent();

		/// <summary>
		/// Podmienia bufory wyświetlania.
		/// </summary>
		void SwapBuffers();

		GLFWwindow* GetWindow() const {
			return m_Window;
		}

	private:
		/// <summary>
		/// Szerokość i wysokość.
		/// </summary>
		std::uint32_t m_Width = 0, m_Height = 0;

		/// <summary>
		/// Tytuł okna.
		/// </summary>
		std::string m_Title = "";

		/// <summary>
		/// Wskaźnik do okna.
		/// </summary>
		GLFWwindow* m_Window = nullptr;
	};

}
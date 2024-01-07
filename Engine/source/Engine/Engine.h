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

	// Klasa zawiera obiekty.
	class Scene : public BaseClass
	{
	public:
		friend class Engine;

		Scene() = default;

		// Tworzy nowy trójkąt.
		std::shared_ptr<Triangle*> CreateTriangle(Triangle* object);

	private:
		// Trójkąty sceny.
		std::vector<std::shared_ptr<Triangle*>> m_Triangles = { };
	};

	// Klasa silnika która zawiera główne okno.
	class Engine : public BaseClass
	{
	public:
		Engine(std::uint32_t width, std::uint32_t height, const std::string& title);
		Engine() = default;
		~Engine();

		// Zwraca główną kamerę silnika.
		inline Camera& GetCamera() { return m_Camera; }

		// Zwraca maksymalną ilość klatek.
		inline std::uint32_t GetMaxFPS() { return m_Fps; }

		// Tworzy nową scenę.
		std::shared_ptr<Scene> CreateScene();

		// Zawiera pętlę główną.
		void Run();

		// Ustawia ilość klatek.
		void SetFPS(std::uint32_t fps);

	private:
		// Okienko aplikacji.
		Window m_Window;

		// Źródło zdarzeń.
		EventSource m_EventSource;

		// Kamera silnika.
		Camera m_Camera;

		// Sceny silnika.
		std::vector<std::shared_ptr<Scene>> m_Scenes = {};

		// Maksymalna ilość klatek.
		std::uint32_t m_Fps = 120;
	};

}
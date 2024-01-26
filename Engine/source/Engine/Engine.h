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

	/// <summary>
	/// Sceny zawierające obiekty.
	/// </summary>
	class Scene : public BaseClass
	{
	public:
		friend class Engine;

		Scene() = default;

		/// <summary>
		/// Tworzy nowy trójkąt na danej scenie.
		/// </summary>
		/// <param name="object">Obiekt trójkąta</param>
		/// <returns>Wskaźnik na nowy trójkąt</returns>
		std::shared_ptr<Triangle> CreateTriangle(Triangle object);

		/// <summary>
		/// Tworzy nowy prostokąt na danej scenie.
		/// </summary>
		/// <param name="object">Obiekt prostokąta</param>
		/// <returns>Wskaźnik na nowy prostokąt</returns>
		std::shared_ptr<Rectangle> CreateRectangle(Rectangle object);

		/// <summary>
		/// Tworzy nową kostkę na danej scenie.
		/// </summary>
		/// <param name="object">Obiekt kostki</param>
		/// <returns>Wskaźnik na nowa kostkę</returns>
		std::shared_ptr<Cube> CreateCube(Cube object);

		/// <summary>
		/// Tworzy nowy trójkąt na danej scenie.
		/// </summary>
		/// <param name="object">Obiekt trójkąta</param>
		/// <returns>Wskaźnik na nowy trójkąt</returns>
		std::shared_ptr<Sphere> CreateSphere(Sphere object);

	private:
		/// <summary>
		/// Trójkąty dla danej sceny.
		/// </summary>
		std::vector<std::shared_ptr<Triangle>> m_Triangles = { };
		
		/// <summary>
		/// Prostokąty dla danej sceny.
		/// </summary>
		std::vector<std::shared_ptr<Rectangle>> m_Rectangles = { };

		/// <summary>
		/// Kostki dla danej sceny.
		/// </summary>
		std::vector<std::shared_ptr<Cube>> m_Cubes = { };

		/// <summary>
		/// Sphere dla danej sceny.
		/// </summary>
		std::vector<std::shared_ptr<Sphere>> m_Spheres = { };
	};

	/// <summary>
	/// Klasa silnika która zawiera sceny, kamerę i okno.
	/// </summary>
	class Engine : public BaseClass
	{
	public:
		Engine(std::uint32_t width, std::uint32_t height, const std::string& title);
		Engine() = default;
		~Engine();

		/// <summary>
		/// Zwraca główną kamerę silnika.
		/// </summary>
		/// <returns>Główna kamera</returns>
		inline Camera& GetCamera() { return m_Camera; }

		/// <summary>
		/// Zwraca aktualny limit klatek.
		/// </summary>
		/// <returns>Limit klatek</returns>
		inline std::uint32_t GetMaxFPS() { return m_Fps; }


		/// <summary>
		/// Tworzy nową scenę.
		/// </summary>
		/// <returns>Wskaźnik na nową scenę</returns>
		std::shared_ptr<Scene> CreateScene();

		/// <summary>
		/// Kod silnika i pętla główna.
		/// </summary>
		void Run();
		
		/// <summary>
		/// Ustawia daną ilość klatek jako limit.
		/// </summary>
		/// <param name="fps">Limit klatek</param>
		void SetFPS(std::uint32_t fps);

	private:
		/// <summary>
		/// Okno aplikacji.
		/// </summary>
		Window m_Window;
		
		/// <summary>
		/// Źródło zdarzeń.
		/// </summary>
		EventSource m_EventSource;

		/// <summary>
		/// Główna kamera silnika.
		/// </summary>
		Camera m_Camera;

		/// <summary>
		/// Sceny silnika.
		/// </summary>
		std::vector<std::shared_ptr<Scene>> m_Scenes = {};

		/// <summary>
		/// Maksymalna ilość klatek.
		/// </summary>
		std::uint32_t m_Fps = 120;

	};

}
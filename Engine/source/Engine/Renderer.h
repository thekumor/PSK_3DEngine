#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <Engine/internal/buffers.h>
#include <Engine/BaseClass.h>

namespace eng
{

	/// <summary>
	/// Renderer który wyświetla obiekty.
	/// </summary>
	class Renderer : public BaseClass
	{
	public:
		Renderer(const Renderer&) = delete;
		Renderer& operator=(Renderer&) = delete;

		/// <summary>
		/// Zwraca renderer.
		/// </summary>
		/// <returns>Renderer</returns>
		static Renderer* Get();
		
		/// <summary>
		/// Czyści ekran.
		/// </summary>
		/// <param name="color">Kolor tła</param>
		void Clear(const glm::fvec4& color);

		/// <summary>
		/// Rysuje z danej tablicy werteksów.
		/// </summary>
		/// <param name="vao">Tablica werteksów</param>
		void Draw(std::uint32_t vao);
	private:
		Renderer() = default;
	};

}
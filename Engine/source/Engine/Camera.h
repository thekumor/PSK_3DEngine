#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glfw/glfw3.h>

#include <Engine/BaseClass.h>
#include <Engine/events.h>
#include <Engine/globals.h>

namespace eng
{

	/// <summary>
	/// Kamera. Steruje ona wyświetlaniem obrazu.
	/// </summary>
	class Camera : public BaseClass, public EventInteractive
	{
	public:
		Camera(const glm::fvec3& position, const glm::fvec3& angles);
		Camera() = default;

		/// <summary>
		/// Zwraca pozycję kamery.
		/// </summary>
		/// <returns>Pozycja kamery</returns>
		inline const glm::fvec3& GetPosition() const { return m_Position; }

		/// <summary>
		/// Zwraca kąt nachylenia kamery.
		/// </summary>
		/// <returns>Kąt nachylenia kamery</returns>
		inline const glm::fvec3& GetRotation() const { return m_Rotation; }

		/// <summary>
		/// Rusza kamerą.
		/// </summary>
		/// <param name="factor">Kierunek ruchu</param>
		void Move(const glm::fvec3& factor);

		/// <summary>
		/// Ustawia kamerze pozycję.
		/// </summary>
		/// <param name="position">Nowa pozycja</param>
		void SetPosition(const glm::fvec3& position);

		/// <summary>
		/// Ustawia kamerze kąt nachylenia.
		/// </summary>
		/// <param name="rotation">Nowy kąt nachylenia</param>
		void SetRotation(const glm::fvec3& rotation);

		/// <summary>
		/// Rotuje kamerę o dany kąt.
		/// </summary>
		/// <param name="factor">Kąt???</param>
		void Rotate(const glm::fvec3& factor);

	private:
		/// <summary>
		/// Odbiornik zdarzeń.
		/// </summary>
		EventReceiver m_Receiver;

		/// <summary>
		/// Pozycja kamery.
		/// </summary>
		glm::fvec3 m_Position = {};

		/// <summary>
		/// Kąt nachylenia kamery.
		/// </summary>
		glm::fvec3 m_Rotation = {};
	};

}
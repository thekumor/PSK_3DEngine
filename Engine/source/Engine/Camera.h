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
		Camera(const glm::fvec3& position, float rotationRadians);
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
		inline float GetRotation() const { return m_Rotation; }

		/// <summary>
		/// Zwraca radiany nachylenia kamery.
		/// </summary>
		/// <returns>Radiany nachylenia kamery</returns>
		inline const glm::fvec4& GetRotation4() const { return m_Rotation4; }

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
		/// Resetuje kamerę o dany kąt.
		/// </summary>
		/// <param name="radians">Kąt w radianach</param>
		void SetRotation(float radians);

		/// <summary>
		/// Resetuje kamerę na dane radiany.
		/// </summary>
		/// <param name="radians">Radiany nachylenia.</param>
		void SetRotation4(const glm::fvec4& radians);

		/// <summary>
		/// Rotuje kamerę o dane radiany.
		/// </summary>
		/// <param name="factor">Dodatkowe radiany</param>
		void Rotate4(const glm::fvec4& factor);

		/// <summary>
		/// Rotuje kamerę o dany kąt.
		/// </summary>
		/// <param name="radians">Kąt w radianach</param>
		void Rotate(float radians);

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
		/// Rotacja kamery w radianach.
		/// </summary>
		glm::fvec4 m_Rotation4 = {};

		/// <summary>
		/// Rotacja kamery w radianach.
		/// </summary>
		float m_Rotation = 0.0f;
	};

}
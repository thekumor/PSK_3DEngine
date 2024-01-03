#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glfw/glfw3.h>

#include <Engine/BaseClass.h>
#include <Engine/events.h>
#include <Engine/globals.h>

namespace eng
{

	// Kamera która steruje wyświetlaniem obrazu.
	class Camera : public BaseClass, public EventInteractive
	{
	public:
		Camera(const glm::fvec3& position, const glm::fvec3& angles);
		Camera() = default;

		// Zwraca pozycję kamery.
		inline const glm::fvec3& GetPosition() const { return m_Position; }

		// Zwraca kąty nachylenia kamery.
		inline const glm::fvec3& GetRotation() const { return m_Rotation; }

		// Rusza kamerą.
		void Move(const glm::fvec3& factor);

		// Ustawia pozycję kamery.
		void SetPosition(const glm::fvec3& position);

		// Ustawia kąt nachylenia kamery.
		void SetRotation(const glm::fvec3& rotation);

		// Rotuje kamerę o podany kąt.
		void Rotate(const glm::fvec3& factor);

	private:
		// Odbiornik zdarzeń.
		EventReceiver m_Receiver;

		// Pozycja kamery.
		glm::fvec3 m_Position = {};

		// Kąt nachylenia kamery.
		glm::fvec3 m_Rotation = {};
	};

}
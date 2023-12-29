#pragma once

#include <glm/glm.hpp>

#include <Engine/BaseClass.h>

namespace eng
{

	// Kamera która steruje wyświetlaniem obrazu.
	class Camera : public BaseClass
	{
	public:
		Camera(const glm::fvec3& position, const glm::fvec3& angles);
		Camera() = default;

		// Zwraca pozycję kamery.
		inline glm::fvec3 GetPosition() const { return m_Position; }

		// Zwraca kąt nachylenia kamery.
		inline glm::fvec3 GetAngles() const { return m_Angles; }

		// Rusza kamerą.
		void Move(const glm::fvec3& factor);

		// Ustawia pozycję kamery.
		void SetPosition(const glm::fvec3& position);

		// Ustawia kąt nachylenia.
		void SetAngles(const glm::fvec3& angles);

		// Pochyla kamerę.
		void Rotate(const glm::fvec3& factor);

	private:
		// Pozycja kamery.
		glm::fvec3 m_Position = {};

		// Kąt nachylenia kamery.
		glm::fvec3 m_Angles = {};
	};

}
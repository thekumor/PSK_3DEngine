#include "Camera.h"

namespace eng
{

	Camera::Camera(const glm::fvec3& position, const glm::fvec3& angles)
		: m_Position(position), m_Rotation(angles)
	{
	}

	void Camera::Move(const glm::fvec3& factor)
	{
		m_Position += factor;
	}

	void Camera::SetPosition(const glm::fvec3& position)
	{
		m_Position = position;
	}

	void Camera::SetRotation(const glm::fvec3& rotation)
	{
		m_Rotation = rotation;
	}

	void Camera::Rotate(const glm::fvec3& factor)
	{
	}

}
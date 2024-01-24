#include "Camera.h"

namespace eng
{

	Camera::Camera(const glm::fvec3& position, float rotationRadians)
		: m_Position(position), m_Rotation(rotationRadians)
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

	void Camera::SetRotation(float radians)
	{
		m_Rotation = radians;
	}

	void Camera::Rotate(float radians)
	{
		m_Rotation += radians;
	}

}
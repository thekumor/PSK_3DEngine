#include "Camera.h"

namespace eng
{

	Camera::Camera(const glm::fvec3& position, const glm::fvec3& angles)
		: m_Position(position), m_Angles(angles)
	{
		g_EventSource.AddReceiver(&m_Receiver);

		float defaultMoveFactor = 100;
		m_Receiver.AddHook(EventType::KeyPress, Hook("CameraBehavior", [&](const EventData& data)
			{
				std::cout << m_Position.x << ", " << m_Position.y << std::endl;

				switch (std::any_cast<std::int32_t>(data.Data))
				{
					case GLFW_KEY_W:
					{
						Move(glm::fvec3(0.0f, defaultMoveFactor, 0.0f));
					} break;

					case GLFW_KEY_S:
					{
						Move(glm::fvec3(0.0f, -defaultMoveFactor, 0.0f));
					} break;

					case GLFW_KEY_A:
					{
						Move(glm::fvec3(-defaultMoveFactor, 0.0f, 0.0f));
					} break;

					case GLFW_KEY_D:
					{
						Move(glm::fvec3(defaultMoveFactor, 0.0f, 0.0f));
					} break;
				}
			}));
	}

	void Camera::Move(const glm::fvec3& factor)
	{
		m_Position += factor;
	}

	void Camera::SetPosition(const glm::fvec3& position)
	{
		m_Position = position;
	}

	void Camera::SetAngles(const glm::fvec3& angles)
	{
		m_Angles = angles;
	}

	void Camera::Rotate(const glm::fvec3& factor)
	{
		m_Angles += factor;
	}

}
#include "Camera.h"

namespace eng
{

	Camera::Camera(const glm::fvec3& position, const glm::fvec3& angles)
		: m_Position(position), m_Rotation(angles)
	{
		g_EventSource.AddReceiver(&m_Receiver);

		m_Receiver.AddHook(EventType::KeyPress, Hook("CameraBehavior", [&](const EventData& data)
			{
				const float defaultMoveFactor = 0.05f;

				std::cout << m_Position.x << ", " << m_Position.y << std::endl;

				switch (std::any_cast<std::int32_t>(data.Data))
				{
					case GLFW_KEY_W:
					{
						Move(glm::fvec3(0.0f, -defaultMoveFactor, 0.0f));
					} break;

					case GLFW_KEY_S:
					{
						Move(glm::fvec3(0.0f, defaultMoveFactor, 0.0f));
					} break;

					case GLFW_KEY_A:
					{
						Move(glm::fvec3(defaultMoveFactor, 0.0f, 0.0f));
					} break;

					case GLFW_KEY_D:
					{
						Move(glm::fvec3(-defaultMoveFactor, 0.0f, 0.0f));
					} break;

					case GLFW_KEY_Q:
					{
						Rotate(glm::fvec3(0.0f, 0.5f, 0.0f));
					} break;

					case GLFW_KEY_E:
					{
						Rotate(glm::fvec3(0.5f, 0.0f, 0.0f));
					} break;
				}
			}));

		m_Receiver.AddHook(EventType::MouseWheel, Hook("CameraBehavior", [&](const EventData& data)
			{
				const glm::dvec2& scroll = std::any_cast<glm::dvec2>(data.Data);
				const double xOffset = scroll[0];
				const double yOffset = scroll[1];

				Move(glm::fvec3(0.0f, 0.0f, -yOffset / 10));
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

	void Camera::SetRotation(const glm::fvec3& rotation)
	{
		m_Rotation = rotation;
	}

	void Camera::Rotate(const glm::fvec3& factor)
	{
	}

}
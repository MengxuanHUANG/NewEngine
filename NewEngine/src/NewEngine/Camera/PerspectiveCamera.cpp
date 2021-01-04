#include "pch.h"
#include "PerspectiveCamera.h"

namespace engine
{
	PerspectiveCamera::PerspectiveCamera(float fov, float aspect_ration, float near_plane, float far_plane, glm::vec3 position, glm::vec3 up, float yaw, float pitch)
		:m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_Yaw(yaw), m_Pitch(pitch)
	{
		m_Position = position;
		m_WorldUp = up;
		m_Projection = glm::perspective(glm::radians(fov), aspect_ration, near_plane, far_plane);
		UpdateCameraVectors();
	}
	PerspectiveCamera::PerspectiveCamera(float fov, float aspect_ration, float near_plane, float far_plane, 
		float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
		:m_Yaw(yaw), m_Pitch(pitch)
	{
		m_Position = glm::vec3(posX, posY, posZ);
		m_WorldUp = glm::vec3(upX, upY, upZ);
		m_Projection = glm::perspective(glm::radians(fov), aspect_ration, near_plane, far_plane);
		UpdateCameraVectors();
	}
	void PerspectiveCamera::SetPostion(const glm::vec3& position)
	{
		m_Position = position;
		UpdateCameraVectors();
	}
	void PerspectiveCamera::SetProjection(float fov, float aspect_ration, float near_plane, float far_plane)
	{
		m_Projection = glm::perspective(glm::radians(fov), aspect_ration, near_plane, far_plane);
	}
	void PerspectiveCamera::SetRotation(float yaw, float pitch)
	{
		m_Yaw = yaw;
		m_Pitch = pitch;
		UpdateCameraVectors();
	}
	void PerspectiveCamera::AddRotation(float yaw, float pitch, bool constrain_pitch = true)
	{
		m_Yaw += yaw;
		m_Pitch += pitch;
		if (constrain_pitch)
		{
			if (m_Pitch > 89.0f) m_Pitch = 89.0f;
			if (m_Pitch < -89.0f) m_Pitch = -89.0f;
		}
		UpdateCameraVectors();
	}
	void PerspectiveCamera::UpdateCameraVectors()
	{
		// calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);
		// also re-calculate the Right and Up vector
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));

		m_View = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}
}
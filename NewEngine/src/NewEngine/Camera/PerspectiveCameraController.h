#pragma once

#include "PerspectiveCamera.h"

#include "NewEngine/Events/MouseEvents.h"
#include "NewEngine/Events/ApplicationEvents.h"

namespace engine
{
	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController(float fov, float aspect_ration, float near_plane, float far_plane, 
			glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
			float yaw = -90.0f, float pitch = 0.0f);

		void OnUpdate();
		void OnEvent(Event& event);

		void SetPosition(glm::vec3 position);
		void SetRotation(float yaw, float pitch);
		void SetZoomLevel(float level);

		inline void SetMovementSpeed(float speed) { m_CamMovementSpeed = speed; }
		inline void SetSensitivity(float sensitivity) { m_CamSensitivity = sensitivity; }

		inline float GetCamSpeed() const { return m_CamMovementSpeed; }
		inline float GetCamSensitivity() const { return m_CamSensitivity; }
		inline PerspectiveCamera& GetCamera() { return m_Camera; }
		inline const PerspectiveCamera& GetCamera() const { return m_Camera; }
		inline float GetZoomLevel() { return m_ZoomLevel; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnWindowResize(WindowResizedEvent& event);
		bool OnCamRotate(MouseMovedEvent& event);
		bool OnMouseMoved(MouseMovedEvent& event);
	private:
		float m_AspectRatio;

		PerspectiveCamera m_Camera;

		float m_CamMovementSpeed = 5.0f;
		float m_CamSensitivity = 0.03f;
		float m_ZoomLevel = 45.0f;
		float m_MousePosX;
		float m_MousePosY;
	};
}
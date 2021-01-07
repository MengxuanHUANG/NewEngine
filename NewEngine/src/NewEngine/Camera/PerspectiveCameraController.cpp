#include "pch.h"
#include "PerspectiveCameraController.h"

#include "NewEngine/Core/Input.h"

namespace engine
{
	PerspectiveCameraController::PerspectiveCameraController(float fov, float aspect_ration, float near_plane, float far_plane,
		glm::vec3 position , glm::vec3 up  , float yaw, float pitch )
		:m_AspectRatio(aspect_ration),
		m_Camera(fov, aspect_ration, near_plane, far_plane, position, up, yaw, pitch)
	{
		m_MousePosX = Input::GetMousePos().first;
		m_MousePosY = Input::GetMousePos().second;
	}
	void PerspectiveCameraController::OnUpdate()
	{
		m_Camera.UpdateCameraVectors();
	}

	void PerspectiveCameraController::SetPosition(glm::vec3 position)
	{
		m_Camera.SetPostion(position);
	}
	void PerspectiveCameraController::SetRotation(float yaw, float pitch)
	{
		m_Camera.SetRotation(yaw, pitch);
	}
	void PerspectiveCameraController::SetZoomLevel(float level)
	{
		m_ZoomLevel = level;
		m_Camera.SetProjection(m_ZoomLevel, m_AspectRatio, 1.0f, 100.0f);
	}
	void PerspectiveCameraController::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(PerspectiveCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT_FN(PerspectiveCameraController::OnWindowResize));
		if (Input::IsMouseButtonPressed(2))
		{
			dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(PerspectiveCameraController::OnCamRotate));
		}
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(PerspectiveCameraController::OnMouseMoved));
	}
	bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent& event)
	{
		m_ZoomLevel -= event.GetOffsetY() * 0.5f;

		m_ZoomLevel = std::max(m_ZoomLevel, 1.0f);
		m_ZoomLevel = std::min(m_ZoomLevel, 45.0f);

		m_Camera.SetProjection(m_ZoomLevel, m_AspectRatio, 1.0f, 100.0f);
		return false;
	}
	bool PerspectiveCameraController::OnWindowResize(WindowResizedEvent& event)
	{
		m_AspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
		m_Camera.SetProjection(m_ZoomLevel, m_AspectRatio, 1.0f, 100.0f);
		return false;
	}
	bool PerspectiveCameraController::OnCamRotate(MouseMovedEvent& event)
	{
		float offset_x = (event.GetX() - m_MousePosX) * m_CamSensitivity;
		float offset_y = (event.GetY() - m_MousePosY) * m_CamSensitivity;

		/*std::stringstream ss;
		ss << "Mouse Moved: [ " << offset_x << ", " << offset_y << " ]";
		MY_ENGINE_INFO(ss.str());*/

		m_Camera.AddRotation(offset_x, offset_y, true);
		return false;
	}
	bool PerspectiveCameraController::OnMouseMoved(MouseMovedEvent& event)
	{
		m_MousePosX = event.GetX();
		m_MousePosY = event.GetY();

		/*std::stringstream ss;
		ss << "Mouse Pos: [ " <<m_MousePosX<<", "<< m_MousePosY<<" ]";
		MY_ENGINE_TRACE(ss.str());*/
		return false;
	}
}
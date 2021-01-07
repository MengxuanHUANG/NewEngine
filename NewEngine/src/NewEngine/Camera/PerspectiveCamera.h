#pragma once

namespace engine
{
	class PerspectiveCamera
	{
	public:
		PerspectiveCamera(float fov, float aspect_ration, float near_plane, float far_plane, 
			glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
			float yaw = -90.0f, float pitch = 0.0f);

		PerspectiveCamera(float fov, float aspect_ration, float near_plane, float far_plane, 
			float posX, float posY, float posZ, float upX, float upY, float upZ, 
			float yaw = -90.0f, float pitch = 0.0f);

		void SetPostion(const glm::vec3& position);
		void SetRotation(float yaw, float pitch);
		void AddRotation(float yaw, float pitch, bool constrain_pitch);
		void SetProjection(float fov, float aspect_ration, float near_plane, float far_plane);

		inline float& GetYaw() { return m_Yaw; }
		inline float& GetPitch() { return m_Pitch; }
		inline glm::vec3& GetPosition() { return m_Position; }
		inline const glm::mat4& GetViewMatrix() const { return m_View; }
		inline const glm::mat4& GetProjectionMatrix() const { return m_Projection; }
		void UpdateCameraVectors();
	private:
		// camera Attributes
		glm::vec3 m_Position;
		glm::vec3 m_Front;
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp;
		// euler Angles
		float m_Yaw;
		float m_Pitch;

		//view, projection matrix
		glm::mat4 m_View;
		glm::mat4 m_Projection;
	};
}
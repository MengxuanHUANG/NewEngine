#pragma once

namespace engine
{
	class SpotLight
	{
	public:
		SpotLight(glm::vec3 position, glm::vec3 color);
		~SpotLight();
		
		inline void SetColor(glm::vec3 color) { m_Color = color; }
		inline glm::vec3& GetColor() { return m_Color; }
		inline void SetPosition(glm::vec3 position) { m_Position = position; }
		inline glm::vec3& GetPosition() { return m_Position; }
	private:
		float m_Strength;

		glm::vec3 m_Color;
		glm::vec3 m_Position;
	};
}
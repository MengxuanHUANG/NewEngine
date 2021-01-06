#pragma once


namespace engine
{
	class Light
	{
	public:
		virtual glm::vec3& GetPosition() { return m_Position; }
		virtual glm::vec4& GetColor() { return m_Color; }
		virtual float& GetStrength() { return m_Strength; }

		virtual unsigned int GetVerticesCount() const = 0;
		virtual unsigned int GetIndicesCount() const = 0;

		virtual const float* GetVertices() const = 0;
		virtual const unsigned int* GetIndices() const = 0;
	protected:
		Light(glm::vec3 position, glm::vec4 color, float strength);
		
		float m_Strength;
		glm::vec4 m_Color;
		glm::vec3 m_Position;
	};
}
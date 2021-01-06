#pragma once

namespace engine
{
	struct Float3
	{
		float x, y, z;
	};
	struct Float4
	{
		float r, g, b, a;
	};
	struct Float2
	{
		float x, y;
	};
	struct Vertex
	{
		Float3 positon;
		Float3 normal;
		Float4 color;
		float slot;
	};

	class Object
	{
	public:
		virtual void ReCalculateModelMat() = 0;
		virtual unsigned int GetVerticesCount() const = 0;
		virtual unsigned int GetIndicesCount() const = 0;

		virtual const float* GetVertices() const = 0;
		virtual const unsigned int* GetIndices() const = 0;

		virtual glm::vec3& GetScale() { return m_Scale; }
		virtual glm::vec3& GetTanslate() { return m_Translation; }
		virtual glm::vec3& GetRotation() { return m_Rotation; }
		virtual glm::mat4 GetModelMat() { return m_ModelMat; }
	protected:
		Object(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
			:m_Translation(translation), m_Rotation(rotation), m_Scale(scale)
		{
			m_ModelMat = glm::translate(glm::mat4(1.0f), translation);
			m_ModelMat = glm::rotate(m_ModelMat, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			m_ModelMat = glm::rotate(m_ModelMat, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
			m_ModelMat = glm::rotate(m_ModelMat, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			m_ModelMat = glm::scale(m_ModelMat, scale);
		}
		glm::vec3 m_Translation;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;

		glm::mat4 m_ModelMat;
	};
}
#include "pch.h"
#include "Object.h"

namespace engine
{
	Object::Object(glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
		:m_Translation(translation), m_Rotation(rotation), m_Scale(scale)
	{
		m_ModelMat = glm::translate(glm::mat4(1.0f), translation);
		m_ModelMat = glm::rotate(m_ModelMat, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		m_ModelMat = glm::rotate(m_ModelMat, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		m_ModelMat = glm::rotate(m_ModelMat, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		m_ModelMat = glm::scale(m_ModelMat, scale);
	}
}
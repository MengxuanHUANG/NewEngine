#include "pch.h"
#include "Cube.h"

namespace engine
{
	Cube::Cube(glm::vec4 color, glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
		:Object(scale, translation, rotation), m_Color(color)
	{
	}
	Cube::Cube(const std::string& file_path, glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
		:Object(scale, translation, rotation), m_Color(1.0f)
	{
	}
	Cube::~Cube()
	{
	}
	void Cube::ReCalculateModelMat()
	{
		m_ModelMat = glm::translate(glm::mat4(1.0f), m_Translation);
		m_ModelMat = glm::rotate(m_ModelMat, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		m_ModelMat = glm::rotate(m_ModelMat, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		m_ModelMat = glm::rotate(m_ModelMat, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		m_ModelMat = glm::scale(m_ModelMat, m_Scale);
	}
}
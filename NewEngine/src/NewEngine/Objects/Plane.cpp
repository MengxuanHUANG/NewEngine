#include "pch.h"
#include "Plane.h"

namespace engine
{
	Plane::Plane(glm::vec4 color, glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
		:Object(translation, rotation, scale), m_Color(color)
	{
		vertices = new float[]{
			//front
			-0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, 0.0f, //0
			 0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, //1
			 0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, 0.0f, //2
			-0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, 0.0f, //3
		};
		indices = new unsigned int[]{
			 0,  1,  2,  2,  3,  0
		};
	}
	Plane::Plane(const std::string& file_path, glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale)
		:Object(translation, rotation, scale), m_Color(1.0f)
	{
		vertices = new float[]{
			//front
			-0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, 0.0f, //0
			 0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, 0.0f, //1
			 0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, 0.0f, //2
			-0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, 0.0f, //3
		};
		indices = new unsigned int[]{
			 0,  1,  2,  2,  3,  0
		};
	}
	Plane::~Plane()
	{
		delete[] vertices;
		delete[] indices;
	}
	void Plane::ReCalculateModelMat()
	{
		m_ModelMat = glm::translate(glm::mat4(1.0f), m_Translation);
		m_ModelMat = glm::rotate(m_ModelMat, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		m_ModelMat = glm::rotate(m_ModelMat, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		m_ModelMat = glm::rotate(m_ModelMat, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		m_ModelMat = glm::scale(m_ModelMat, m_Scale);
	}
}

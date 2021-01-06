#pragma once

#include "Object.h"
#include "NewEngine/Renderer/VertexArray.h"

#include <vector>
#include <string>

namespace engine
{
	class Cube : public Object
	{
	public:
		Cube(glm::vec4 color = glm::vec4(1.0f), glm::vec3 translation = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));
		Cube(const std::string& file_path, glm::vec3 translation = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));
		~Cube();
		
		glm::vec4& GetColor() { return m_Color; }
		void SetTexture(const std::string& file_path);

		virtual void ReCalculateModelMat() override;

		virtual inline unsigned int GetVerticesCount() const override { return m_VericesCount; }
		virtual inline unsigned int GetIndicesCount() const override { return m_IndicesCount; }
		virtual inline const float* GetVertices() const override { return vertices; }
		virtual inline const unsigned int* GetIndices() const override { return indices; }
		inline unsigned int& GetRendererID() { return m_RendererID; };
	private:
		unsigned int m_RendererID;
		unsigned int m_VericesCount = 24;
		unsigned int m_IndicesCount = 36;
		glm::vec4 m_Color;

		float vertices[312]{
			//front
			-0.5f, -0.5f,  0.5f, 0.0f,  0.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, //0
			 0.5f, -0.5f,  0.5f, 0.0f,  0.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //1
			 0.5f,  0.5f,  0.5f, 0.0f,  0.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //2
			-0.5f,  0.5f,  0.5f, 0.0f,  0.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, //3

			//back
			-0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, //4
			 0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //5
			 0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //6
			-0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, //7

			//left
			-0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, //8
			-0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //9
			-0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //10
			-0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, //11

			//right
			 0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, //12
			 0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //13
			 0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //14
			 0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, //15

			//top
			 0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, //16
			 0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //17
			-0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //18
			-0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, //19

			//bottom
			-0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, //20
			-0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //21
			 0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //22
			 0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f  //23
		};
		unsigned int indices[36]{
			 0,  1,  2,  2,  3,  0, //front
			 4,  7,  6,  6,  5,  4, //back
			 8,  9, 10, 10, 11,  8, //left
			12, 13, 14, 14, 15, 12, //right
			16, 17, 18, 18, 19, 16, //top
			20, 21, 22, 22, 23, 20  //bottom
		};
	};
}
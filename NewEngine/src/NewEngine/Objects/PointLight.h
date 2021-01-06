#pragma once

#include "Light.h"

namespace engine
{
	class PointLight : public Light
	{
	public:
		PointLight(glm::vec3 position = glm::vec3(0.0f), glm::vec4 color = glm::vec4(1.0f), float strength = 1.0f);
		~PointLight();

		inline unsigned int GetVerticesCount() const override { return m_VerticesCount; }
		inline unsigned int GetIndicesCount() const override { return m_IndicesCount; }
		inline const float* GetVertices() const override { return m_Vertices; }
		inline const unsigned int* GetIndices() const override {return m_Indices;}

	private:
		unsigned int m_RendererID;
		unsigned int m_VerticesCount = 24;
		unsigned int m_IndicesCount = 36;

		float m_Vertices[72]{
			//front
			-0.5f, -0.5f, 0.5f,//0
			 0.5f, -0.5f, 0.5f,//1
			 0.5f,  0.5f, 0.5f,//2
			-0.5f,  0.5f, 0.5f,//3

			//back
			-0.5f, -0.5f, -0.5f, //4
			 0.5f, -0.5f, -0.5f, //5
			 0.5f,  0.5f, -0.5f, //6
			-0.5f,  0.5f, -0.5f, //7

			//left
			-0.5f, -0.5f, 0.5f, //8
			-0.5f,  0.5f,  0.5f, //9
			-0.5f,  0.5f, -0.5f, //10
			-0.5f, -0.5f, -0.5f, //11

			//right
			 0.5f, -0.5f,  0.5f, //12
			 0.5f, -0.5f, -0.5f, //13
			 0.5f,  0.5f, -0.5f, //14
			 0.5f,  0.5f,  0.5f, //15

			//top
			 0.5f,  0.5f,  0.5f, //16
			 0.5f,  0.5f, -0.5f, //17
			-0.5f,  0.5f, -0.5f, //18
			-0.5f,  0.5f,  0.5f, //19

			//bottom
			-0.5f, -0.5f,  0.5f, //20
			-0.5f, -0.5f, -0.5f, //21
			 0.5f, -0.5f, -0.5f, //22
			 0.5f, -0.5f,  0.5f  //23
		};
		unsigned int m_Indices[36]{
			 0,  1,  2,  2,  3,  0, //front
			 4,  7,  6,  6,  5,  4, //back
			 8,  9, 10, 10, 11,  8, //left
			12, 13, 14, 14, 15, 12, //right
			16, 17, 18, 18, 19, 16, //top
			20, 21, 22, 22, 23, 20  //bottom
		};
	};
}
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
		
		glm::vec4& GetColor() override { return m_Color; }
		void SetTexture(const std::string& file_path);

		virtual void ReCalculateModelMat() override;

		virtual inline unsigned int GetVerticesCount() const override { return m_VerticesCount; }
		virtual inline unsigned int GetIndicesCount() const override { return m_IndicesCount; }
		virtual inline const float* GetVertices() const override { return vertices; }
		virtual inline const unsigned int* GetIndices() const override { return indices; }
		inline unsigned int& GetRendererID() { return m_RendererID; };
	private:
		unsigned int m_RendererID;
		unsigned int m_VerticesCount = 24;
		unsigned int m_IndicesCount = 36;
		glm::vec4 m_Color;

		float* vertices;
		unsigned int* indices;
	};
}
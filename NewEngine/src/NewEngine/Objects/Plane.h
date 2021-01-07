#pragma once
#include "Object.h"

namespace engine
{
	class Plane:public Object
	{
	public:
		Plane(glm::vec4 color = glm::vec4(1.0f), glm::vec3 translation = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));
		Plane(const std::string& file_path, glm::vec3 translation = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));
		~Plane();

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
		unsigned int m_VerticesCount = 4;
		unsigned int m_IndicesCount = 6;
		glm::vec4 m_Color;

		float* vertices;
		unsigned int* indices;
	};
}

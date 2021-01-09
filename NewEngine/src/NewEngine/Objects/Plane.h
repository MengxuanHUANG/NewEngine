#pragma once
#include "Object.h"

#include <memory>
#include <vector>
#include <string>

namespace engine
{
	class Plane:public Object
	{
	public:
		Plane();
		Plane(glm::vec4 color = glm::vec4(1.0f), glm::vec3 translation = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));
		Plane(const std::string& file_path, glm::vec3 translation = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));
		~Plane();

		glm::vec4& GetColor() override { return m_Color; }
		void AddMaterial(const std::shared_ptr<Material>& material);

		virtual void ReCalculateModelMat() override;

		virtual inline std::vector<std::shared_ptr<Material> >& GetMaterial() override { return m_Materials; }
		virtual inline  unsigned int GetMaterialCount() const override { return m_Materials.size(); }
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
		std::vector<std::shared_ptr<Material> > m_Materials;
	};
}

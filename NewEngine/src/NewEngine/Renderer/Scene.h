#pragma once

#include "NewEngine/Objects/Object.h"
#include "NewEngine/Objects/Light.h"

#include "NewEngine/Camera/PerspectiveCamera.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "Texture.h"

#include <string>
#include <vector>
#include <memory>

namespace engine
{
	class Scene
	{
	public:
		Scene(const std::string& objectShaderPath, const std::string& lightShaderPath, const PerspectiveCamera& camera);
		~Scene();

		void Draw();
		unsigned int AddObject(const Object& object);
		unsigned int AddLight(const Light& light);

		void RemoveObject(unsigned int index);
		void RemoveLight(unsigned int index);
		void FlushObject();
		void FlushLight();

	private:
		unsigned int m_ObjectVerticesCount;
		unsigned int m_ObjectIndicesCount;
		unsigned int m_LightVerticesCount;
		unsigned int m_LightIndicesCount;

		std::shared_ptr<VertexBuffer> m_ObjectVB;
		std::shared_ptr<IndexBuffer> m_ObjectIB;
		std::shared_ptr<VertexArray> m_ObjectVA;
		std::shared_ptr<Shader> m_ObjectShader;

		std::shared_ptr<VertexBuffer> m_LightVB;
		std::shared_ptr<IndexBuffer> m_LightIB;
		std::shared_ptr<VertexArray> m_LightVA;
		std::shared_ptr<Shader> m_LightShader;

		std::vector<const Object*> m_Objects;
		std::vector<const Light*> m_Lights;

		Light m_SignleLight;

		const PerspectiveCamera& m_Camera;
	};
}
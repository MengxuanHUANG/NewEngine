#include "pch.h"
#include "Scene.h"

#include "RenderCommand.h"

namespace engine
{
	Scene::Scene(const std::string& objectShaderPath, const std::string& lightShaderPath, PerspectiveCamera& camera)
		:m_Camera(camera), m_ObjectVerticesCount(0), m_ObjectIndicesCount(0), m_LightVerticesCount(0), m_LightIndicesCount(0)
	{
		m_Colors = nullptr;
		m_Models = nullptr;
		m_ObjectShader = std::shared_ptr<Shader>(Shader::CreateShader(objectShaderPath));
		m_LightShader = std::shared_ptr<Shader>(Shader::CreateShader(lightShaderPath));
	}
	Scene::~Scene()
	{
		if (m_Colors)
		{
			delete[] m_Colors;
		}
		if (m_Models)
		{
			delete[] m_Models;
		}
	}
	
	void Scene::OnUpdate()
	{
		if (m_Colors != nullptr)
		{
			delete[] m_Colors;
		}
		m_Colors = new float[4 * m_Objects.size()];
		if (m_Models != nullptr)
		{
			delete[] m_Models;
		}
		m_Models = new float[16 * m_Objects.size()];

		for (int index = 0; index < m_Objects.size(); index++)
		{
			std::shared_ptr<Object> obj = m_Objects[index];
			obj->ReCalculateModelMat();
			m_Colors[index * 4] = obj->GetColor().x;
			m_Colors[1 + index * 4] = obj->GetColor().y;
			m_Colors[2 + index * 4] = obj->GetColor().z;
			m_Colors[3 + index * 4] = obj->GetColor().w;

			for (int i = 0; i < 16; i++)
			{
				m_Models[i + index * 16] = obj->GetModelMat()[i / 4][i % 4];
			}
		}
	}

	void Scene::Draw()
	{
		m_ObjectShader->Bind();
		m_ObjectShader->SetUniformFloat4("u_LightColor", m_SignleLight->GetColor());
		m_ObjectShader->SetUniformFloat3("u_LightPos", m_SignleLight->GetPosition());
		m_ObjectShader->SetUniformFloat3("u_ViewPos", m_Camera.GetPosition());
		m_ObjectShader->SetUniformFloat("u_SpecularStrength", 2.0f);
		m_ObjectShader->SetUniformArrayMat4f("u_Models", m_Objects.size(), m_Models);
		m_ObjectShader->SetUniformMat4("u_View", m_Camera.GetViewMatrix());
		m_ObjectShader->SetUniformMat4("u_Projection", m_Camera.GetProjectionMatrix());
		m_ObjectShader->SetUniformArray4f("u_Color", m_Objects.size(), m_Colors);
		m_ObjectVA->Bind();
		m_ObjectIB->Bind();
		RenderCommand::Draw(m_ObjectIndicesCount);

		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_SignleLight->GetPosition());
		model = glm::scale(model, glm::vec3(0.1));
		
		m_LightShader->Bind();
		m_LightShader->SetUniformFloat4("u_Color", m_SignleLight->GetColor());
		m_LightShader->SetUniformMat4("u_Model", model);
		m_LightShader->SetUniformMat4("u_View", m_Camera.GetViewMatrix());
		m_LightShader->SetUniformMat4("u_Projection", m_Camera.GetProjectionMatrix());
		m_LightVA->Bind();
		m_LightIB->Bind();
		RenderCommand::Draw(m_LightIndicesCount);
	}
	unsigned int Scene::AddObject(const std::shared_ptr<Object>& object)
	{
		m_Objects.emplace_back(object);
		m_ObjectVerticesCount += object->GetVerticesCount();
		m_ObjectIndicesCount += object->GetIndicesCount();
		return m_Objects.size();
	}
	unsigned int Scene::AddLight(const std::shared_ptr<Light>& light)
	{
		m_SignleLight = light;
		m_LightVerticesCount += light->GetVerticesCount();
		m_LightIndicesCount += light->GetIndicesCount();
		return 0;
	}
	void Scene::RemoveObject(unsigned int index)
	{
		m_Objects.erase(m_Objects.begin() + index);
	}
	void Scene::RemoveLight(unsigned int index)
	{
		m_Lights.erase(m_Lights.begin() + index);
	}
	void Scene::FlushObject()
	{
		if (m_Colors != nullptr)
		{
			delete[] m_Colors;
		}
		m_Colors = new float[4 * m_Objects.size()];
		if (m_Models != nullptr)
		{
			delete[] m_Models;
		}
		m_Models = new float[16 * m_Objects.size()];

		const int vertexStride = 10;
		float* vertices = new float[m_ObjectVerticesCount * vertexStride]();
		unsigned int* indices = new unsigned int[m_ObjectIndicesCount]();

		unsigned int vOffset = 0;
		unsigned int iOffset = 0;
		for (int index = 0; index < m_Objects.size(); index++)
		{
			std::shared_ptr<Object> obj = m_Objects[index];
			m_Colors[index * 4] = obj->GetColor().x;
			m_Colors[1 + index * 4] = obj->GetColor().y;
			m_Colors[2 + index * 4] = obj->GetColor().z;
			m_Colors[3 + index * 4] = obj->GetColor().w;
			
			for (int i = 0; i < 16; i++)
			{
				m_Models[i + index * 16] = obj->GetModelMat()[i/4][i%4];
			}

			//vertices
			for (int i = 0; i < obj->GetVerticesCount(); i++)
			{
				for (int j = 0; j < 9; j++)
				{
					vertices[j + (i + vOffset) * vertexStride] = obj->GetVertices()[j + i * 9];
				}
				vertices[9 + (i + vOffset) * vertexStride] = (float)index;
			}
			//indices
			for (int i = 0; i < obj->GetIndicesCount(); ++i)
			{
				indices[iOffset + i] = obj->GetIndices()[i] + vOffset;
			}
			vOffset += obj->GetVerticesCount();
			iOffset += obj->GetIndicesCount();
		}
		m_ObjectVB = std::shared_ptr<VertexBuffer>(VertexBuffer::CreateVertexBuffer(vertices, m_ObjectVerticesCount * vertexStride * sizeof(float)));
		m_ObjectIB = std::shared_ptr<IndexBuffer>(IndexBuffer::CreateIndexBuffer(indices, m_ObjectIndicesCount * sizeof(unsigned int)));

		delete[]vertices;
		delete[]indices;

		m_ObjectVA = std::shared_ptr<VertexArray>(VertexArray::CreateVertexArray());

		VertexBufferLayout* layout = VertexBufferLayout::CreateBufferLayout();
		layout->Push(DataType::FLOAT, 3);
		layout->Push(DataType::FLOAT, 3);
		layout->Push(DataType::FLOAT, 2);
		layout->Push(DataType::FLOAT, 1);
		layout->Push(DataType::FLOAT, 1);
		m_ObjectVA->SetLayout(*m_ObjectVB, *layout);
		delete layout;
	}
	void Scene::FlushLight()
	{
		m_LightVB = std::shared_ptr<VertexBuffer>(VertexBuffer::CreateVertexBuffer(m_SignleLight->GetVertices(), m_SignleLight->GetVerticesCount() * 3 * sizeof(float)));
		m_LightIB = std::shared_ptr<IndexBuffer>(IndexBuffer::CreateIndexBuffer(m_SignleLight->GetIndices(), m_SignleLight->GetIndicesCount() * sizeof(unsigned int)));
		m_LightVA = std::shared_ptr<VertexArray>(VertexArray::CreateVertexArray());

		//m_LightCount = sizeof(m_SignleLight.GetIndices())/sizeof(unsigned int);

		VertexBufferLayout* layout = VertexBufferLayout::CreateBufferLayout();
		layout->Push(DataType::FLOAT, 3);
		m_LightVA->SetLayout(*m_LightVB, *layout);
		delete layout;
	}
}
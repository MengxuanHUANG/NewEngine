#include "pch.h"
#include "Scene.h"

#include "RenderCommand.h"

namespace engine
{
	Scene::Scene(const std::string& objectShaderPath, const std::string& lightShaderPath, const PerspectiveCamera& camera)
		:m_Camera(camera), m_ObjectVerticesCount(0), m_ObjectIndicesCount(0), m_LightVerticesCount(0), m_LightIndicesCount(0)
	{
		m_ObjectShader = std::shared_ptr<Shader>(Shader::CreateShader(objectShaderPath));
		m_LightShader = std::shared_ptr<Shader>(Shader::CreateShader(lightShaderPath));
	}
	Scene::~Scene()
	{
	}
	
	void Scene::Draw()
	{
		m_ObjectShader->Bind();
		m_ObjectShader->SetUniformFloat4("u_LightColor", m_SignleLight->GetColor());
		m_ObjectShader->SetUniformFloat3("u_LightPos", m_SignleLight->GetPosition());
		m_ObjectShader->SetUniformFloat3("u_ViewPos", m_Camera.GetPosition());
		m_ObjectShader->SetUniformFloat("u_SpecularStrength", 1.5);
		m_ObjectShader->SetUniformMat4("u_View", m_Camera.GetViewMatrix());
		m_ObjectShader->SetUniformMat4("u_Projection", m_Camera.GetProjectionMatrix());
		m_ObjectVA->Bind();
		m_ObjectIB->Bind();
		RenderCommand::Draw(m_ObjectIndicesCount);

		m_LightShader->Bind();
		m_LightShader->SetUniformFloat4("u_Color", m_SignleLight->GetColor());
		m_LightShader->SetUniformMat4("u_View", m_Camera.GetViewMatrix());
		m_LightShader->SetUniformMat4("u_Projection", m_Camera.GetProjectionMatrix());
		m_LightVA->Bind();
		m_LightIB->Bind();
		RenderCommand::Draw(m_LightIndicesCount);
	}
	unsigned int Scene::AddObject(const Object& object)
	{
		m_Objects.emplace_back(&object);
		m_ObjectVerticesCount += object.GetVerticesCount();
		m_ObjectIndicesCount += object.GetIndicesCount();
		return m_Objects.size();
	}
	unsigned int Scene::AddLight(Light& light)
	{
		m_SignleLight = &light;
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
		float* vertices = new float[m_ObjectVerticesCount];
		unsigned int* indices = new unsigned int[m_ObjectIndicesCount];

		unsigned int vOffset = 0;
		unsigned int iOffset = 0;
		for (const Object* obj : m_Objects)
		{
			for (int i = 0; i < obj->GetVerticesCount(); i++)
			{
				for (int j = 0; j < 13; j++)
				{
					vertices[j + (i + vOffset) * 13] = obj->GetVertices()[j + i * 13];
				}
			}

			for (int i = 0; i < obj->GetIndicesCount(); ++i)
			{
				indices[iOffset + i] = obj->GetIndices()[i];
			}
			vOffset += obj->GetVerticesCount();
			iOffset += obj->GetIndicesCount();
		}
		m_ObjectVB = std::shared_ptr<VertexBuffer>(VertexBuffer::CreateVertexBuffer(vertices, sizeof(vertices)));
		m_ObjectIB = std::shared_ptr<IndexBuffer>(IndexBuffer::CreateIndexBuffer(indices, sizeof(indices)));
		m_ObjectVA = std::shared_ptr<VertexArray>(VertexArray::CreateVertexArray());

		VertexBufferLayout* layout = VertexBufferLayout::CreateBufferLayout();
		layout->Push(DataType::FLOAT, 3);
		layout->Push(DataType::FLOAT, 3);
		layout->Push(DataType::FLOAT, 4);
		layout->Push(DataType::FLOAT, 2);
		layout->Push(DataType::FLOAT, 1);
		m_ObjectVA->SetLayout(*m_ObjectVB, *layout);
		delete[] vertices;
		delete[] indices;
		delete layout;
	}
	void Scene::FlushLight()
	{
		m_LightVB = std::shared_ptr<VertexBuffer>(VertexBuffer::CreateVertexBuffer(m_SignleLight->GetVertices(), sizeof(m_SignleLight->GetVertices())));
		m_LightIB = std::shared_ptr<IndexBuffer>(IndexBuffer::CreateIndexBuffer(m_SignleLight->GetIndices(), sizeof(m_SignleLight->GetIndices())));
		m_LightVA = std::shared_ptr<VertexArray>(VertexArray::CreateVertexArray());

		//m_LightCount = sizeof(m_SignleLight.GetIndices())/sizeof(unsigned int);

		VertexBufferLayout* layout = VertexBufferLayout::CreateBufferLayout();
		layout->Push(DataType::FLOAT, 3);
		m_LightVA->SetLayout(*m_LightVB, *layout);
		delete layout;
	}
}
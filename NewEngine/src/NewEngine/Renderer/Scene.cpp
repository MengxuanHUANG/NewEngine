#include "pch.h"
#include "Scene.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "RenderCommand.h"

namespace engine
{
	Scene::Scene(const std::string& objectShaderPath, const std::string& lightShaderPath, PerspectiveCamera& camera)
		:m_Camera(camera), m_ObjectVerticesCount(0), m_ObjectIndicesCount(0), m_LightVerticesCount(0), m_LightIndicesCount(0)
	{
		m_ObjectShader = std::shared_ptr<Shader>(Shader::CreateShader(objectShaderPath));
		m_LightShader = std::shared_ptr<Shader>(Shader::CreateShader(lightShaderPath));
	}
	Scene::~Scene()
	{
		if (m_Models)
		{
			delete[] m_Models;
		}
		if (m_NormalMatrixes != nullptr)
		{
			delete[] m_NormalMatrixes;
		}
	}
	
	void Scene::OnUpdate()
	{
		if (m_Models != nullptr)
		{
			delete[] m_Models;
		}
		m_Models = new float[16 * m_Objects.size()];
		if (m_NormalMatrixes != nullptr)
		{
			delete[] m_NormalMatrixes;
		}
		m_NormalMatrixes = new float[16 * m_Objects.size()];
		for (int index = 0; index < m_Objects.size(); index++)
		{
			m_Objects[index]->ReCalculateModelMat();
			for (int i = 0; i < 16; i++)
			{
				m_Models[i + index * 16] = m_Objects[index]->GetModelMat()[i / 4][i % 4];
			}
			glm::mat4 normalMat = glm::transpose(glm::inverse(m_Objects[index]->GetModelMat()));
			for (int i = 0; i < 16; i++)
			{
				m_NormalMatrixes[i + index * 16] = normalMat[i / 4][i % 4];
			}
		}
	}

	void Scene::Draw()
	{
		m_ObjectShader->Bind();
		unsigned int* textures = new unsigned int[m_Textures.size() + m_Objects.size()]();
		for (int i = 0; i < m_Textures.size(); i++)
		{
			textures[i] = m_Textures[i]->GetRendererID();
		}
		for (int i = 0; i < m_SpecularTextures.size(); i++)
		{
			textures[m_Textures.size() + i] = m_SpecularTextures[i]->GetRendererID();
		}
		RenderCommand::BindTextures(0, m_Textures.size() + m_Objects.size(), textures);

		delete[] textures;

		unsigned int mOffset = 0;

		for (int i = 0; i < m_Objects.size(); i++)
		{
			for (int j = 0; j < m_Objects[i]->GetMaterialCount(); j++)
			{
				std::stringstream ss;
				ss << "u_Materials[" << mOffset + j << "].";
				m_ObjectShader->SetUniformFloat(ss.str().append("shininess"), m_Objects[i]->GetMaterial()[j]->shininess);
				m_ObjectShader->SetUniformFloat(ss.str().append("diffuse"), j + mOffset);
				m_ObjectShader->SetUniformFloat(ss.str().append("specular"), m_Textures.size() + j + mOffset);
			}
			mOffset += m_Objects[i]->GetMaterialCount();
		}
		
		m_ObjectShader->SetUniformFloat3("u_Light.position", m_SignleLight->GetPosition());
		m_ObjectShader->SetUniformFloat3("u_Light.ambient", m_SignleLight->GetStrength() * m_SignleLight->GetAmbient() * glm::vec3(m_SignleLight->GetColor()));
		m_ObjectShader->SetUniformFloat3("u_Light.diffuse", m_SignleLight->GetStrength() * m_SignleLight->GetDiffuse() * glm::vec3(m_SignleLight->GetColor()));
		m_ObjectShader->SetUniformFloat3("u_Light.specular", m_SignleLight->GetStrength() * m_SignleLight->GetSpecular() * glm::vec3(m_SignleLight->GetColor()));

		m_ObjectShader->SetUniformFloat3("u_ViewPos", m_Camera.GetPosition());
		m_ObjectShader->SetUniformArrayMat4f("u_Models", m_Objects.size(), m_Models);
		
		m_ObjectShader->SetUniformArrayMat4f("u_NormalMat", m_Objects.size(), m_NormalMatrixes);
		m_ObjectShader->SetUniformMat4("u_View", m_Camera.GetViewMatrix());
		m_ObjectShader->SetUniformMat4("u_Projection", m_Camera.GetProjectionMatrix());
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
		if (m_Models != nullptr)
		{
			delete[] m_Models;
		}
		m_Models = new float[16 * m_Objects.size()];
		if (m_NormalMatrixes != nullptr)
		{
			delete[] m_NormalMatrixes;
		}
		m_NormalMatrixes = new float[16 * m_Objects.size()];
		
		const int vertexStride = 10;
		
		float* vertices = new float[m_ObjectVerticesCount * vertexStride]();
		unsigned int* indices = new unsigned int[m_ObjectIndicesCount]();

		unsigned int vOffset = 0;
		unsigned int iOffset = 0;
		unsigned int mOffset = 0;
		for (int index = 0; index < m_Objects.size(); index++)
		{
			//Model Matrix
			for (int i = 0; i < 16; i++)
			{
				m_Models[i + index * 16] = m_Objects[index]->GetModelMat()[i/4][i%4];
			}
			//Normal Matrix
			glm::mat4 normalMat = glm::transpose(glm::inverse(m_Objects[index]->GetModelMat()));
			for (int i = 0; i < 16; i++)
			{
				m_NormalMatrixes[i + index * 16] = normalMat[i / 4][i % 4];
			}
			//Textures
			for (int i = 0; i < m_Objects[index]->GetMaterialCount(); i++)
			{
				m_Textures.emplace_back(std::shared_ptr<Texture>(Texture::CreateTexture(m_Objects[index]->GetMaterial()[i]->diffuse)));
				m_SpecularTextures.emplace_back(std::shared_ptr<Texture>(Texture::CreateTexture(m_Objects[index]->GetMaterial()[i]->specular)));
			}
			//vertices
			for (int i = 0; i < m_Objects[index]->GetVerticesCount(); i++)
			{
				for (int j = 0; j < 8; j++)
				{
					vertices[j + (i + vOffset) * vertexStride] = m_Objects[index]->GetVertices()[j + i * 9];
				}
				vertices[8 + (i + vOffset) * vertexStride] = m_Objects[index]->GetVertices()[8 + i * 9] + (float)mOffset;
				vertices[9 + (i + vOffset) * vertexStride] = (float)index;
			}
			//indices
			for (int i = 0; i < m_Objects[index]->GetIndicesCount(); ++i)
			{
				indices[iOffset + i] = m_Objects[index]->GetIndices()[i] + vOffset;
			}
			mOffset += m_Objects[index]->GetMaterialCount();
			vOffset += m_Objects[index]->GetVerticesCount();
			iOffset += m_Objects[index]->GetIndicesCount();
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
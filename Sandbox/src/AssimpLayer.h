#pragma once
#include "NewEngine.h"

#include <string>
#include <windows.h>
#include <memory>

using namespace engine;

class AssimpLayer : public Layer
{
public:
	AssimpLayer(const std::string& name = "Assimp Lyer")
		:Layer(name), m_PerspectiveCamera(45.0f,
			(float)(Application::GetApplication()->GetWindow()->GetWidth()) / (float)(Application::GetApplication()->GetWindow()->GetHeight()), 
			1.0f, 100.0f, glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f)
	{
		float vertices[] = {
			-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
			 0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f
		};

		unsigned int indices[] = {0, 1, 2};

		m_VB = std::shared_ptr<VertexBuffer>(VertexBuffer::CreateVertexBuffer(vertices, sizeof(vertices)));
		m_IB = std::shared_ptr<IndexBuffer>(IndexBuffer::CreateIndexBuffer(indices, sizeof(indices)));

		m_Shader = std::shared_ptr<Shader>(Shader::CreateShader("G://GameEngine//NewEngine//NewEngine//res//shaders//assimp.glsl"));

		VertexBufferLayout* layout = VertexBufferLayout::CreateBufferLayout();
		layout->Push(DataType::FLOAT, 3);
		layout->Push(DataType::FLOAT, 4);

		m_VA = std::shared_ptr<VertexArray>(VertexArray::CreateVertexArray());

		m_VA->SetLayout(*m_VB, *layout);
		delete layout;
	}
	~AssimpLayer()
	{

	}
	void OnUpdate() override
	{
		m_Shader->Bind();
		m_Shader->SetUniformMat4("u_Projection", m_PerspectiveCamera.GetCamera().GetProjectionMatrix());
		m_Shader->SetUniformMat4("u_View", m_PerspectiveCamera.GetCamera().GetViewMatrix());
		m_Shader->SetUniformMat4("u_Model", glm::mat4(1.0f));
		m_VA->Bind();
		m_IB->Bind();

		RenderCommand::Draw(3);
	}

	void OnImGuiRender() override
	{

	}

	void OnEvent(Event& event) override
	{
		m_PerspectiveCamera.OnEvent(event);
	}

private:

	std::shared_ptr<VertexBuffer> m_VB;
	std::shared_ptr<IndexBuffer> m_IB;
	std::shared_ptr<VertexArray> m_VA;

	std::shared_ptr<Shader> m_Shader;

	PerspectiveCameraController m_PerspectiveCamera;
};
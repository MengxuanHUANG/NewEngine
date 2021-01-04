#pragma once
#include "NewEngine.h"

#include <string>
#include <windows.h>

using namespace engine;

static const std::string shader_path = "G://GameEngine//NewEngine//NewEngine//res//shaders//";
static const std::string texture_path = "G://GameEngine//NewEngine//NewEngine//res//textures//";

class ExampleLayer : public engine::Layer
{
public:
	ExampleLayer(const std::string& name = "Example Lyer")
		:Layer(name), 
		m_PerspectiveCam(45.0f, 
			(float)(Application::GetApplication()->GetWindow()->GetWidth())/(float)(Application::GetApplication()->GetWindow()->GetHeight()), 
			1.0f, 100.0f, m_CamPos)
	{
		float vertices[] =
		{
			//front
			-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //0
			 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //1
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //2
			-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //3

			//back
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //4
			 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //5
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //6
			-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //7

			//left
			-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //8
			-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //9
			-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //10
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //11

			//right
			 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //12
			 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //13
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //14
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //15

			//top
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //16
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //17
			-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //18
			-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, //19

			//bottom
			-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //20
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //21
			 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //22
			 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  //23
		};
		unsigned int indices[] =
		{
			 0,  1,  2,  2,  3,  0, //front
			 4,  7,  6,  6,  5,  4, //back
			 8,  9, 10, 10, 11,  8, //left
			12, 13, 14, 14, 15, 12, //right
			16, 17, 18, 18, 19, 16, //top
			20, 21, 22, 22, 23, 20  //bottom
		};

		m_VB = VertexBuffer::CreateVertexBuffer(vertices, sizeof(vertices));
		m_IB = IndexBuffer::CreateIndexBuffer(indices, sizeof(indices));
		m_VA = VertexArray::CreateVertexArray();
		m_Shader = Shader::CreateShader(shader_path + "Basic.glsl");
		m_Shader->Bind();

		VertexBufferLayout* layout = VertexBufferLayout::CreateBufferLayout();
		layout->Push(DataType::FLOAT, 3);
		layout->Push(DataType::FLOAT, 4);
		layout->Push(DataType::FLOAT, 2);
		m_VA->SetLayout(*m_VB, *layout);
		delete layout;

		m_Texture = Texture::CreateTexture(texture_path + "Checkerboard.png");
		m_Shader->SetUniformFloat("u_Texture", 0);

		//Light
		float lightVertices[] =
		{
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
			- 0.5f, -0.5f, 0.5f, //8
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
		unsigned int lightIndices[] =
		{
			 0,  1,  2,  2,  3,  0, //front
			 4,  7,  6,  6,  5,  4, //back
			 8,  9, 10, 10, 11,  8, //left
			12, 13, 14, 14, 15, 12, //right
			16, 17, 18, 18, 19, 16, //top
			20, 21, 22, 22, 23, 20  //bottom
		};
		m_LightVB = VertexBuffer::CreateVertexBuffer(lightVertices, sizeof(lightVertices));
		m_LightIB = IndexBuffer::CreateIndexBuffer(lightIndices, sizeof(lightIndices));
		m_LightShader = Shader::CreateShader(shader_path + "Light.glsl");
		m_LightShader->Bind();

		m_LightVA = VertexArray::CreateVertexArray();

		layout = VertexBufferLayout::CreateBufferLayout();
		layout->Push(DataType::FLOAT, 3);
		m_LightVA->SetLayout(*m_LightVB, *layout);
		delete layout;

		m_TimeStart = GetTickCount();
	}
	~ExampleLayer()
	{
		delete m_VB;
		delete m_IB;
		delete m_VA;
		delete m_Shader;
		delete m_Texture;

		delete m_LightVB;
		delete m_LightIB;
		delete m_LightShader;
		delete m_LightVA;
	}
	void OnEvent(Event& event) override
	{
		m_PerspectiveCam.OnEvent(event);
	}
	void OnUpdate() override
	{
		m_PerspectiveCam.SetPosition(m_CamPos);
		float width = Application::GetApplication()->GetWindow()->GetWidth();
		float height = Application::GetApplication()->GetWindow()->GetHeight();

		m_TimeEnd = GetTickCount();
		
		float time = (float)(m_TimeEnd - m_TimeStart) / 1000;

		//Model Matrix
		glm::mat4 model(1.0f);
		//model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		m_Shader->Bind();
		m_Shader->SetUniformMat4("u_Model", model);
		m_Shader->SetUniformMat4("u_View", m_PerspectiveCam.GetCamera().GetViewMatrix());
		m_Shader->SetUniformMat4("u_Projection", m_PerspectiveCam.GetCamera().GetProjectionMatrix());

		m_VA->Bind();
		m_IB->Bind();
		RenderCommand::Draw(36);

		glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
		model = glm::translate(glm::mat4(1.0f), lightPos);
		model = glm::scale(model, glm::vec3(0.2));

		m_LightShader->Bind();
		m_LightShader->SetUniformMat4("u_Model", model);
		m_LightShader->SetUniformMat4("u_View", m_PerspectiveCam.GetCamera().GetViewMatrix());
		m_LightShader->SetUniformMat4("u_Projection", m_PerspectiveCam.GetCamera().GetProjectionMatrix());
		m_LightVA->Bind();
		m_LightIB->Bind();
		RenderCommand::Draw(36);
	}
	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::SetWindowFontScale(2.0f);

		ImGui::SliderFloat3("Camera Position", &m_CamPos.x, -20, 20);
		if (ImGui::Button("Reset Camera"))
		{
			m_CamPos = glm::vec3(0.0f, 0.0f, 10.0f);
			m_PerspectiveCam.SetZoomLevel(45.0f);
			m_PerspectiveCam.SetRotation(-90.0f, 0.0f);
		}
		ImGui::End();
	}
private:
	//TODO:remove
	VertexBuffer* m_VB = nullptr;
	IndexBuffer* m_IB = nullptr;
	VertexArray* m_VA = nullptr;
	Shader* m_Shader = nullptr;
	Texture* m_Texture = nullptr;

	VertexBuffer* m_LightVB = nullptr;
	IndexBuffer* m_LightIB = nullptr;
	Shader* m_LightShader = nullptr;
	VertexArray* m_LightVA = nullptr;

	PerspectiveCameraController m_PerspectiveCam;

	DWORD m_TimeStart, m_TimeEnd;

	glm::vec3 m_CamPos = { 0.0f, 0.0f, 10.0f };
};
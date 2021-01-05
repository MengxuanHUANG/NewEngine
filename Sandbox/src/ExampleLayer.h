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
		:Layer(name), m_TimeStart(GetTickCount()),
		m_PerspectiveCam(45.0f, 
			(float)(Application::GetApplication()->GetWindow()->GetWidth())/(float)(Application::GetApplication()->GetWindow()->GetHeight()), 
			1.0f, 100.0f, m_CamPos, glm::vec3(0.0f, 1.0f, 0.0f), -66.5f, -16.6f)
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
		float vertices_temp[] =
		{
			//front
			-0.5f, -0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  0.0f,  1.0f, //0
			 0.5f, -0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  0.0f,  1.0f, //1
			 0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  0.0f,  1.0f, //2
			-0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  0.0f,  1.0f, //3

			//back
			-0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  0.0f, -1.0f, //4
			 0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  0.0f, -1.0f, //5
			 0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  0.0f, -1.0f, //6
			-0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  0.0f, -1.0f, //7

			//left
			-0.5f, -0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 1.0f, -1.0f,  0.0f,  0.0f, //8
			-0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 1.0f, -1.0f,  0.0f,  0.0f, //9
			-0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 1.0f, -1.0f,  0.0f,  0.0f, //10
			-0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 1.0f, -1.0f,  0.0f,  0.0f, //11

			//right
			 0.5f, -0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  1.0f,  0.0f,  1.0f, //12
			 0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  1.0f,  0.0f,  1.0f, //13
			 0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  1.0f,  0.0f,  1.0f, //14
			 0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  1.0f,  0.0f,  1.0f, //15

			//top
			 0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  1.0f,  0.0f, //16
			 0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  1.0f,  0.0f, //17
			-0.5f,  0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  1.0f,  0.0f, //18
			-0.5f,  0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f,  1.0f,  0.0f, //19

			//bottom
			-0.5f, -0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f, -1.0f,  1.0f, //20
			-0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f, -1.0f,  1.0f, //21
			 0.5f, -0.5f, -0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f, -1.0f,  1.0f, //22
			 0.5f, -0.5f,  0.5f, 1.0f, 0.5f, 0.31f, 1.0f,  0.0f, -1.0f,  1.0f  //23
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

		m_VB = VertexBuffer::CreateVertexBuffer(vertices_temp, sizeof(vertices_temp));
		m_IB = IndexBuffer::CreateIndexBuffer(indices, sizeof(indices));
		m_VA = VertexArray::CreateVertexArray();
		m_Shader = Shader::CreateShader(shader_path + "light_object.glsl");
		m_Shader->Bind();

		VertexBufferLayout* layout = VertexBufferLayout::CreateBufferLayout();
		layout->Push(DataType::FLOAT, 3);
		layout->Push(DataType::FLOAT, 4);
		layout->Push(DataType::FLOAT, 3);
		m_VA->SetLayout(*m_VB, *layout);
		delete layout;

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

		//Plane
		float verticesPlane[] =
		{
			-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.2f, 0.0f, 0.0f, //0
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.2f, 1.0f, 0.0f, //1
			 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.2f, 1.0f, 1.0f, //2
			 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.2f, 0.0f, 1.0f  //3
		};
		unsigned int indicesPlane[] = { 0, 1, 2, 2, 3, 0 };

		m_PlaneVB = VertexBuffer::CreateVertexBuffer(verticesPlane, sizeof(verticesPlane));
		m_PlaneIB = IndexBuffer::CreateIndexBuffer(indicesPlane, sizeof(indicesPlane));
		m_PlaneVA = VertexArray::CreateVertexArray();
		layout = VertexBufferLayout::CreateBufferLayout();
		layout->Push(DataType::FLOAT, 3);
		layout->Push(DataType::FLOAT, 4);
		layout->Push(DataType::FLOAT, 2);
		
		m_PlaneShader = Shader::CreateShader(shader_path + "Basic.glsl");
		m_PlaneShader->Bind();

		m_PlaneVA->SetLayout(*m_PlaneVB, *layout);
		delete layout;
		m_PlaneTexture = Texture::CreateTexture(texture_path + "Checkerboard.png");
		m_PlaneShader->SetUniformFloat("u_Texture", 0);
	}
	~ExampleLayer()
	{
		delete m_VB;
		delete m_IB;
		delete m_VA;
		delete m_Shader;

		delete m_LightVB;
		delete m_LightIB;
		delete m_LightShader;
		delete m_LightVA;

		delete m_PlaneVB;
		delete m_PlaneIB;
		delete m_PlaneVA;
		delete m_PlaneShader;
		delete m_PlaneTexture;
	}
	void OnEvent(Event& event) override
	{
		m_PerspectiveCam.OnEvent(event);
	}
	void OnUpdate() override
	{
		m_PerspectiveCam.SetPosition(m_CamPos);

		m_TimeEnd = GetTickCount();
		
		float time = (float)(m_TimeEnd - m_TimeStart) / 1000;

		//Model Matrix
		glm::mat4 model(1.0f);
		//model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		//model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		m_Shader->Bind();
		m_Shader->SetUniformFloat3("u_LightColor", m_LightColor);
		m_Shader->SetUniformFloat3("u_LightPos", m_LightPos);
		m_Shader->SetUniformFloat3("u_ViewPos", m_CamPos);
		m_Shader->SetUniformFloat("u_SpecularStrength", m_SpecularStrength);
		m_Shader->SetUniformMat4("u_Model", model);
		m_Shader->SetUniformMat4("u_View", m_PerspectiveCam.GetCamera().GetViewMatrix());
		m_Shader->SetUniformMat4("u_Projection", m_PerspectiveCam.GetCamera().GetProjectionMatrix());

		m_VA->Bind();
		m_IB->Bind();
		RenderCommand::Draw(36);

		model = glm::translate(glm::mat4(1.0f), m_LightPos);
		model = glm::scale(model, glm::vec3(0.2));

		m_LightShader->Bind();
		m_LightShader->SetUniformMat4("u_Model", model);
		m_LightShader->SetUniformMat4("u_View", m_PerspectiveCam.GetCamera().GetViewMatrix());
		m_LightShader->SetUniformMat4("u_Projection", m_PerspectiveCam.GetCamera().GetProjectionMatrix());
		m_LightVA->Bind();
		m_LightIB->Bind();
		RenderCommand::Draw(36);

		model = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 1.0f, 10.0f));

		m_PlaneVA->Bind();
		m_PlaneIB->Bind();

		m_PlaneShader->Bind();
		m_PlaneShader->SetUniformMat4("u_Model", model);
		m_PlaneShader->SetUniformMat4("u_View", m_PerspectiveCam.GetCamera().GetViewMatrix());
		m_PlaneShader->SetUniformMat4("u_Projection", m_PerspectiveCam.GetCamera().GetProjectionMatrix());
		
		RenderCommand::Draw(6);
	}
	void OnImGuiRender() override
	{
		ImGui::Begin("NewEngine");
		ImGui::SetWindowFontScale(1.0f);

		ImGui::SliderFloat3("Camera Position", &m_CamPos.x, -5, 10);
		std::stringstream ss;
		ss << "Camera Yaw: " << m_PerspectiveCam.GetCamera().GetYaw()<<"\n";
		ss << "Camera Pitch: " << m_PerspectiveCam.GetCamera().GetPitch();
		ImGui::Text(ss.str().c_str());

		if (ImGui::Button("Reset Camera"))
		{
			m_CamPos = { -1.5f, 1.4f, 3.2f };
			m_PerspectiveCam.SetZoomLevel(45.0f);
			m_PerspectiveCam.SetRotation(-66.5f, -16.6f);
		}
		ImGui::SliderFloat("Specular Strength", &m_SpecularStrength, 0.1, 2.0);
		ImGui::SliderFloat3("Light Position", &m_LightPos.x, -10, 10);
		ImGui::ColorEdit3("Light Color", &m_LightColor.x);
		if (ImGui::Button("Reset Light"))
		{
			m_LightPos = { 1.2f, 1.0f, 2.0f };
			m_LightColor = { 1.0f, 1.0f, 1.0f };
		}
		ImGui::End();
	}
private:
	//cube
	VertexBuffer* m_VB = nullptr;
	IndexBuffer* m_IB = nullptr;
	VertexArray* m_VA = nullptr;
	Shader* m_Shader = nullptr;
	//light
	VertexBuffer* m_LightVB = nullptr;
	IndexBuffer* m_LightIB = nullptr;
	Shader* m_LightShader = nullptr;
	VertexArray* m_LightVA = nullptr;
	//plane
	VertexBuffer* m_PlaneVB = nullptr;
	IndexBuffer* m_PlaneIB = nullptr;
	VertexArray* m_PlaneVA = nullptr;
	Shader* m_PlaneShader = nullptr;
	Texture* m_PlaneTexture = nullptr;

	//camera
	PerspectiveCameraController m_PerspectiveCam;

	DWORD m_TimeStart, m_TimeEnd;

	float m_SpecularStrength = 0.5;
	glm::vec3 m_CamPos = { -1.5f, 1.4f, 3.2f };
	glm::vec3 m_LightPos = { -0.2f, 1.0f, 1.0f };
	glm::vec3 m_LightColor = { 1.0f, 1.0f, 1.0f };
};
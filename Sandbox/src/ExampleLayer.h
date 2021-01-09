#pragma once
#include "NewEngine.h"

#include <string>
#include <windows.h>
#include <memory>

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
			1.0f, 100.0f, glm::vec3(-1.5f, 1.4f, 3.2f), glm::vec3(0.0f, 1.0f, 0.0f), -66.5f, -16.6f)
	{
		m_Scene_1 = std::make_shared<Scene>(shader_path + "light_object.glsl", shader_path + "Light.glsl", m_PerspectiveCam.GetCamera());
		m_Scene_2 = std::make_shared<Scene>(shader_path + "light_object.glsl", shader_path + "Light.glsl", m_PerspectiveCam.GetCamera());
		m_Cube = std::make_shared<Cube>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
		m_Plane = std::make_shared<Plane>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, -0.5f, 0.0f), glm::vec3(-90.0f, 0.0f, 0.0f), glm::vec3(5.0f , 5.0f, 1.0f));
		m_Light = std::make_shared<PointLight>(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec4(1.0f));

		m_Cube->AddMaterial(std::make_shared<Material>(64.0f, texture_path + "container2.png", texture_path + "container2_specular.png"));
		m_Plane->AddMaterial(std::make_shared<Material>(64.0f, texture_path + "Checkerboard.png", texture_path + "Checkerboard.png"));

		m_Scene_1->AddObject(m_Cube);
		m_Scene_1->AddLight(m_Light);

		//m_Scene_1->AddObject(m_Plane);
		m_Scene_2->AddLight(m_Light);

		m_Scene_1->FlushObject();
		m_Scene_1->FlushLight();

		//m_Scene_2->FlushObject();
		//m_Scene_2->FlushLight();
	}
	~ExampleLayer()
	{
	}
	void OnEvent(Event& event) override
	{
		m_PerspectiveCam.OnEvent(event);
	}
	void OnUpdate() override
	{
		m_PerspectiveCam.OnUpdate();

		m_TimeEnd = GetTickCount();
		
		float time = (float)(m_TimeEnd - m_TimeStart) / 1000;
		m_Scene_1->OnUpdate();
		m_Scene_1->Draw();

		//m_Scene_2->OnUpdate();
		//m_Scene_2->Draw();
	}
	void OnImGuiRender() override
	{
		ImGui::Begin("Cube");
		ImGui::SetWindowFontScale(1.0f);

		//ImGui::SliderFloat3("Cube Position", &(m_Cube->GetTanslate().x), -2.0f, 2.0f);
		ImGui::SliderFloat3("Cube Rotation", &(m_Cube->GetRotation().x), -90.0f, 90.0f);
		//ImGui::SliderFloat3("Cube Scale", &(m_Cube->GetScale().x), 1.0f, 2.0f);

		ImGui::ColorEdit4("Cube Color", &(m_Cube->GetColor().x));
		ImGui::SliderFloat("Cube Shininess", &(m_Cube->GetMaterial()[0]->shininess), 32.0f, 256.0f);

		if (ImGui::Button("Reset Cube"))
		{
			m_Cube->GetTanslate() = { 0.0f, 0.0f, 0.0f };
			m_Cube->GetRotation() = { 0.0f, 0.0f, 0.0f };
			m_Cube->GetScale() = { 1.0f, 1.0f, 1.0f };
			m_Cube->GetColor() = { 1.0f, 1.0f, 1.0f, 1.0f };
		}
		ImGui::End();

		ImGui::Begin("Light");
		ImGui::SliderFloat("Specular Strength", &(m_Light->GetStrength()), 0.1f, 2.0f);
		ImGui::SliderFloat3("Light Position", &(m_Light->GetPosition().x), -3.0f, 3.0f);
		ImGui::ColorEdit4("Light Color", &(m_Light->GetColor().x));
		if (ImGui::Button("Reset Light"))
		{
			m_Light->GetPosition() = { 1.2f, 1.0f, 2.0f };
			m_Light->GetColor() = { 1.0f, 1.0f, 1.0f, 1.0f };
		}
		ImGui::End();

		ImGui::Begin("Camera");
		ImGui::SliderFloat3("Camera Position", &(m_PerspectiveCam.GetCamera().GetPosition().x), -5, 10);
		std::stringstream ss;
		ss << "Camera Yaw: " << m_PerspectiveCam.GetCamera().GetYaw() << "\n";
		ss << "Camera Pitch: " << m_PerspectiveCam.GetCamera().GetPitch();
		ImGui::Text(ss.str().c_str());
		if (ImGui::Button("Reset Camera"))
		{
			m_PerspectiveCam.GetCamera().GetPosition() = { -1.5f, 1.4f, 3.2f };
			m_PerspectiveCam.SetZoomLevel(45.0f);
			m_PerspectiveCam.SetRotation(-66.5f, -16.6f);
		}
		if (ImGui::Button("Top"))
		{
			m_PerspectiveCam.GetCamera().GetPosition() = { 0.0f, 10.0f, 0.0f };
			m_PerspectiveCam.SetZoomLevel(45.0f);
			m_PerspectiveCam.SetRotation(0.0f, -89.0f);
		}
		if (ImGui::Button("Front"))
		{
			m_PerspectiveCam.GetCamera().GetPosition() = { 0.0f, 0.0f, 10.0f };
			m_PerspectiveCam.SetZoomLevel(45.0f);
			m_PerspectiveCam.SetRotation(-90.0f, -0.0f);
		}
		ImGui::End();
	}
private:
	std::shared_ptr<Scene> m_Scene_1;
	std::shared_ptr<Scene> m_Scene_2;
	std::shared_ptr<Cube> m_Cube;
	std::shared_ptr<Plane> m_Plane;
	std::shared_ptr<PointLight> m_Light;

	//camera
	PerspectiveCameraController m_PerspectiveCam;

	DWORD m_TimeStart, m_TimeEnd;
};
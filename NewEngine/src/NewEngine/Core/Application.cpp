#include "pch.h"

#include "Application.h"
#include "Event.h"
#include "NewEngine/Events/ApplicationEvents.h"

#include "NewEngine/Renderer/RenderCommand.h"
#include "NewEngine/ImGui/ImGuiDriver.h"

namespace engine
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
		:m_Running(true)
	{
		MY_ENGINE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		engine::Logger::Init();

		WindowProps props(1280, 960);

		s_Window = Window::WindowCreate(BIND_EVENT_FN(Application::OnEvent), props);

		RenderCommand::Init();
		ImGuiDriver::ImGuiInit();
	}
	Application::~Application()
	{
		delete s_Window;
		RenderCommand::Terminate();
		ImGuiDriver::ImGuiShutdown();
	}
	void Application::Run()
	{
		while (m_Running)
		{
			RenderCommand::ClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

			for (auto layer : m_Layers)
			{
				layer->OnUpdate();
			}
			RenderCommand::Draw(36);
			ImGuiDriver::ImGuiStartFrame();
			
			for (auto layer : m_Layers)
			{
				layer->OnImGuiRender();
			}

			ImGuiDriver::ImGuiEndFrame();
			ImGuiDriver::ImGuiRender();

			//****important****
			s_Window->OnUpdate();
		}
	}
	void Application::OnEvent(Event& event)
	{
		//MY_ENGINE_TRACE("{0}", event);
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
		dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT_FN(Application::OnWindowResized));

		for (auto it = m_Layers.end(); it != m_Layers.begin();)
		{
			(*(--it))->OnEvent(event);
			if (event.m_Handled) break;
		}
	}
	void Application::PushLayer(Layer* layer)
	{
		m_Layers.PushLayer(layer);
	}
	void Application::PushSuperLayer(Layer* layer)
	{
		m_Layers.PushSuperLayer(layer);
	}
	bool Application::OnWindowClosed(Event& event)
	{
		m_Running = false;
		return false;
	}
	bool Application::OnWindowResized(Event& event)
	{
		s_Window->GetGraphicContext()->Resized(0, 0, ((WindowResizedEvent*)&event)->GetWidth(), ((WindowResizedEvent*)&event)->GetHeight());
		return false;
	}
}
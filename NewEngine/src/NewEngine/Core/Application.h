#pragma once
#include "Window.h"
#include "NewEngine/Layer/LayerStack.h"
#include "NewEngine/Renderer/VertexBuffer.h"
#include "NewEngine/Renderer/IndexBuffer.h"
#include "NewEngine/Renderer/VertexArray.h"
#include "NewEngine/Renderer/Shader.h"
#include "NewEngine/Renderer/Texture.h"

namespace engine
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();
		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushSuperLayer(Layer* layer);

		inline Window* GetWindow() const { return s_Window; }
		inline static Application* GetApplication() { return s_Instance; }
	private:
		bool OnWindowClosed(Event& event);
		bool OnWindowResized(Event& event);
	private:
		static Application* s_Instance;
		Window* s_Window;
		LayerStack m_Layers;
		bool m_Running;
	};

	Application* CreateApplication();
}
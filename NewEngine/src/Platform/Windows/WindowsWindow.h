#pragma once

#include "NewEngine/Core/Window.h"
#include "NewEngine/Renderer/GraphicContext.h"

#include <GLFW/glfw3.h>

namespace engine
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(EventCallbackFn& fn, const WindowProps& props);
		~WindowsWindow();

		virtual void OnUpdate() override;
		virtual void SetSync(bool enabled) override;
		virtual inline void SetEventCallback(EventCallbackFn callback) override { m_Data.EventCallback = callback; }

		virtual inline bool IsSync() const override { return m_Data.VSync; }
		virtual inline uint32_t GetWidth() const override { return m_Data.width; }
		virtual inline uint32_t GetHeight() const override { return m_Data.height;}
		virtual inline const std::string& GetTitle() const override { return m_Data.title;}
		virtual inline void* GetNativeWindow() const override { return m_Window;}
		virtual inline GraphicContext* GetGraphicContext() const override { return s_GraphicContext; }
	private:
		void Init(EventCallbackFn& fn, const WindowProps& props);
		void Shutdown();
	private:
		struct WindowData
		{
			uint32_t width, height;
			std::string title;
			bool VSync;

			EventCallbackFn EventCallback;
		};
		WindowData m_Data;
		GraphicContext* s_GraphicContext;
		GLFWwindow* m_Window;
	};
}
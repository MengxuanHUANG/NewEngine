#pragma once

#include "Event.h"
#include "NewEngine/Renderer/GraphicContext.h"

#include <string>
#include <functional>

namespace engine
{

	struct WindowProps
	{
		uint32_t width, height;
		std::string title;

		WindowProps(uint32_t width = 1280, uint32_t height = 960, const std::string& title = "My Engine")
			:width(width), height(height), title(title)
		{
		}
	};
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual void SetSync(bool enabled) = 0;
		virtual void SetEventCallback(EventCallbackFn callback) = 0;
		
		virtual bool IsSync() const = 0;
		virtual inline uint32_t GetWidth() const = 0;
		virtual inline uint32_t GetHeight() const = 0;
		virtual const std::string& GetTitle() const = 0;

		virtual void* GetNativeWindow() const = 0;
		virtual inline GraphicContext* GetGraphicContext() const = 0;
		static Window* WindowCreate(EventCallbackFn fn, const WindowProps& props = WindowProps());
	};
}
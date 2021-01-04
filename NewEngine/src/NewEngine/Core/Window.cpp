#include "pch.h"
#include "Window.h"

#include "Platform/Windows/WindowsWindow.h"

namespace engine
{
	static bool IsWindowCreated = false;
#ifdef  PLATFORM_WINDOWS
	Window* Window::WindowCreate(EventCallbackFn fn, const WindowProps& props)
	{
		return new WindowsWindow(fn, props);
	}
#endif
}
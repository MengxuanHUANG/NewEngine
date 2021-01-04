#include "pch.h"

#include "WindowsWindow.h"
#include "NewEngine/Events/ApplicationEvents.h"
#include "NewEngine/Events/KeyBoardEvents.h"
#include "NewEngine/Events/MouseEvents.h"

namespace engine
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		MY_ENGINE_ERROR("GLFW Error({0}): {1}", error, description);
	}

	WindowsWindow::WindowsWindow(EventCallbackFn& fn, const WindowProps& props)
	{
		Init(fn, props);
	}
	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}
	void WindowsWindow::Init(EventCallbackFn& fn, const WindowProps& props)
	{
		MY_ENGINE_ASSERT(!s_GLFWInitialized, "Windows Window already exits!");

		m_Data.width = props.width;
		m_Data.height = props.height;
		m_Data.title = props.title;
		m_Data.VSync = true;

		SetEventCallback(fn);

		MY_ENGINE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			MY_ENGINE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_Window = glfwCreateWindow((int)props.width, (int)props.height, m_Data.title.c_str(), nullptr, nullptr);

		glfwSetWindowPos(m_Window, 200, 300);
		glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GLFW_TRUE);

		glfwSetWindowUserPointer(m_Window, &m_Data);

		s_GraphicContext = GraphicContext::MakeContext(m_Window);

		s_GraphicContext->Init(m_Data.width, m_Data.height);
		glfwSwapInterval(1);

		//set GLFW call back
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;
			WindowResizedEvent event(width, height);

			data.EventCallback(event);
		});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowClosedEvent event;
			data.EventCallback(event);
		});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent(key, 1);
					break;
				}
			}
		});
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int input_char)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(input_char);
			data.EventCallback(event);
		});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MousePressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double x_Offset, double y_Offset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event({ (float)x_Offset, (float)y_Offset });
			data.EventCallback(event);
		});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x_Pos, double y_Pos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event({ (float)x_Pos, (float)y_Pos });
			data.EventCallback(event);
		});
	}
	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
		delete s_GraphicContext;
	}
	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		s_GraphicContext->SwapBuffers();
	}
	void WindowsWindow::SetSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}
}
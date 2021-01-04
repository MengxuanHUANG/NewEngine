#include "pch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include<GLFW/glfw3.h>

namespace engine
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		:m_WindowHandle(window)
	{
		MY_ENGINE_ASSERT(m_WindowHandle, "Handle is null!");
	}
	OpenGLContext::~OpenGLContext()
	{
	}
	void OpenGLContext::Init(int width, int height)
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MY_ENGINE_ASSERT(status, "Failed to iniitalize Glad!");

		MY_ENGINE_INFO(" Vendor: {0}", glGetString(GL_VENDOR));
		MY_ENGINE_INFO(" Renderer: {0}", glGetString(GL_RENDERER));
		MY_ENGINE_INFO(" Version: {0}", glGetString(GL_VERSION));

		glViewport(0, 0, width, height);
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
	void OpenGLContext::Resized(int posX, int posY, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}
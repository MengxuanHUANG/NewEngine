#include "pch.h"
#include "OpenGLRenderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace engine
{
	OpenGLRenderer3D::OpenGLRenderer3D(int width, int height)
	{
		Init(width, height);
	}
	OpenGLRenderer3D::~OpenGLRenderer3D()
	{
		Terminate();
	}

	void OpenGLRenderer3D::Init(int width, int height)
	{
		bool success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MY_ENGINE_ASSERT(success, "Failed to initialize GLAD");

		glViewport(0, 0, width, height);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRenderer3D::Terminate()
	{
	}
	void OpenGLRenderer3D::ClearColor(glm::vec4 color)
	{
		glClearColor(color.x, color.y, color.z, color.w);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGLRenderer3D::Draw(int count)
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}
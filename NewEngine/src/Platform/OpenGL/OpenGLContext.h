#pragma once

#include "NewEngine/Renderer/GraphicContext.h"

struct GLFWwindow {};

namespace engine
{
	class OpenGLContext: public GraphicContext
	{
	public:
		OpenGLContext(GLFWwindow* window);
		~OpenGLContext();

		virtual void Init(int width, int height) override;
		virtual void SwapBuffers() override;
		virtual void Resized(int posX, int posY, int width, int height) override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}
#include "pch.h"
#include "GraphicContext.h"

#include "Platform/OpenGL/OpenGLContext.h"
#include "RenderCommand.h"

namespace engine
{
	bool GraphicContext::s_Initialized = false;

	GraphicContext* GraphicContext::MakeContext(void* window)
	{
		MY_ENGINE_ASSERT(!GraphicContext::IsInitialized(), "Graphic alreadly exit!");
		s_Initialized = true;

		switch (RenderCommand::GetRendererAPI())
		{
		case RendererAPI::OpenGL:
			return new OpenGLContext((GLFWwindow*)window);

		case RendererAPI::Directx:
		case RendererAPI::None:
		default:
			MY_ENGINE_ASSERT(false, "Undefined Renderer API!");
		}
	}
}
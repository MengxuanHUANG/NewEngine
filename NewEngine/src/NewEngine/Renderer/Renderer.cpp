#include "pch.h"
#include "Renderer.h"

#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRenderer.h"

namespace engine
{
	Renderer3D* Renderer3D::Create3DRenderer(int width, int height)
	{
		switch (RenderCommand::GetRendererAPI())
		{
		case RendererAPI::OpenGL:
			return new OpenGLRenderer3D(width, height);
			break;
		case RendererAPI::Directx:
		case RendererAPI::None:
		default:
			MY_ENGINE_ASSERT(false, "Undefined Renderer API!");
		}
	}
}
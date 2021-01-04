#include "pch.h"
#include "VertexBuffer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "RenderCommand.h"

namespace engine
{
	VertexBuffer* VertexBuffer::CreateVertexBuffer(const void* vertex, unsigned int size)
	{
		switch (RenderCommand::GetRendererAPI())
		{
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertex, size);

		case RendererAPI::Directx:
		case RendererAPI::None:
		default:
			MY_ENGINE_ASSERT(false, "Undefined Renderer API!");
		}
	}
}
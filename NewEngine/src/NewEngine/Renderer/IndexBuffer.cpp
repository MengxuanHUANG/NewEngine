#include "pch.h"
#include "IndexBuffer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "RenderCommand.h"

namespace engine
{
	IndexBuffer* IndexBuffer::CreateIndexBuffer(const void* index, unsigned int size)
	{
		switch (RenderCommand::GetRendererAPI())
		{
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(index, size);

		case RendererAPI::Directx:
		case RendererAPI::None:
		default:
			MY_ENGINE_ASSERT(false, "Undefined Renderer API!");
		}
	}
}



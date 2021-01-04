#include "pch.h"
#include "Texture.h"

#include "Platform/OpenGL/OpenGLTexture.h"
#include "RenderCommand.h"

namespace engine
{
	Texture* Texture::CreateTexture(const std::string& file_path)
	{
		switch (RenderCommand::GetRendererAPI())
		{
		case RendererAPI::OpenGL:
			return new OpenGLTexture(file_path);

		case RendererAPI::Directx:
		case RendererAPI::None:
		default:
			MY_ENGINE_ASSERT(false, "Undefined Renderer API!");
		}
	}

	/*Texture* Texture::CreateTexture(unsigned int width, unsigned int height)
	{
		switch (RenderCommand::GetRendererAPI())
		{
		case RendererAPI::OpenGL:
			return new OpenGLTexture(width, height);

		case RendererAPI::Directx:
		case RendererAPI::None:
		default:
			MY_ENGINE_ASSERT(false, "Undefined Renderer API!");
		}
	}*/
}
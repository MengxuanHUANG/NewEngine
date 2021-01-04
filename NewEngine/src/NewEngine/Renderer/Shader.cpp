#include "pch.h"
#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "RenderCommand.h"

namespace engine
{
	Shader* Shader::CreateShader(const std::string& shader_path)
	{
		switch (RenderCommand::GetRendererAPI())
		{
		case RendererAPI::OpenGL:
			return new OpenGLShader(shader_path);

		case RendererAPI::Directx:
		case RendererAPI::None:
		default:
			MY_ENGINE_ASSERT(false, "Undefined Renderer API!");
		}
	}
}
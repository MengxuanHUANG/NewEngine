#include "pch.h"
#include "ImGuiDriver.h"

#include "NewEngine/Renderer/RenderCommand.h"
#include "Platform/OpenGL/ImGui/OpenGL3ImGuiDriver.h"

namespace engine
{
	ImGuiDriver* ImGuiDriver::s_Instance;
	ImGuiDriver* ImGuiDriver::CreateImGuiDriver()
	{
		switch (RenderCommand::GetRendererAPI())
		{
		case RendererAPI::OpenGL:
			return new OpenGL3ImGuiDriver();
		}
	}
}
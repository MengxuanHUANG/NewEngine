#include "pch.h"
#include "RenderCommand.h"

#include "NewEngine/Core/Application.h"

namespace engine
{

#ifdef PLATFORM_WINDOWS
	RendererAPI RenderCommand::s_RendererAPI = RendererAPI::OpenGL;
#else
	RendererAPI Renderer::s_RendererAPI = RendererAPI::None;
#endif

	Renderer3D* RenderCommand::s_Renderer3D = nullptr;

	static bool isRendererInit = false;

	void RenderCommand::Init()
	{
		MY_ENGINE_ASSERT(!isRendererInit, "Renderer already Initialized!");
		isRendererInit = true;

		s_Renderer3D = Renderer3D::Create3DRenderer(Application::GetApplication()->GetWindow()->GetWidth(), Application::GetApplication()->GetWindow()->GetHeight());
	}
	void RenderCommand::Terminate()
	{
		MY_ENGINE_ASSERT(s_Renderer3D, "Renderer never initialized!");
		delete s_Renderer3D;
	}
	void RenderCommand::BufferData()
	{
	}
	void RenderCommand::Draw(int count)
	{
		s_Renderer3D->Draw(count);
	}
	void RenderCommand::ClearColor(glm::vec4 color)
	{
		s_Renderer3D->ClearColor(color);
	}

}
#pragma once

#include "imgui.h"

namespace engine
{
	class ImGuiDriver
	{
	public:
		static void ImGuiInit() { s_Instance = CreateImGuiDriver(); }
		inline static void ImGuiShutdown() { delete s_Instance; }
		inline static void ImGuiStartFrame() { s_Instance->StartFrame(); }
		inline static void ImGuiEndFrame() { s_Instance->EndFrame(); }
		inline static void ImGuiRender() { s_Instance->Render(); }
	protected:
		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void StartFrame() = 0;
		virtual void EndFrame() = 0;

		virtual void Render() = 0;
	private:
		static ImGuiDriver* s_Instance;
		static ImGuiDriver* CreateImGuiDriver();
	};
}


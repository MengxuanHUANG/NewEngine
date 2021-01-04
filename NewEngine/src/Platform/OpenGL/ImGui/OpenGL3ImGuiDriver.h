#pragma once

#include "NewEngine/ImGui/ImGuiDriver.h"

namespace engine
{
	class OpenGL3ImGuiDriver : public ImGuiDriver
	{
	public:
		OpenGL3ImGuiDriver();
		~OpenGL3ImGuiDriver();

		virtual void Init() override;
		virtual void Shutdown() override;
		virtual void StartFrame() override;
		virtual void EndFrame() override;

		virtual void Render() override;
	};
}
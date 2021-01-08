#include "pch.h"
#include "OpenGL3ImGuiDriver.h"

#include "NewEngine/ImGui/imgui.h" 
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "NewEngine/Core/Application.h"
#include <GLFW/glfw3.h>

namespace engine
{
	OpenGL3ImGuiDriver::OpenGL3ImGuiDriver()
	{
		Init();
	}
	OpenGL3ImGuiDriver::~OpenGL3ImGuiDriver()
	{
		Shutdown();
	}

	void OpenGL3ImGuiDriver::Init()
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; //Enable Keyboard contrl
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; //Enable Gamepad contrl
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; //Enable Docking contrl
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; //Enable Muti-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge
		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer bindings
		auto window = static_cast<GLFWwindow*>(Application::GetApplication()->GetWindow()->GetNativeWindow());
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 130");
	}

	void OpenGL3ImGuiDriver::Shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void OpenGL3ImGuiDriver::StartFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void OpenGL3ImGuiDriver::EndFrame()
	{
	}

	void OpenGL3ImGuiDriver::Render()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
}

#include "NewEngine.h"
#include "NewEngine/Core/EntryPoint.h"

#include "ExampleLayer.h"

class SandboxApp :public engine::Application
{
public:
	SandboxApp()
	{
		PushLayer(new ExampleLayer());
	}
	~SandboxApp()
	{

	}
};

engine::Application* engine::CreateApplication()
{
	return new SandboxApp();
}
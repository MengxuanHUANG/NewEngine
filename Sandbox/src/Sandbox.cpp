#include "NewEngine.h"
#include "NewEngine/Core/EntryPoint.h"

#include "ExampleLayer.h"
#include "AssimpLayer.h"

class SandboxApp :public engine::Application
{
public:
	SandboxApp()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new AssimpLayer());
	}
	~SandboxApp()
	{

	}
};

engine::Application* engine::CreateApplication()
{
	return new SandboxApp();
}
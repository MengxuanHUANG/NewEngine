#pragma once

#ifdef PLATFORM_WINDOWS

int main(char* arg, char** args)
{
	auto app = engine::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif
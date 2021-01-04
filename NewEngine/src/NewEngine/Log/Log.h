#pragma once

#include"spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace engine
{
	class Logger
	{
	public:
		static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return m_EngineLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_ClientLogger; }

		static void Init(const std::string& format = "%^[%T] %n: %v%$");
	private:
		static std::shared_ptr<spdlog::logger> m_EngineLogger;
		static std::shared_ptr<spdlog::logger> m_ClientLogger;
	};
}

#pragma once

#define MY_ENGINE_TRACE(...) ::engine::Logger::GetEngineLogger()->trace(__VA_ARGS__)
#define MY_ENGINE_INFO(...)  ::engine::Logger::GetEngineLogger()->info(__VA_ARGS__)
#define MY_ENGINE_WARN(...)  ::engine::Logger::GetEngineLogger()->warn(__VA_ARGS__)
#define MY_ENGINE_ERROR(...) ::engine::Logger::GetEngineLogger()->error(__VA_ARGS__)
#define MY_ENGINE_FATAL(...) ::engine::Logger::GetEngineLogger()->fatal(__VA_ARGS__)

#define MY_CLIENT_TRACE(...) ::engine::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define MY_CLIENT_INFO(...)  ::engine::Logger::GetClientLogger()->info(__VA_ARGS__)
#define MY_CLIENT_WARN(...)  ::engine::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define MY_CLIENT_ERROR(...) ::engine::Logger::GetClientLogger()->error(__VA_ARGS__)
#define MY_CLIENT_FATAL(...) ::engine::Logger::GetClientLogger()->fatal(__VA_ARGS__)

#ifdef MY_DEBUG
#define MY_ENABLE_ASSERTS
#endif

#ifdef MY_ENABLE_ASSERTS
#define MY_CLIENT_ASSERT(x, ...) {if(!(x)) {MY_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#define MY_ENGINE_ASSERT(x, ...) {if(!(x)) {MY_ENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
#define MY_CLIENT_ASSERT(x, ...)
#define MY_ENGINE_ASSERT(x, ...)
#endif
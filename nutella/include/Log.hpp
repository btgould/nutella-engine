#pragma once

#include <memory>

#include "Core.hpp"

#include "spdlog/spdlog.h"

namespace Nutella {
	class Log {
	  public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {
			return s_CoreLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() {
			return s_ClientLogger;
		}

	  private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
} // namespace Nutella

// core logging macros
#define NT_CORE_TRACE(...) ::Nutella::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define NT_CORE_INFO(...) ::Nutella::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NT_CORE_WARN(...) ::Nutella::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NT_CORE_ERROR(...) ::Nutella::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NT_CORE_CRITICAL(...)                                                  \
	::Nutella::Log::GetCoreLogger()->critical(__VA_ARGS__)

// client logger macros
#define NT_CLIENT_TRACE(...)                                                   \
	::Nutella::Log::GetClientLogger()->trace(__VA_ARGS__)
#define NT_CLIENT_INFO(...) ::Nutella::Log::GetClientLogger()->info(__VA_ARGS__)
#define NT_CLIENT_WARN(...) ::Nutella::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NT_CLIENT_ERROR(...)                                                   \
	::Nutella::Log::GetClientLogger()->error(__VA_ARGS__)
#define NT_CLIENT_CRITICAL(...)                                                \
	::Nutella::Log::GetClientLogger()->critical(__VA_ARGS__)

// TODO: strip definitions from distribution builds
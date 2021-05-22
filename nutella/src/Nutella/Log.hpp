#pragma once

// NOTE: BE VERY CAREFUL, spdlog.h MUST BE INCLUDED BEFORE fmt/ostr.h
// IF IT IS NOT, A LINKING ERROR IS GENERATED FOR SANDBOX, BUT NOT NUTELLA
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Nutella {
	// class to encapsulate logging methods
	class Log {
	  public:
		// creates and initializes spdlog outputs for nutella and client
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	  private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
} // namespace Nutella

#ifndef NT_DIST
  // core logging macros
	#define NT_CORE_TRACE(...) ::Nutella::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define NT_CORE_INFO(...) ::Nutella::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define NT_CORE_WARN(...) ::Nutella::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define NT_CORE_ERROR(...) ::Nutella::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define NT_CORE_CRITICAL(...) ::Nutella::Log::GetCoreLogger()->critical(__VA_ARGS__)

	// client logger macros
	#define NT_TRACE(...) ::Nutella::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define NT_INFO(...) ::Nutella::Log::GetClientLogger()->info(__VA_ARGS__)
	#define NT_WARN(...) ::Nutella::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define NT_ERROR(...) ::Nutella::Log::GetClientLogger()->error(__VA_ARGS__)
	#define NT_CRITICAL(...) ::Nutella::Log::GetClientLogger()->critical(__VA_ARGS__)
#else
	#define NT_CORE_TRACE(...)
	#define NT_CORE_INFO(...)
	#define NT_CORE_WARN(...)
	#define NT_CORE_ERROR(...)
	#define NT_CORE_CRITICAL(...)

	#define NT_TRACE(...)
	#define NT_INFO(...)
	#define NT_WARN(...)
	#define NT_ERROR(...)
	#define NT_CRITICAL(...)
#endif

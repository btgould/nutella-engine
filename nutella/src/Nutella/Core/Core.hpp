#pragma once

#include <signal.h>

#ifdef NT_ENABLE_ASSERTS
	#define NT_ASSERT(x, ...)                                                                      \
		{                                                                                          \
			if (!(x)) {                                                                            \
				NT_ERROR("Assertation failed: {0}", __VA_ARGS__);                                  \
				raise(SIGINT);                                                                     \
			}                                                                                      \
		}
	#define NT_CORE_ASSERT(x, ...)                                                                 \
		{                                                                                          \
			if (!(x)) {                                                                            \
				NT_CORE_ERROR("Assertation failed: {0}", __VA_ARGS__);                             \
				raise(SIGINT);                                                                     \
			}                                                                                      \
		}
#else
	#define NT_ASSERT(x, ...)
	#define NT_CORE_ASSERT(x, ...)
#endif

#ifdef NT_PROFILE
	#define NT_PROFILE_BEGIN_SESSION(name, filepath)                                               \
		::Nutella::Instrumentor::Get().BeginSession(name, filepath)
	#define NT_PROFILE_END_SESSION() ::Nutella::Instrumentor::Get().EndSession()
	#define NT_PROFILE_SCOPE(name) ::Nutella::InstrumentationTimer timer##__LINE__(name)
	#define NT_PROFILE_FUNC() NT_PROFILE_SCOPE(__PRETTY_FUNCTION__)
#else
	#define NT_PROFILE_BEGIN_SESSION(name, filepath)
	#define NT_PROFILE_END_SESSION()
	#define NT_PROFILE_SCOPE(name)
	#define NT_PROFILE_FUNC()
#endif

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace Nutella {
	template <typename T> using Ref = std::shared_ptr<T>;
	template <typename T, typename... Args> constexpr Ref<T> CreateRef(Args&&... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <typename T> using ScopedRef = std::unique_ptr<T>;
	template <typename T, typename... Args> constexpr ScopedRef<T> CreateScopedRef(Args&&... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
} // namespace Nutella

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
